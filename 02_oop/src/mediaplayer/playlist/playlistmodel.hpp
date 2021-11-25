#ifndef PLAYLISTMODEL_HPP
#define PLAYLISTMODEL_HPP

#include <QtWidgets>
#include <list>
#include <memory>

#include "../mediadata/mediadata.hpp"

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
		void deleteSelectFiles(QModelIndexList indexList);
		void deleteAllFiles();
		void addFiles(const QStringList &files);
		void addDir(const QString &dirName);

		void savePlaylist(const QString &filename);
		void openPlaylist(const QString &filename);
		void loadPlaylist(const QString &filename);
		
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
