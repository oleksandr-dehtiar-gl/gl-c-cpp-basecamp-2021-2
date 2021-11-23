#include "playlistgui.hpp"
#include <iostream>

constexpr char filterformat[] = "*.mp3 *.mp4";
constexpr char filterplaylist[] = "*.mplist";
constexpr char startSearchDir[] = "E:/BACKUP_FROM_OLD_DISC/MUSIC";

namespace mediaplayer {
	
	PlaylistGui::PlaylistGui(QWidget *pwgt) 
		: QDialog(pwgt)
	{
		mpListView = new QListView;
		mpListView->setModel(&mPlListModel);
		mpListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
		
		mpHBox_1 = new QHBoxLayout;
		mpHBox_1->addWidget(mpListView);
		
		addActions();
		createMenus();
		
		mpHBox_2 = new QHBoxLayout;
		mpHBox_2->addWidget(mpAddMenuBar);
		mpHBox_2->addWidget(mpDelMenuBar);
		mpHBox_2->addWidget(mpPllistMenuBar);
		mpHBox_2->addStretch(1);
		
		mpVBox = new QVBoxLayout;
		mpVBox->addLayout(mpHBox_1);
		mpVBox->addLayout(mpHBox_2);

		connect(this, &PlaylistGui::deleteSelectFiles, &mPlListModel, &Playlistmodel::deleteSelectFiles);
		connect(this, &PlaylistGui::deleteAllFiles, &mPlListModel, &Playlistmodel::deleteAllFiles);
		connect(this, &PlaylistGui::addFilesToList, &mPlListModel, &Playlistmodel::addFiles);
		connect(this, &PlaylistGui::addDirToList, &mPlListModel, &Playlistmodel::addDir);
		
		connect(this, &PlaylistGui::savePlaylistToFile, &mPlListModel, &Playlistmodel::savePlaylist);
		connect(this, &PlaylistGui::openPlaylistFromFile, &mPlListModel, &Playlistmodel::openPlaylist);
		connect(this, &PlaylistGui::loadPlaylistFromFile, &mPlListModel, &Playlistmodel::loadPlaylist);
		
		setLayout(mpVBox);
		resize(600, 800);
	}

	void PlaylistGui::addActions() {
		mpAddFile = new QAction("&Add File", this);
		connect(mpAddFile, &QAction::triggered, this, &PlaylistGui::addFiles);
		
		mpAddDirectoy = new QAction("&Add Directory", this);
		connect(mpAddDirectoy, &QAction::triggered, this, &PlaylistGui::addDirectory);
		
		mpAddPlaylist = new QAction("&Add Playlist", this);
		connect(mpAddPlaylist, &QAction::triggered, this, &PlaylistGui::addPlaylist);
		
		mpDeleteFiles = new QAction("&Delete Select files", this);
		mpDeleteFiles->setShortcuts(QKeySequence::Delete);
		connect(mpDeleteFiles, &QAction::triggered, this, &PlaylistGui::removeSelectFiles);
		
		mpClearPlaylist = new QAction("&Clear Playlist", this);
		connect(mpClearPlaylist, &QAction::triggered, this, &PlaylistGui::removeAllFiles);
		
		mpLoadPlaylist = new QAction("&Load Playlist", this);
		connect(mpLoadPlaylist, &QAction::triggered, this, &PlaylistGui::loadPlaylist);
		
		mpSavePlaylist = new QAction("&Save Playlist", this);
		connect(mpSavePlaylist, &QAction::triggered, this, &PlaylistGui::savePlaylist);
		
	}
	
	void PlaylistGui::createMenus() {
		mpAddMenuBar = new QMenuBar;
		mpAddMenu = new QMenu("&ADD");
		
		mpAddMenu->addAction(mpAddFile);
		mpAddMenu->addAction(mpAddDirectoy);
		mpAddMenu->addAction(mpAddPlaylist);
		
		mpAddMenuBar->setDefaultUp(true);
		mpAddMenuBar->addMenu(mpAddMenu);
		
		mpDelMenuBar = new QMenuBar;
		mpDelMenu = new QMenu("&DEL");
		
		mpDelMenu->addAction(mpDeleteFiles);
		mpDelMenu->addAction(mpClearPlaylist);
		
		mpDelMenuBar->setDefaultUp(true);
		mpDelMenuBar->addMenu(mpDelMenu);
		
		mpPllistMenuBar = new QMenuBar;
		mpPllistMenu = new QMenu("&LIST");
		
		mpPllistMenu->addAction(mpLoadPlaylist);
		mpPllistMenu->addAction(mpSavePlaylist);
		
		mpPllistMenuBar->setDefaultUp(true);
		mpPllistMenuBar->addMenu(mpPllistMenu);
		
	}

	void PlaylistGui::addFiles() {
		QStringList listFiles(QFileDialog::getOpenFileNames(0, "Select Files", startSearchDir, filterformat));
		if (listFiles.empty())
			return;
		emit addFilesToList(listFiles);
	}
	
	void PlaylistGui::addDirectory() {
		QString path = QFileDialog::getExistingDirectory(0, "Select Directory", startSearchDir);
		if (path.isNull())
			return;
		emit addDirToList(path);
	}

	void PlaylistGui::removeSelectFiles() {
		emit deleteSelectFiles(mpListView->selectionModel()->selectedIndexes());
	}
	
	void PlaylistGui::removeAllFiles() {
		emit deleteAllFiles();
	}
	

	void PlaylistGui::addPlaylist() {
		QString path(QFileDialog::getOpenFileName(0, "Open Playlist", startSearchDir, filterplaylist));
		if (path.isNull())
			return;
		emit openPlaylistFromFile(path);
	}

	void PlaylistGui::savePlaylist() {
		QString strFilter;
		QString saveFile = QFileDialog::getSaveFileName(0, "Save File", "playlist", filterplaylist, &strFilter);
		emit savePlaylistToFile(saveFile);

	}
	
	void PlaylistGui::loadPlaylist() {
		QString path(QFileDialog::getOpenFileName(0, "Open Playlist", startSearchDir, filterplaylist));
		if (path.isNull())
			return;
		emit loadPlaylistFromFile(path);
	}
	// QTextStream out(stdout);
	// out << saveFile << endl;
	
}

