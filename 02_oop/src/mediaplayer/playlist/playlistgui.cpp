#include "playlistgui.hpp"

namespace mediaplayer {
	
	PlaylistGui::PlaylistGui(QWidget *pwgt) 
		: QDialog(pwgt)
	{
		mpPlListModel = new Playlistmodel;
		mpListView = new QListView;
		mpListView->setModel(mpPlListModel);
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

		connect(this, &PlaylistGui::deleteSelectFiles, mpPlListModel, &Playlistmodel::deleteSelectFiles);
		connect(this, &PlaylistGui::deleteAllFiles, mpPlListModel, &Playlistmodel::deleteAllFiles);
		connect(this, &PlaylistGui::addFilesToList, mpPlListModel, &Playlistmodel::addFiles);
		connect(this, &PlaylistGui::addDirToList, mpPlListModel, &Playlistmodel::addDir);
		
		connect(this, &PlaylistGui::savePlaylistToFile, mpPlListModel, &Playlistmodel::savePlaylist);
		connect(this, &PlaylistGui::openPlaylistFromFile, mpPlListModel, &Playlistmodel::openPlaylist);
		connect(this, &PlaylistGui::loadPlaylistFromFile, mpPlListModel, &Playlistmodel::loadPlaylist);
		
		connect(mpListView, &QListView::doubleClicked, mpPlListModel, &Playlistmodel::getIndexFileForPlay);
		connect(mpPlListModel, SIGNAL(sendFileForPlay(std::shared_ptr<MediaFile>)), SIGNAL(getMediaFileForPlay(std::shared_ptr<MediaFile>)));
		connect(mpPlListModel, SIGNAL(sendFile(std::shared_ptr<MediaFile>)), SIGNAL(getMediaFile(std::shared_ptr<MediaFile>)));
		
		connect(this, &PlaylistGui::nextMediFile, mpPlListModel, &Playlistmodel::nextFile);
		connect(this, &PlaylistGui::previosMediFile, mpPlListModel, &Playlistmodel::previousFile);
		connect(this, &PlaylistGui::currentMediaFile, mpPlListModel, &Playlistmodel::getCurrentFile);
		
		connect(this, &PlaylistGui::setRepeatAll, mpPlListModel, &Playlistmodel::repeatPlaylist);
		
		setLayout(mpVBox);
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
		QStringList listFiles(QFileDialog::getOpenFileNames(0, "Select Files", getHomeDirectory(), getFiltersFormat()));
		if (listFiles.empty())
			return;
		emit addFilesToList(listFiles);
	}
	
	void PlaylistGui::addDirectory() {
		QString path = QFileDialog::getExistingDirectory(0, "Select Directory", getHomeDirectory());
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
		// this whith filters QString path(QFileDialog::getOpenFileName(0, "Open Playlist", getHomeDirectory(), getFiltersFormatLibs()));
		QString path(QFileDialog::getOpenFileName(0, "Open Playlist", getHomeDirectory()));
		if (path.isNull())
			return;
		emit openPlaylistFromFile(path);
	}

	void PlaylistGui::savePlaylist() {
		QString strFilter;
		QString saveFile = QFileDialog::getSaveFileName(0, "Save File", "playlist", getFiltersFormatLibs(), &strFilter);
		if (saveFile.isNull())
			return;
		emit savePlaylistToFile(saveFile);
	}
	
	void PlaylistGui::loadPlaylist() {
		// this whith filters QString path(QFileDialog::getOpenFileName(0, "Open Playlist", getHomeDirectory(), getFiltersFormatLibs()));
		QString path(QFileDialog::getOpenFileName(0, "Open Playlist", getHomeDirectory()));
		if (path.isNull())
			return;
		emit loadPlaylistFromFile(path);
	}

}

