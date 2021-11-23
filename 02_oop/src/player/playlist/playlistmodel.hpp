#ifndef PLAYLISTMODEL_HPP
#define PLAYLISTMODEL_HPP

#include <QtWidgets>

namespace mediaplayer {
	
	class Playlistmodel : public QAbstractListModel  {
		Q_OBJECT
	private:
		QList<QSharedPointer<QString>> mList;
	public:
		explicit Playlistmodel(QObject *pobj = nullptr);
	public:
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	private:
		void readFilesFromDirRecursive(const std::string &path);
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
	};
	
}

#endif // PLAYLISTMODEL_HPP
