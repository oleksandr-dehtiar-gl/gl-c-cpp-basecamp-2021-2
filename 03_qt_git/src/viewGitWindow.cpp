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
		mptrSearchResult = new QLineEdit;
		mptrSearchResult->setReadOnly(true);
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

		QHBoxLayout *ptrHBoxSearchChanges = new QHBoxLayout;
		ptrHBoxSearchChanges->addWidget(ptrSearchLbl);
		ptrHBoxSearchChanges->addWidget(mptrSearchField);
		ptrHBoxSearchChanges->addWidget(mptrSearchResult);

		QVBoxLayout *ptrVBRepo = new QVBoxLayout;
		ptrVBRepo->addWidget(ptrVSplitComChanges);
		ptrVBRepo->addWidget(mptrActiveBranch);
		ptrVBRepo->addWidget(mptrActiveCommit);
		ptrVBRepo->addLayout(ptrHBoxSearchChanges);
		
		setLayout(ptrVBRepo);
	}
	
	void ViewGitWindow::setModelCommit(std::shared_ptr<ModelCommitTree> model) {
		mModelCommit = model;
		mptrViewCommits->setModel(mModelCommit.get());
		mptrViewCommits->update(QModelIndex());
		
		// Set evant for context menu
		mptrViewCommits->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(mptrViewCommits, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(checkoutCommit(const QPoint&)));
		
		// Check commit
		connect(mptrViewCommits, &QTreeView::doubleClicked, this, &ViewGitWindow::getSHACommit);
	}
	
	void ViewGitWindow::setModelBranch(std::shared_ptr<ModelBranchList> model) {
		mBranchModel = model;
		mptrViewBranches->setModel(mBranchModel.get());
		mptrViewBranches->update(QModelIndex());
		
		// Set evant for context menu
		mptrViewBranches->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(mptrViewBranches, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(checkoutBranch(const QPoint&)));
				
		// Check branch
		connect(mptrViewBranches, &QListView::doubleClicked, this, &ViewGitWindow::getSHABranch);
	}
	
	void ViewGitWindow::showCommitChanges(const QString& changes) {
		QStringList commitChanges(changes.split("\n"));
		mptrCommitChanges->clear();
		for(auto &line : commitChanges) {
			mptrCommitChanges->setTextColor(Qt::black);
			// Separate between files that has been changed
			if (line.contains(QRegExp("^diff"))) {
				mptrCommitChanges->setTextColor(Qt::darkGray);
				mptrCommitChanges->append(QString());
				mptrCommitChanges->append(QString("========================================================="));
				mptrCommitChanges->append(QString());
				mptrCommitChanges->setTextColor(Qt::blue);
				continue;
			}
			// Set color for each line type
			if (line.contains(QRegExp("\\b(^new|^index)\\b"))) {
				continue;
				mptrCommitChanges->setTextColor(Qt::blue);
			}
			else if (line.contains(QRegExp("^---"))) 
				mptrCommitChanges->setTextColor(Qt::blue);
			else if (line.contains(QRegExp("^-"))) 
				mptrCommitChanges->setTextColor(Qt::red);
			else if (line.contains(QRegExp("^\\+\\+\\+"))) 
				mptrCommitChanges->setTextColor(Qt::blue);
			else if (line.contains(QRegExp("^\\+"))) 
				mptrCommitChanges->setTextColor(Qt::darkGreen);
			else if (line.contains(QRegExp("^@@"))) 
				continue;
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
				emit makeCheckout(mModelCommit->getCommit(item));
				commitForShowChanges(mModelCommit->getCommit(item));
			}
		}
	}
	
	void ViewGitWindow::checkoutBranch(const QPoint& pos) {
		QPoint globalPos = mptrViewBranches->mapToGlobal(pos);
		auto item = mptrViewBranches->indexAt(pos);
		if (item.isValid()) {
			if (showContextMenu(globalPos, QString{"Checkout Branche"})) {
				emit makeCheckout(mBranchModel->getBranch(item));
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
		mptrActiveCommit->setText(QString{"Commit HEAD: "} + sha.sha());
		mptrActiveCommit->setStyleSheet("QLabel { color : darkBlue; }");
	}
	
	void ViewGitWindow::showActiveBranch(const Branch& branch) {
		mptrActiveBranch->setText(QString{"Branch of commit HEAD: "} + branch.name());
		mptrActiveBranch->setStyleSheet("QLabel { color : darkBlue; }");
	}
	
}
