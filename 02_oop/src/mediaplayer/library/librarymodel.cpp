#include "librarymodel.hpp"

namespace mediaplayer {
	
	constexpr char* headNames[] {"Name", "Title", "Genre", "Year"};
	
	LibraryModel::LibraryModel(QObject *qobj) 
		: QAbstractTableModel(qobj)
	{
		
	}
	
	QVariant LibraryModel::data(const QModelIndex& index, int Role) const {
		if (!index.isValid())
			return QVariant();
		if ((index.column() > sizeTupleAudio()) || (index.row() > mAudioList.size()))
			return QVariant();
		
		switch(Role) {
			case Qt::DisplayRole:
				auto iter = mAudioList.begin();
				std::advance(iter, index.row());
				switch (index.column()) {
					case 0: return QString::fromStdString(std::get<0>(*iter)->name());
					case 1: return QString::fromStdString(std::get<1>(*iter));
					case 2: return QString::fromStdString(std::get<2>(*iter));
					case 3: return QString::fromStdString(std::get<3>(*iter));
				}
		}
		return QVariant();
	}
	
	int LibraryModel::rowCount(const QModelIndex& index) const {
		return mAudioList.size();
	}
	
	int LibraryModel::columnCount(const QModelIndex& index) const {
		return sizeTupleAudio();
	}
	
	QVariant LibraryModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const {
		
		switch(nRole) {
			case Qt::DisplayRole:
				if (nSection < sizeTupleAudio() && orientation == Qt::Horizontal)
					return QString(headNames[nSection]);
		}
		return QVariant();
	}
	
	
	
}
