#include <iostream>
#include <QtWidgets>

#include "process.hpp"
#include "startWindow.hpp"
#include "mainWindow.hpp"
#include "viewGitWindow.hpp"
#include "treeCommitNode.hpp"

#include <iterator>

void printCommits(gitgui::sharedTreeCommitNode node, int level = 0) {
	QTextStream out(stdout);
	for (int j = 0; j < level; ++j)
		out << " ";
	out << node->getCommit().sha() << endl;
	for (int i = 0; i < node->childCount(); ++i) {
		if (node->child(i))
			printCommits(node->child(i), level + 1);
	}
}

void testPath(const QString& path) {
	QTextStream out(stdout);
	QDir TestDir(path);
	QString resultpath;
	resultpath = path;
	//resultpath = TestDir.cleanPath(TestDir.absoluteFilePath("icon"));
	out << endl << "Path: " << resultpath << endl;
	if (TestDir.isAbsolute()) out << "Absolute" << endl;
	if (TestDir.isRelative()) out << "Relative" << endl;
	if (TestDir.exists()) {
		out << "Exists" << endl;
		out << "Absolute path: " << TestDir.absolutePath() << endl;
	}
	else 
		out << "No Exists" << endl;
	
}


int main(int argc, char **argv) {
#define MAIN_PROG
// #define TEST

#ifdef TEST
	QTextStream out(stdout);
	QString test1{"e:\\edication\\basecamp\\task\\task3\\03_qt_git\\src\\"};
	QString test2{"e:\\edication\\hefdsa"};
	QString test3{"icon"};
	QString test4{"test"};
	QString test5{"edication\\hefdsa"};
	
	testPath(test1);
	testPath(test2);
	testPath(test3);
	testPath(test4);
	testPath(test5);
	//////////////////////////////
	// QString url{"https://github.com/AndreiBarishnichenko87/CNCMachinSimulator.git"};
	// QStringList args;
	// args << "clone";
	// args << url;
	// QString resultCommits{gitgui::Process(QString{"git"}, args).run()};
	// out << "OUTPUT ==============================" << endl << resultCommits << endl;
	
	std::cin.get();
	return 0;
#endif

#ifdef MAIN_PROG
	QApplication app(argc, argv);
	
	// gitgui::Process cmd;
	// cmd.setWorkDirectory(QString("."));
	// QTextStream out(stdout);
	// out << cmd.run(QString("cmd"), QStringList() << "/c" << "dir") << endl;
	// cmd.setWorkDirectory(QString(".."));
	// out << cmd.run() << endl;

	gitgui::MainWindow mwin;
	mwin.show();

	return app.exec();
#endif
}
