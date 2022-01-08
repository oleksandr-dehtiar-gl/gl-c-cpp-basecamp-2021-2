#include "cloneRepoDialog.hpp"

namespace gitgui {
	
	CloneRepoDialog::CloneRepoDialog(QWidget *ptrwgt)
		: QDialog(ptrwgt)
	{
		mpURL = new QLineEdit;
		mpDirecotry = new QLineEdit;
		QAction *mpOpenDirAction = mpDirecotry->addAction(QIcon("icon/opendir.png"), QLineEdit::TrailingPosition);
		connect(mpOpenDirAction, &QAction::triggered, this, &CloneRepoDialog::openDirHandler);

		QLabel *pLblURL = new QLabel("&URL");
		
		QLabel *pLblDirecoty = new QLabel("&Directory");
		
		pLblURL->setBuddy(mpURL);
		pLblDirecoty->setBuddy(mpDirecotry);
		
		QPushButton *pOK = new QPushButton("&OK");
		QPushButton *pCancel = new QPushButton("&Cancel");
		
		connect(pOK, SIGNAL(clicked()), SLOT(accept()));
		connect(pCancel, SIGNAL(clicked()), SLOT(reject()));
		
		// Layout setup
		QGridLayout *pGridLayer = new QGridLayout;
		pGridLayer->addWidget(pLblURL, 0, 0);
		pGridLayer->addWidget(mpURL, 0, 1);
		pGridLayer->addWidget(pOK, 2, 0);
		pGridLayer->addWidget(pLblDirecoty, 1, 0);
		pGridLayer->addWidget(mpDirecotry, 1, 1);
		pGridLayer->addWidget(pCancel, 2, 1);
		
		setLayout(pGridLayer);
		this->setMinimumWidth(400);
		this->adjustSize();
		this->setFixedHeight(this->size().height());
	}
	
	void CloneRepoDialog::openDirHandler() {
		QTextStream out(stdout);
		QString path = QFileDialog::getExistingDirectory(0, "Select Directory", ".");
		if (!path.isEmpty())
			mpDirecotry->setText(path);
	}
	
}