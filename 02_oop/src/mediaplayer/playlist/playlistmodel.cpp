#include "playlistmodel.hpp"
#include "../../filesysapi/filesysapi.hpp"

#include <iostream>
#include <iterator>

namespace mediaplayer {
	
	Playlistmodel::Playlistmodel(QObject *pobj) 
		: QAbstractListModel(pobj),
		mRepeatPlaylist(false)
	{
		mIndex = createIndex(0, 0);
	}
	
	// Overload methods
	int Playlistmodel::rowCount(const QModelIndex &parent) const {
		return mList.size();
	}
	
	QVariant Playlistmodel::data(const QModelIndex &index, int role) const {
		if (!index.isValid()) {
			return QVariant();
		}
		auto iter = mList.begin();
		std::advance(iter, index.row());
		switch(role) {
			case Qt::DisplayRole:
				return QString::fromStdString(std::to_string(index.row()) + ". " + (*iter)->name());
			case Qt::BackgroundRole:
				if ((index.row() == mIndex.row()) && (index.column() == mIndex.column()))
					return QBrush(Qt::gray);
				break;
		}
		return QVariant();
	}
	
	// Service methods
	void Playlistmodel::readFromDirRecursive(const std::string &path) {
		filesysapi::pairPath pathpair;
		#define pathname std::get<0>(pathpair)
		try {
			filesysapi::PathManager file(path);
			while (std::get<1>(pathpair = file.nextPath()) != filesysapi::FileType::NO_MORE_FILES) {
				if (std::get<1>(pathpair) == filesysapi::FileType::DIRECTORY) {
					if ((pathname != ".") && (pathname != "..")) {
						readFromDirRecursive(std::string(path + "/" + pathname));
					}
				} else {
					std::shared_ptr<MediaFile> mediafile(facoryMediaFile(path + "/" + pathname));
					if (mediafile)
						mList.push_back(mediafile);
				}
			}
		}
		catch(std::invalid_argument &exc) {
			printf("Non correct Path :%s\n", path.c_str());
		}
		#undef pathname
	}

	// Slots
	void Playlistmodel::deleteSelectFiles(QModelIndexList &indexList) {
		if (indexList.empty())
			return;

		std::sort(indexList.begin(),indexList.end(),
			[](const QModelIndex& a, const QModelIndex& b)->bool{return a.row() < b.row();});

		int modelIndexPos = 0;
		int startsize = mList.size();
		auto iter = mList.begin();
		std::advance(iter, indexList[0].row());
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
		std::list<std::shared_ptr<MediaFile>>().swap(mList);
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::savePlaylist(QString &filename) {
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream fout(&file);
		for (auto &path : mList)
			fout << (QString::fromStdString(path->path())) << endl;
		file.close();
	}
	
	void Playlistmodel::openPlaylist(QString &filename) {
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QTextStream fin(&file);
		QString line = fin.readLine();
		while (!line.isNull()) {
			auto filemedia(facoryMediaFile(line.toStdString()));
			if (filemedia)
				mList.push_back(filemedia);
			line = fin.readLine();
		}
		file.close();
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}

	void Playlistmodel::addFiles(QStringList &files) {
		for (auto &file : files) {
			auto filemedia(facoryMediaFile(file.toStdString()));
			if (filemedia)
				mList.push_back(filemedia);
		}
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::addDir(QString &dirName) {
		std::string path = dirName.toStdString();
		readFromDirRecursive(path);
		emit dataChanged(this->index(0,0), this->index(0,mList.size()));
	}
	
	void Playlistmodel::loadPlaylist(QString &filename) {
		std::list<std::shared_ptr<MediaFile>>().swap(mList);
		openPlaylist(filename);
	}
	
	void Playlistmodel::getIndexFileForPlay(const QModelIndex &index) {
		if (index.isValid()) {
			auto iter = mList.begin();
			std::advance(iter, index.row());
			mIndex = index;
			emit sendFileForPlay(*iter);
		}
	}
	
	void Playlistmodel::getCurrentFile() {
		if (mList.empty())
			return;
		if (mIndex.isValid()) {
			auto iter = mList.begin();
			std::advance(iter, mIndex.row());
			emit sendFileForPlay(*iter);
		}
	}
	
	void Playlistmodel::nextFile() {
		std::shared_ptr<MediaFile> file;
		if (mList.empty()) {
			emit sendFile(file);
			return;
		}
		if (!mIndex.isValid()) {
			mIndex = mIndex.sibling(0, 0);
			file = *mList.begin();
		} else if (mIndex.row() < mList.size() - 1) {
			auto iter = mList.begin();
			std::advance(iter, mIndex.row() + 1);
			mIndex = mIndex.sibling(mIndex.row() + 1, 0);
			file = *iter;
		} else if (mRepeatPlaylist) {
			mIndex = mIndex.sibling(0, 0);
			file = *mList.begin();
		}
		emit sendFile(file);
	}
	
	void Playlistmodel::previousFile() {
		std::shared_ptr<MediaFile> file;
		if (mList.empty()) {
			emit sendFile(file);
			return;
		}
		if (!mIndex.isValid()) {
			mIndex = mIndex.sibling(0, 0);
			file = *mList.begin();
		} else if ((mIndex.row() > 0) && mIndex.row() < mList.size()) {
			auto iter = mList.begin();
			std::advance(iter, mIndex.row() - 1);
			mIndex = mIndex.sibling(mIndex.row() - 1, 0);
			file = *iter;
		}
		emit sendFile(file);
	}
	
	void Playlistmodel::repeatPlaylist(bool repeat) {
		mRepeatPlaylist = repeat;
	}
	
}

