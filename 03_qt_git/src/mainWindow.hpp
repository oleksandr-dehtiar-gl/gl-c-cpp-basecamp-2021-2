#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets>
#include <memory>

#include "startWindow.hpp"
#include "viewGitWindow.hpp"
#include "gitRepository.hpp"

namespace gitgui {
	
	enum StartMenuType {
		MOVE_TO_REPO = 52,
		CLONE_NEW_REPO = 5,
		UNDEFINE_TEST = 8
	};
	
	class MainWindow : public QMainWindow {
		Q_OBJECT
	public:
		MainWindow(QWidget *wgtptr = nullptr);
	private:
		void createStartMenuWindow();
		void createMainRepoWindow();
		void fixedCentralWgt(const QSize& size);
		void relaxCentralWgt();
		void createRepository(const QString& path);
		void cloneNewRepository();
		void gitViewRepoConnections();
	private slots:
		void handleStartMenuSelectItem(int menuType);
	private:
		StartWindow *mptrStartWindow = nullptr;
		ViewGitWindow *mptrViewWindow = nullptr;
		QTabWidget *mptrTab = nullptr;
		std::shared_ptr<GitRepository> mGitRepo;
	};
	
}

#endif // MAINWINDOW_HPP