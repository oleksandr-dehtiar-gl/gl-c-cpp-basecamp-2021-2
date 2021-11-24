#ifndef PLAYLISTMODEL_HPP
#define PLAYLISTMODEL_HPP

#include <QtWidgets>
#include <list>
#include <memory>

#include "../mediadata/mediadata.hpp" // define default directory for search files and search filters for files and libraries

namespace mediaplayer {
	
	class Playlistmodel : public QAbstractListModel  {
		Q_OBJECT
	private:
		std::list<std::shared_ptr<MediaFile>> mList;
		QModelIndex mIndex;
		bool mRepeatPlaylist;
	public:
		explicit Playlistmodel(QObject *pobj = nullptr);
	public:
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	private:
		void readFromDirRecursive(const std::string &path);
	public slots:
		// Good
		void deleteSelectFiles(QModelIndexList &indexList);
		void deleteAllFiles();
		void addFiles(QStringList &files);
		void addDir(QString &dirName);

		// Not good
		void savePlaylist(QString &filename);
		void openPlaylist(QString &filename);
		void loadPlaylist(QString &filename);
		
		void getIndexFileForPlay(const QModelIndex &index);
		void nextFile();
		void previousFile();
		void getCurrentFile();
		void repeatPlaylist(bool repeat);
	signals:
		void sendFileForPlay(std::shared_ptr<MediaFile>);
		void sendFile(std::shared_ptr<MediaFile>);
	};
	
}

#endif // PLAYLISTMODEL_HPP
