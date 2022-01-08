#ifndef CLONEREPODIALOG_HPP
#define CLONEREPODIALOG_HPP

#include <QtWidgets>

namespace gitgui {
	
	class CloneRepoDialog : public QDialog {
		Q_OBJECT
	public:
		CloneRepoDialog(QWidget *ptrwgt = nullptr);
		CloneRepoDialog(const CloneRepoDialog&) = delete;
		CloneRepoDialog& operator=(const CloneRepoDialog&) = delete;
	public:
		QString getURL() { return mpURL->text(); }
		QString getDir() { return mpDirecotry->text(); }
	private slots:
		void openDirHandler();
	private:
		QLineEdit *mpURL;
		QLineEdit *mpDirecotry;
	};
	
}

#endif // CLONEREPODIALOG_HPP