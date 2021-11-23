#include "librarymodel.hpp"

#include <iostream>

#define print std::cout << "DEBUG" << std::endl

namespace mediaplayer {
	
	LibraryModel::LibraryModel(QWidget *parent)
		: QWidget(parent)
	{
		mPlayer = new QMediaPlayer(this);
		connect(mPlayer, QOverload<>::of(&QMediaObject::metaDataChanged), this, &LibraryModel::statusChanged);
		mPlayer->setMedia(QUrl::fromLocalFile("ID3.mp3"));
		mPlayer->setVolume(50);
		mPlayer->play();
	}
	
	void LibraryModel::statusChanged() {
		print;
		if (mPlayer->isMetaDataAvailable()) {
			GetMetaData();
		} else {
			std::cout << "No metadata\n";
		}
	}
	
	void LibraryModel::GetMetaData() {
		QStringList metadatalist = mPlayer->availableMetaData();
		int list_size = metadatalist.size();
		std::cout << "size list: " << list_size << std::endl;
	}
	
}
