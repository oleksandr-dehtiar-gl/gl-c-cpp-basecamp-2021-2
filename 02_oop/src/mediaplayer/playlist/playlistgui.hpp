#ifndef PLAYILISTGUI_HPP
#define PLAYILISTGUI_HPP

#include <QtWidgets>
#include "playlistmodel.hpp"

namespace mediaplayer {
	
	class PlaylistGui : public QDialog {
		Q_OBJECT
	public:
		PlaylistGui(QWidget *pwgt = nullptr);
	private:
		Playlistmodel *mpPlListModel = nullptr;
		QListView *mpListView = nullptr;
		QItemSelectionModel *mpSelectModel = nullptr;
	private:
		QHBoxLayout *mpHBox_1 = nullptr;
		QHBoxLayout *mpHBox_2 = nullptr;
		QVBoxLayout *mpVBox = nullptr;
	private:
		QMenuBar *mpAddMenuBar = nullptr;
		QMenu *mpAddMenu = nullptr;
		QMenuBar *mpDelMenuBar = nullptr;
		QMenu *mpDelMenu = nullptr;
		QMenuBar *mpPllistMenuBar = nullptr;
		QMenu *mpPllistMenu = nullptr;
	private:
		QAction *mpAddFile = nullptr;
		QAction *mpAddDirectoy = nullptr;
		QAction *mpAddPlaylist = nullptr;
		QAction *mpDeleteFiles = nullptr;
		QAction *mpClearPlaylist = nullptr;
		QAction *mpLoadPlaylist = nullptr;
		QAction *mpSavePlaylist = nullptr;
	private:
		void addActions();
		void createMenus();
	private slots:
		void addFiles();
		void addDirectory();
		void addPlaylist();
		
		void removeSelectFiles();
		void removeAllFiles();
		
		void savePlaylist();
		void loadPlaylist();
	signals:
		void deleteSelectFiles(QModelIndexList&);
		void deleteAllFiles();
		void addFilesToList(QStringList&);
		void addDirToList(QString&);
		
		void savePlaylistToFile(QString&);
		void openPlaylistFromFile(QString&);
		void loadPlaylistFromFile(QString&);
		
		void currentMediaFile();
		void nextMediFile();
		void previosMediFile();
		void getMediaFileForPlay(std::shared_ptr<MediaFile>);
		void getMediaFile(std::shared_ptr<MediaFile>);
		
		void setRepeatAll(bool);
	};
	
}

#endif // PLAYILISTGUI_HPP
