#include "playlistmodel.hpp"
#include "../../filesysapi/filesysapi.hpp"

#include <iostream>
#include <cassert>

namespace mediaplayer {
	
	Playlistmodel::Playlistmodel(QObject *pobj) 
		: QAbstractListModel(pobj)
	{

	}
	
	// Overload methods
	int Playlistmodel::rowCount(const QModelIndex &parent) const {
		return mList.size();
	}
	
	QVariant Playlistmodel::data(const QModelIndex &index, int role) const {
		if (!index.isValid()) {
			return QVariant();
		}
		QString str;
		str.setNum(index.row());
		return (role == Qt::DisplayRole) ? (str + ". " + *mList.at(index.row())) : QVariant();
	}
	
	// Service methods
	void Playlistmodel::readFilesFromDirRecursive(const std::string &path) {
		std::list<std::string> fList;
		filesysapi::getFileList(fList, path);
		for (auto &str : fList)
			mList << QSharedPointer<QString>(new QString(QString::fromStdString(str)));
	}
	
	// Slots
	void Playlistmodel::deleteSelectFiles(QModelIndexList &indexList) {
		if (indexList.empty())
			return;

		std::sort(indexList.begin(),indexList.end(),
			[](const QModelIndex& a, const QModelIndex& b)->bool{return a.row() < b.row();});

		int modelIndexPos = 0;
		int startsize = mList.size();
		auto iter = mList.begin() + indexList[0].row();
		for (int mListPos = indexList[0].row(); mListPos < startsize; ++mListPos) {
			if (modelIndexPos == indexList.size())
				break;
			if (indexList[modelIndexPos].row() == mListPos) {
				iter = mList.erase(iter);
				++modelIndexPos;
			} else 
				++iter;
		}
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}

	void Playlistmodel::deleteAllFiles() {
		QList<QSharedPointer<QString>>().swap(mList);
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::savePlaylist(QString &filename) {
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream fout(&file);
		for (auto &path : mList)
			fout << (*path) << endl;
		file.close();
	}
	
	void Playlistmodel::openPlaylist(QString &filename) {
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream fin(&file);
		QString line = fin.readLine();
		while (!line.isNull()) {
			mList << QSharedPointer<QString>(new QString(line));
			line = fin.readLine();
		}
		file.close();
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}

	void Playlistmodel::addFiles(QStringList &files) {
		for (auto &file : files)
			mList << QSharedPointer<QString>(new QString(file));
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::addDir(QString &dirName) {
		std::string path = dirName.toStdString();
		readFilesFromDirRecursive(path);
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::loadPlaylist(QString &filename) {
		QList<QSharedPointer<QString>>().swap(mList);
		openPlaylist(filename);
	}
	
}

