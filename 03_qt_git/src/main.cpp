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

int main(int argc, char **argv) {
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
}
