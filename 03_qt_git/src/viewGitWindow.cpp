#include "viewGitWindow.hpp"

namespace gitgui {
	
	ViewGitWindow::ViewGitWindow(QWidget *ptrwgt) 
		: QFrame(ptrwgt)
	{
		// Branches 
		mptrViewBranches = new QListView;
		mptrViewBranches->setEditTriggers(QAbstractItemView::NoEditTriggers);
		// Commits 
		mptrViewCommits = new QTreeView;
		// Search Changes
		QLabel *ptrSearchLbl = new QLabel("Enter find text changes");
		mptrSearchField = new QLineEdit;
		mptrSearchResult = new QComboBox;
		mptrSearchResult->showPopup();
		mptrFindTextInCommitsButton = new QPushButton("Find Commits");
		// Status active commit and branch
		mptrActiveCommit = new QLabel;
		mptrActiveBranch = new QLabel;
		// Commit changes
		mptrCommitChanges = new QTextEdit();
		mptrCommitChanges->setReadOnly(true);

		// Arrangement of widgets
		QSplitter *ptrHSplitRepo = new QSplitter(Qt::Horizontal);
		ptrHSplitRepo->addWidget(mptrViewBranches);
		ptrHSplitRepo->addWidget(mptrViewCommits);

		QSplitter *ptrVSplitComChanges = new QSplitter(Qt::Vertical);
		ptrVSplitComChanges->addWidget(ptrHSplitRepo);
		ptrVSplitComChanges->addWidget(mptrCommitChanges);

		QSplitter *ptrHSplitSerchText = new QSplitter(Qt::Horizontal);
		ptrHSplitSerchText->addWidget(mptrSearchField);
		ptrHSplitSerchText->addWidget(mptrSearchResult);
		
		QHBoxLayout *ptrHBoxSearchChanges = new QHBoxLayout;
		ptrHBoxSearchChanges->addWidget(ptrSearchLbl);
		ptrHBoxSearchChanges->addWidget(mptrFindTextInCommitsButton);
		ptrHBoxSearchChanges->addWidget(ptrHSplitSerchText);

		QVBoxLayout *ptrVBRepo = new QVBoxLayout;
		ptrVBRepo->addWidget(ptrVSplitComChanges);
		ptrVBRepo->addWidget(mptrActiveBranch);
		ptrVBRepo->addWidget(mptrActiveCommit);
		ptrVBRepo->addLayout(ptrHBoxSearchChanges);
		
		setConnections();
		
		setLayout(ptrVBRepo);
	}
	
	void ViewGitWindow::setConnections() {
		connect(mptrSearchResult, SIGNAL(activated(int)), SLOT(selectSearchResultCommit(int)));
		
		// Connections for find commits where text was changed
		connect(mptrFindTextInCommitsButton, SIGNAL(clicked()), SLOT(searchCommitsForSomeText()));
		
		// Connections for open context menu and make checkout to select commit or branch
		connect(mptrViewCommits, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(checkoutCommit(const QPoint&)));
		connect(mptrViewBranches, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(checkoutBranch(const QPoint&)));
		
		// Connections for check commits of branches for show changes
		connect(mptrViewCommits, &QTreeView::doubleClicked, this, &ViewGitWindow::getSHACommit);
		connect(mptrViewBranches, &QListView::doubleClicked, this, &ViewGitWindow::getSHABranch);
	}
	
	void ViewGitWindow::setModelCommit(std::shared_ptr<ModelCommitTree> model) {
		mModelCommit = model;
		mptrViewCommits->setModel(mModelCommit.get());
		mptrViewCommits->update(QModelIndex());
		
		// Set evant for context menu
		mptrViewCommits->setContextMenuPolicy(Qt::CustomContextMenu);
		
		// Check commit
	}
	
	void ViewGitWindow::setModelBranch(std::shared_ptr<ModelBranchList> model) {
		mBranchModel = model;
		mptrViewBranches->setModel(mBranchModel.get());
		mptrViewBranches->update(QModelIndex());
		
		// Set evant for context menu
		mptrViewBranches->setContextMenuPolicy(Qt::CustomContextMenu);
				
		// Check branch
	}
	
	void ViewGitWindow::setColorLine(const QString& line) {
		if (line.contains(QRegExp("^---"))) 
			mptrCommitChanges->setTextColor(Qt::blue);
		else if (line.contains(QRegExp("^-"))) 
			mptrCommitChanges->setTextColor(Qt::red);
		else if (line.contains(QRegExp("^\\+\\+\\+"))) 
			mptrCommitChanges->setTextColor(Qt::blue);
		else if (line.contains(QRegExp("^\\+"))) 
			mptrCommitChanges->setTextColor(Qt::darkGreen);
	}
	
	bool ViewGitWindow::skipLine(const QString& line) {
		bool ret = false;
		if (line.contains(QRegExp("\\b(^new|^index)\\b")))
			ret = true;
		else if (line.contains(QRegExp("^@@"))) 
			ret = true;
		return ret;
	}
	
	int ViewGitWindow::addseparatorLines(const QString& line) {
		if (line.contains(QRegExp("^diff"))) {
			mptrCommitChanges->setTextColor(Qt::darkGray);
			mptrCommitChanges->append(QString());
			mptrCommitChanges->append(QString("========================================================="));
			mptrCommitChanges->append(QString());
			mptrCommitChanges->setTextColor(Qt::blue);
			return 3; // 3 line add to widget
		}
		return 0; // 0 line add to widget
	}
	
	void ViewGitWindow::showCommitChanges(const QString& changes) {
		QStringList commitChanges(changes.split("\n"));
		mptrCommitChanges->setTextBackgroundColor(Qt::white);
		mptrCommitChanges->clear();
		for(auto &line : commitChanges) {
			mptrCommitChanges->setTextColor(Qt::black);
			// Separate between files
			addseparatorLines(line);
			if (skipLine(line)) 
				continue;
			setColorLine(line);
			mptrCommitChanges->append(line);
		}
		QTextCursor textCursor = mptrCommitChanges->textCursor();
		textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
		mptrCommitChanges->setTextCursor(textCursor);
	}
	
	void ViewGitWindow::getSHACommit(const QModelIndex &index) {
		emit commitForShowChanges(mModelCommit->getCommit(index));
	}
	
	void ViewGitWindow::getSHABranch(const QModelIndex &index) {
		emit commitForShowChanges(mBranchModel->getBranch(index));
	}
	
	void ViewGitWindow::checkoutCommit(const QPoint& pos) {
		QPoint globalPos = mptrViewCommits->mapToGlobal(pos);
		auto item = mptrViewCommits->indexAt(pos);
		if (item.isValid()) {
			if (showContextMenu(globalPos, QString{"Checkout Commit"})) {
				emit makeCheckoutCommit(mModelCommit->getCommit(item));
				commitForShowChanges(mModelCommit->getCommit(item));
			}
		}
	}
	
	void ViewGitWindow::checkoutBranch(const QPoint& pos) {
		QPoint globalPos = mptrViewBranches->mapToGlobal(pos);
		auto item = mptrViewBranches->indexAt(pos);
		if (item.isValid()) {
			if (showContextMenu(globalPos, QString{"Checkout Branche"})) {
				emit makeCheckoutBranch(mBranchModel->getBranch(item));
				commitForShowChanges(mBranchModel->getBranch(item));
			}
		}
	}
	
	bool ViewGitWindow::showContextMenu(const QPoint& pos, const QString& menuName) {
		QMenu myMenu;
		myMenu.addAction(menuName);
		QAction* selectedItem = myMenu.exec(pos);
		return selectedItem;
	}
	
	void ViewGitWindow::showActiveCommit(const SHA& sha) {
		mptrActiveCommit->setText(QString{"Commit: "} + sha.sha());
		mptrActiveCommit->setStyleSheet("QLabel { color : darkBlue; }");
	}
	
	void ViewGitWindow::showActiveBranch(const Branch& branch) {
		mptrActiveBranch->setText(QString{"Branch: "} + branch.name());
		mptrActiveBranch->setStyleSheet("QLabel { color : darkBlue; }");
	}
	
	void ViewGitWindow::searchCommitsForSomeText() {
		QString text{mptrSearchField->displayText()};
		
		// Clear previos data from combobox and search text
		QString{}.swap(mLastSearchText);
		mptrSearchResult->clear();
		if (text.isEmpty())
			return;
		
		mLastSearchText = text;
		emit findCommitsThatContainText(text);
	}
	
	void ViewGitWindow::commitsThatHaveTextChanges(const std::list<Commit>& commits) {
		QStringList resultCommits;
		for (auto &commit : commits) {
			resultCommits << commit.sha();
		}
		mptrSearchResult->clear();
		mptrSearchResult->addItems(resultCommits);
	}
	
	void ViewGitWindow::selectSearchResultCommit(int index) {
		emit showCommitWhereFindText(Commit{mptrSearchResult->itemText(index)});
	}
	
	void ViewGitWindow::showCommitWithFindText(const QString& contain) {
		QTextStream(stdout) << "YEEEEES MUTHER FUCKER!!!!" << endl;
		// showCommitChanges(contain);
		QStringList commitChanges(contain.split("\n"));
		mptrCommitChanges->clear();
		int firstMatchLineNumber = 0;
		int linenum = 1;
		for(auto &line : commitChanges) {
			mptrCommitChanges->setTextBackgroundColor(Qt::white);
			mptrCommitChanges->setTextColor(Qt::black);
			// Separate between files
			linenum += addseparatorLines(line);
			if (skipLine(line)) 
				continue;
			setColorLine(line);
			
			if (line.contains(QRegExp(mLastSearchText))) {
				mptrCommitChanges->setTextBackgroundColor(Qt::cyan);
				if (firstMatchLineNumber == 0)
					firstMatchLineNumber = linenum;
			}
		
			mptrCommitChanges->append(line);
			++linenum;
		}
		QTextCursor cursor(mptrCommitChanges->document()->findBlockByLineNumber(firstMatchLineNumber - 10));
		mptrCommitChanges->setTextCursor(cursor);
	}
	
}
