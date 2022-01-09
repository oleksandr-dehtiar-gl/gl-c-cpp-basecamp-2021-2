#ifndef VIEWGITWINDOW_HPP
#define VIEWGITWINDOW_HPP

#include <QtWidgets>
#include "modelCommitTree.hpp"
#include "modelBranchList.hpp"

namespace gitgui {
	
	class ViewGitWindow : public QFrame {
		Q_OBJECT
	public:
		ViewGitWindow(QWidget *ptrwgt = nullptr);
		ViewGitWindow(const ViewGitWindow&) = delete;
		ViewGitWindow& operator=(const ViewGitWindow&) = delete;
	private slots:
		void getSHACommit(const QModelIndex &index);
		void getSHABranch(const QModelIndex &index);
		void checkoutCommit(const QPoint& pos);
		void checkoutBranch(const QPoint& pos);
	public slots:
		void setModelCommit(std::shared_ptr<ModelCommitTree> model);
		void setModelBranch(std::shared_ptr<ModelBranchList> model);
		void showCommitChanges(const QString& changes);
		void showActiveCommit(const SHA& sha);
		void showActiveBranch(const Branch& branch);
	signals:
		void commitForShowChanges(const SHA& sha);
		void makeCheckoutCommit(const SHA& sha);
		void makeCheckoutBranch(Branch branch);
	private:
		void createChekoutMenu();
		bool showContextMenu(const QPoint& pos, const QString& menuName);
	private:
		QListView *mptrViewBranches;
		QTreeView *mptrViewCommits;
		QLineEdit *mptrSearchField;
		QLineEdit *mptrSearchResult;
		QTextEdit *mptrCommitChanges;
		QLabel *mptrActiveCommit;
		QLabel *mptrActiveBranch;
	private:
		std::shared_ptr<ModelCommitTree> mModelCommit;
		std::shared_ptr<ModelBranchList> mBranchModel;
	};
	
}

#endif // VIEWGITWINDOW_HPP
