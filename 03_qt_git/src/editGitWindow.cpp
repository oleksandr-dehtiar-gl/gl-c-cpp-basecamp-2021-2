#include "editGitWindow.hpp"

namespace gitgui {
	
	EditGitWindow::EditGitWindow(QWidget *pwgt)
		: QWidget(pwgt)
	{
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
		
		mpButtonAddAll = new QPushButton("Index ALL");
		mpButtonRestoreAll = new QPushButton("Restore ALL");
		mpButtonRefresh = new QPushButton("Refresh");
		
		QGridLayout *pIndexGridButton = new QGridLayout;
		pIndexGridButton->setMargin(5);
		pIndexGridButton->setSpacing(10);
		pIndexGridButton->addWidget(mpButtonAddAll, 0, 0);
		pIndexGridButton->addWidget(mpButtonRestoreAll, 0, 1);
		pIndexGridButton->addWidget(mpButtonRefresh, 1, 0);
		
		QVBoxLayout *pVBIndexLayout = new QVBoxLayout;
		pVBIndexLayout->addWidget(pLblTitleIndexed);
		pVBIndexLayout->addWidget(mpViewIndexedFiles);
		pVBIndexLayout->addWidget(pLblTitleNotIndexed);
		pVBIndexLayout->addWidget(mpViewNotIndexedFiles);
		pVBIndexLayout->addLayout(pIndexGridButton);

		setConnections();
		
		setLayout(pVBIndexLayout);
	}
	
	void EditGitWindow::setConnections() {
		connect(mpViewIndexedFiles, &QListView::doubleClicked, this, &EditGitWindow::selectIndexFile);
		connect(mpViewNotIndexedFiles, &QListView::doubleClicked, this, &EditGitWindow::selectNotIndexFile);
		connect(mpButtonAddAll, &QPushButton::clicked, this, &EditGitWindow::clickedIndexAll);
		connect(mpButtonRestoreAll, &QPushButton::clicked, this, &EditGitWindow::clickedRestoreAll);
		connect(mpButtonRefresh, &QPushButton::clicked, this, &EditGitWindow::clickedRefresh);
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
		auto notIndexFileList{mpModelIndexedFiles->stringList()};
		for(auto &file : notIndexFileList)
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
	
}
