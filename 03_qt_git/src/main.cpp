#include <QtWidgets>
#include "mainWindow.hpp"

int main(int argc, char **argv) {
#define MAIN_PROG
// #define TEST

#ifdef TEST
	std::cin.get();
	return 0;
#endif

#ifdef MAIN_PROG
	QApplication app(argc, argv);

	gitgui::MainWindow mwin;
	mwin.show();

	return app.exec();
#endif
}
