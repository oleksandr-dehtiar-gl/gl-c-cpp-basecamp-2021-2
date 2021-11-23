#ifndef LIBRARYMODEL_HPP
#define LIBRARYMODEL_HPP

#include <QWidget>
#include <QMediaPlayer>

namespace mediaplayer {
	
	class LibraryModel : public QWidget {
		Q_OBJECT
	public:
		explicit LibraryModel(QWidget *parent = nullptr);
		~LibraryModel() {}
	private:
		void GetMetaData();
	private slots:
		void statusChanged();
	private:
		QMediaPlayer *mPlayer = nullptr;
	};
	
}

#endif // LIBRARYMODEL_HPP