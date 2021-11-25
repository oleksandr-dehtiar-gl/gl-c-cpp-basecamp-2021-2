#ifndef LIBRARYGUI_HPP
#define LIBRARYGUI_HPP

#include <QtWidgets>
#include "librarymodel.hpp"

namespace mediaplayer {

	class LibraryGui : public QDialog {
		Q_OBJECT
	public:
		LibraryGui(QWidget *pwgt = nullptr);
	private:
		LibraryModel *mpLibraryModel;
		QTableView *mpTableView;
	};

}

#endif // LIBRARYGUI_HPP
