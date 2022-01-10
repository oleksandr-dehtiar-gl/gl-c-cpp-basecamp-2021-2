#ifndef EDITGITWINDOW_HPP
#define EDITGITWINDOW_HPP

#include <QtWidgets>
#include <list>
#include "gitObjects.hpp"

namespace gitgui {
	
	class EditGitWindow : public QWidget {
		Q_OBJECT
	public:
		EditGitWindow(QWidget *pwgt = nullptr);
	private slots:
		void selectIndexFile(const QModelIndex& index);
		void selectNotIndexFile(const QModelIndex& index);
		void clickedIndexAll();
		void clickedRestoreAll();
		void clickedRefresh();
		void clickedCommit();
		void clickedClearCommit();
		void clickedPush();
		void clickedPull();
	public slots:
		void setIndexFiles(const std::list<IndexFile>& listFile);
		void setStatusMakeCommit(const QString &status);
	signals:
		void addToIndexingStage(const std::list<IndexFile> &list);
		void removeFromIndexingStage(const std::list<IndexFile> &list);
		void refreshEditWindow();
		void makeCommit(const QString &msg);
	private:
		void setConnectionsForIndex();
		void setConnectionsForCommit();
	private:
		QStringListModel *mpModelIndexedFiles;
		QStringListModel *mpModelNotIndexedFiles;
		QListView *mpViewIndexedFiles;
		QListView *mpViewNotIndexedFiles;
	private:
		QTextEdit *mpCommitStatus;
		QTextEdit *mpCommitMsg;
	};
	
}

#endif // EDITGITWINDOW_HPP
