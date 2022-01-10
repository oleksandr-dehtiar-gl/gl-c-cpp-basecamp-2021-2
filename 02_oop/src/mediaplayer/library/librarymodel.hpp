#ifndef LIABRARYMODEL_HPP
#define LIABRARYMODEL_HPP

#include <QtWidgets>
#include <vector>
#include <list>
#include <memory>
#include <tuple>

#include "../mediadata/mediadata.hpp"

namespace mediaplayer {
	
	class LibraryModel : public QAbstractTableModel {
		Q_OBJECT
		typedef typename std::tuple<std::shared_ptr<MediaFile>, std::string, std::string, std::string> mtFileTitleGenreYear;
		typedef typename std::list<mtFileTitleGenreYear>::iterator iterAudioList;
		typedef typename std::list<mtFileTitleGenreYear>::iterator iterVideoList;
	private:
		constexpr int sizeTupleAudio() const { return std::tuple_size<mtFileTitleGenreYear>::value; }
		constexpr int sizeTupleVideo() const { return std::tuple_size<mtFileTitleGenreYear>::value; }
	public:
		LibraryModel(QObject *qobj = nullptr);
	public:
		QVariant data(const QModelIndex& index, int Role) const;
		int rowCount(const QModelIndex& index) const;
		int columnCount(const QModelIndex& index) const;
		QVariant headerData(int nSection, Qt::Orientation orientation, int nRole) const;
	private:
		std::list<mtFileTitleGenreYear> mAudioList;
		std::list<mtFileTitleGenreYear> mVideoList;
	};
	
}

#endif // LIABRARYMODEL_HPP
