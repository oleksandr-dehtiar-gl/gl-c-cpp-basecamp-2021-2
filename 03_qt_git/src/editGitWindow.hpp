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
	public slots:
		void setIndexFiles(const std::list<IndexFile>& listFile);
	signals:
		void addToIndexingStage(const std::list<IndexFile> &list);
		void removeFromIndexingStage(const std::list<IndexFile> &list);
		void refreshEditWindow();
	private:
		void setConnections();
	public:
		QStringListModel *mpModelIndexedFiles;
		QStringListModel *mpModelNotIndexedFiles;
		QListView *mpViewIndexedFiles;
		QListView *mpViewNotIndexedFiles;
		QPushButton *mpButtonAddAll;
		QPushButton *mpButtonRestoreAll;
		QPushButton *mpButtonRefresh;
	};
	
}

#endif // EDITGITWINDOW_HPP
