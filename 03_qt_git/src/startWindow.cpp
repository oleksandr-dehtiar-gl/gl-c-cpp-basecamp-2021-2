#include "startWindow.hpp"
#include <iostream>

namespace gitgui {
	
	StartWindow::StartWindow(const std::vector<MenuItem> &container, QWidget *pobj)
		: QWidget(pobj)
	{
		// Set empty space above menu text list
		int vBorderSpace = 20;
		QVBoxLayout *vBoxLblList = new QVBoxLayout;
		vBoxLblList->addSpacing(vBorderSpace);
		
		// Add menu Iteam to vertical box layout
		addItemsToMenu(container.begin(), container.end(), vBoxLblList);

		// Set empty space under menu text list
		vBoxLblList->addSpacing(vBorderSpace);
		
		// Set menu in center of the widget
		int hBorderSpace = 70;
		QHBoxLayout *hbox = new QHBoxLayout;
		hbox->addSpacing(hBorderSpace);
		hbox->addLayout(vBoxLblList);
		hbox->addSpacing(hBorderSpace);
		
		setLayout(hbox);
		this->adjustSize();
		this->setFixedSize(this->size());
	}

	void StartWindow::refshow(const QString& link) {
		int lineNumber = link.toInt();
		emit lineClicked(lineNumber);
	}
	
	template<typename InputIterator>
	void StartWindow::addItemsToMenu(InputIterator begin, InputIterator end, QVBoxLayout *vBox) {
		QString beginUrl("<a href=\"");
		QString endUrl("\">");
		QString endUrlLine("</a>");
		
		while (begin != end) {
			// Save ID in each menu line
			QString menuLine = beginUrl + QString::number(begin->ID) + endUrl + begin->title + endUrlLine;
			// Add new Label to menu widget
			QLabel *newLbl = new QLabel(menuLine);
			vBox->addWidget(newLbl);
			connect(newLbl, &QLabel::linkActivated, this, &StartWindow::refshow);
			++begin;
		}
	}
	
}
