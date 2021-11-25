#include "librarygui.hpp"

namespace mediaplayer {
	
	LibraryGui::LibraryGui(QWidget *pwgt) 
		: QDialog(pwgt)
	{
		mpTableView = new QTableView;
		mpLibraryModel = new LibraryModel;
		mpTableView->setModel(mpLibraryModel);
		QVBoxLayout *mVBoxLayout = new QVBoxLayout;
		mVBoxLayout->addWidget(mpTableView);
		setLayout(mVBoxLayout);
		resize(600, 400);
	}
	
}

