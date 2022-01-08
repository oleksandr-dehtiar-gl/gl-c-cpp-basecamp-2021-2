#ifndef STARTWINDOW_HPP
#define STARTWINDOW_HPP

#include <QtWidgets>
#include <vector>

namespace gitgui {

	struct MenuItem {
		int ID;
		QString title;
	};
	
	class StartWindow : public QWidget {
		Q_OBJECT
	public:
		StartWindow(const std::vector<MenuItem> &container, QWidget *pobj = nullptr);
		StartWindow(const StartWindow&) = delete;
		StartWindow& operator=(const StartWindow&) = delete;
	private slots:
		void refshow(const QString& link);
	signals:
		void lineClicked(int num);
	private:
		template<typename InputIterator>
		void addItemsToMenu(InputIterator begin, InputIterator end, QVBoxLayout *vBox);
	};
	
}

#endif // STARTWINDOW_HPP
