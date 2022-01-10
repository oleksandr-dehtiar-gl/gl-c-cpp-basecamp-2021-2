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
		void searchCommitsForSomeText();
		void selectSearchResultCommit(int index);
	public slots:
		void setModelCommit(std::shared_ptr<ModelCommitTree> model);
		void setModelBranch(std::shared_ptr<ModelBranchList> model);
		void showCommitChanges(const QString& changes);
		void showActiveCommit(const SHA& sha);
		void showActiveBranch(const Branch& branch);
		void commitsThatHaveTextChanges(const std::list<Commit>& commits);
		void showCommitWithFindText(const QString& contain);
	signals:
		void commitForShowChanges(const SHA& sha);
		void makeCheckoutCommit(const SHA& sha);
		void makeCheckoutBranch(Branch branch);
		void findCommitsThatContainText(const QString& text);
		void showCommitWhereFindText(const SHA& sha);
	private:
		void setConnections();
		void createChekoutMenu();
		bool showContextMenu(const QPoint& pos, const QString& menuName);
	private:
		void setColorLine(const QString& line);
		bool skipLine(const QString& line);
		int addseparatorLines(const QString& line);
	private:
		QListView *mptrViewBranches;
		QTreeView *mptrViewCommits;
		QLineEdit *mptrSearchField;
		QComboBox *mptrSearchResult;
		QTextEdit *mptrCommitChanges;
		QLabel *mptrActiveCommit;
		QLabel *mptrActiveBranch;
		QPushButton *mptrFindTextInCommitsButton;
	private:
		std::shared_ptr<ModelCommitTree> mModelCommit;
		std::shared_ptr<ModelBranchList> mBranchModel;
		QString mLastSearchText;
	};
	
}

#endif // VIEWGITWINDOW_HPP
