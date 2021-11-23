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
		Playlistmodel mPlListModel;
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
		void deleteSelectFiles(QModelIndexList &indexList);
		void deleteAllFiles();
		void addFilesToList(QStringList &files);
		void addDirToList(QString &dirName);
		
		void savePlaylistToFile(QString &filename);
		void openPlaylistFromFile(QString &filename);
		void loadPlaylistFromFile(QString &filename);
		
	};
	
}

#endif // PLAYILISTGUI_HPP
