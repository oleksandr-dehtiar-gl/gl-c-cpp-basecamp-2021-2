#include "editGitWindow.hpp"

namespace gitgui {
	
	EditGitWindow::EditGitWindow(QWidget *pwgt)
		: QWidget(pwgt)
	{
		auto frameBounder = QFrame::Box | QFrame::Sunken;
		auto frameLineWidth = 1;
		
		// Create Index panel
		/////////////////////
		QFrame *pIndexFramePanel = new QFrame;
		pIndexFramePanel->setFrameStyle(frameBounder);
		pIndexFramePanel->setLineWidth(frameLineWidth);
		
		// Create models index and not index
		mpModelIndexedFiles = new QStringListModel();
		mpModelNotIndexedFiles = new QStringListModel();
		
		// Create view for models not index
		mpViewNotIndexedFiles = new QListView();
		mpViewNotIndexedFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
		mpViewNotIndexedFiles->setModel(mpModelNotIndexedFiles);
		
		// Create view for models index
		mpViewIndexedFiles = new QListView();
		mpViewIndexedFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
		mpViewIndexedFiles->setModel(mpModelIndexedFiles);
		QLabel *pLblTitleIndexed = new QLabel("Indexed");
		QLabel *pLblTitleNotIndexed = new QLabel("Not Indexed");
		
		// Create buttons for index files
		QPushButton *mpButtonAddAll = new QPushButton("Index ALL");
		QPushButton *mpButtonRestoreAll = new QPushButton("Restore ALL");
		QPushButton *mpButtonRefresh = new QPushButton("Refresh");
		connect(mpButtonAddAll, &QPushButton::clicked, this, &EditGitWindow::clickedIndexAll);
		connect(mpButtonRestoreAll, &QPushButton::clicked, this, &EditGitWindow::clickedRestoreAll);
		connect(mpButtonRefresh, &QPushButton::clicked, this, &EditGitWindow::clickedRefresh);
		
		// Make grid for place index buttons
		QGridLayout *pIndexGridButton = new QGridLayout;
		pIndexGridButton->setMargin(5);
		pIndexGridButton->setSpacing(5);
		pIndexGridButton->addWidget(mpButtonAddAll, 0, 0);
		pIndexGridButton->addWidget(mpButtonRestoreAll, 0, 1);
		pIndexGridButton->addWidget(mpButtonRefresh, 1, 0);
		
		// Index panel layout
		QVBoxLayout *pIndexLayout = new QVBoxLayout;
		pIndexLayout->addWidget(pLblTitleIndexed);
		pIndexLayout->addWidget(mpViewIndexedFiles);
		pIndexLayout->addWidget(pLblTitleNotIndexed);
		pIndexLayout->addWidget(mpViewNotIndexedFiles);
		pIndexLayout->addLayout(pIndexGridButton);
		pIndexFramePanel->setLayout(pIndexLayout);
		
		// Create Commit panel
		//////////////////////
		QFrame *pCommitFramePanel = new QFrame;
		pCommitFramePanel->setFrameStyle(frameBounder);
		pCommitFramePanel->setLineWidth(frameLineWidth);
		
		mpCommitStatus = new QTextEdit;
		mpCommitStatus->setReadOnly(true);
		mpCommitMsg = new QTextEdit;
		QPushButton *mpMakeCommit = new QPushButton("Commit");
		QPushButton *mpClearCommit = new QPushButton("Clear");
		QPushButton *mpPush = new QPushButton("Push");
		QPushButton *mpPull = new QPushButton("Pull");
		QLabel *pLblTitleCommitStatusText = new QLabel("Show Status");
		QLabel *pLblTitleCommitMsg = new QLabel("Field for Commit MSG");
		connect(mpMakeCommit, &QPushButton::clicked, this, &EditGitWindow::clickedCommit);
		connect(mpClearCommit, &QPushButton::clicked, this, &EditGitWindow::clickedClearCommit);
		connect(mpPush, &QPushButton::clicked, this, &EditGitWindow::clickedPush);
		connect(mpPull, &QPushButton::clicked, this, &EditGitWindow::clickedPull);
		
		// Commit button grid
		QGridLayout *pGridCommitButton = new QGridLayout;
		pGridCommitButton->setMargin(5);
		pGridCommitButton->setSpacing(5);
		pGridCommitButton->addWidget(mpMakeCommit, 0, 0);
		pGridCommitButton->addWidget(mpClearCommit, 0, 1);
		pGridCommitButton->addWidget(mpPush, 1, 0);
		pGridCommitButton->addWidget(mpPull, 1, 1);
		
		// Place commit panel widgets and buttons
		QVBoxLayout *pCommitPanel = new QVBoxLayout;
		pCommitPanel->addWidget(pLblTitleCommitStatusText);
		pCommitPanel->addWidget(mpCommitStatus);
		pCommitPanel->addWidget(pLblTitleCommitMsg);
		pCommitPanel->addWidget(mpCommitMsg);
		pCommitPanel->addLayout(pGridCommitButton);
		pCommitFramePanel->setLayout(pCommitPanel);

		// Main edit window layout 
		/////////////////////////
		QHBoxLayout *pHBEditWindow = new QHBoxLayout;
		pHBEditWindow->addWidget(pIndexFramePanel);
		pHBEditWindow->addWidget(pCommitFramePanel);
		
		// Set connections
		setConnectionsForIndex();
		setConnectionsForCommit();
		
		setLayout(pHBEditWindow);
	}
	
	void EditGitWindow::setConnectionsForCommit() {
		
	}
	
	void EditGitWindow::setConnectionsForIndex() {
		connect(mpViewIndexedFiles, &QListView::doubleClicked, this, &EditGitWindow::selectIndexFile);
		connect(mpViewNotIndexedFiles, &QListView::doubleClicked, this, &EditGitWindow::selectNotIndexFile);
	}
	
	void EditGitWindow::setIndexFiles(const std::list<IndexFile>& listFile) {
		QStringList indexedList;
		QStringList notIndexedList;
		for (const auto &file : listFile) {
			if (file.isIndexed())
				indexedList << file.name();
			else
				notIndexedList << file.name();
		}
		mpModelIndexedFiles->setStringList(indexedList);
		mpModelNotIndexedFiles->setStringList(notIndexedList);
	}
	
	void EditGitWindow::selectIndexFile(const QModelIndex& index) {
		if (!index.isValid())
			return;
		std::list<IndexFile> list;
		IndexFile file{mpModelIndexedFiles->data(index).toString()};
		list.push_back(std::move(file));
		emit removeFromIndexingStage(list);
	}
	
	void EditGitWindow::clickedRestoreAll() {
		std::list<IndexFile> list;
		auto allIndexFileList{mpModelIndexedFiles->stringList()};
		for(auto &file : allIndexFileList)
			list.push_back(IndexFile{file});
		emit removeFromIndexingStage(list);
	}
	
	void EditGitWindow::selectNotIndexFile(const QModelIndex& index) {
		if (!index.isValid())
			return;
		std::list<IndexFile> list;
		IndexFile file{mpModelNotIndexedFiles->data(index).toString()};
		list.push_back(std::move(file));
		emit addToIndexingStage(list);
	}
	
	void EditGitWindow::clickedIndexAll() {
		std::list<IndexFile> list;
		auto notIndexFileList{mpModelNotIndexedFiles->stringList()};
		for(auto &file : notIndexFileList)
			list.push_back(IndexFile{file});
		emit addToIndexingStage(list);
	}
	
	
	void EditGitWindow::clickedRefresh() {
		emit refreshEditWindow();
	}
	
	void EditGitWindow::clickedCommit() {
		auto allIndexFileList{mpModelIndexedFiles->stringList()};
		if (allIndexFileList.isEmpty()) {
			mpCommitStatus->clear();
			mpCommitStatus->setTextColor(Qt::red);
			mpCommitStatus->setText(QString{"No index files for make commit!"});
			return;
		}
		auto CommitMSG{mpCommitMsg->toPlainText()};
		if (CommitMSG.isEmpty()) {
			mpCommitStatus->clear();
			mpCommitStatus->setTextColor(Qt::red);
			mpCommitStatus->setText(QString{"Not Commit MSG! Write Commit MSG befor make commit!"});
			return;
		}
		emit makeCommit(mpCommitMsg->toPlainText());
	}
	
	void EditGitWindow::clickedClearCommit() {
		mpCommitMsg->clear();
		mpCommitStatus->clear();
	}
	
	void EditGitWindow::clickedPush() {
		QTextStream(stdout) << "clickedPush" << endl;
	}
	
	void EditGitWindow::clickedPull() {
		QTextStream(stdout) << "clickedPull" << endl;
	}
	
	void EditGitWindow::setStatusMakeCommit(const QString &status) {
		mpCommitStatus->clear();
		mpCommitStatus->setTextColor(Qt::blue);
		mpCommitStatus->setText(status);
	}
	
}
