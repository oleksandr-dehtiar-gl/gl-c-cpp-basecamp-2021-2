#ifndef GITREPOSITORY_HPP
#define GITREPOSITORY_HPP

#include <QtWidgets>

#include "gitapi.hpp"
#include "gitObjects.hpp"
#include "modelCommitTree.hpp"
#include "modelBranchList.hpp"

namespace gitgui {

	class GitRepository : public QObject {
		Q_OBJECT
	public:
		explicit GitRepository(const QString &pathRepo);
		GitRepository(const GitRepository&) = delete;
		GitRepository& operator=(const GitRepository&) = delete;
	public:
		void startInitVeiwWindow();
		static QString cloneRepository(const QString& url, const QString& path);
	public slots:
		void commitForShowChanges(const SHA& sha);
		void makeCheckoutCommit(const SHA& sha);
		void makeCheckoutBranch(Branch branch);
		void findCommitsThatContainText(const QString& text);
		void showCommitWhereFindText(const SHA& sha);
	signals:
		void setModelCommit(std::shared_ptr<ModelCommitTree> model);
		void setModelBranch(std::shared_ptr<ModelBranchList> model);
		void showCommitChanges(const QString& changes);
		void showActiveCommit(const SHA& sha);
		void showActiveBranch(const Branch& branch);
		void commitsThatHaveTextChanges(const std::list<Commit>& commits);
		void showCommitWithFindText(const QString& contain);
	private:
		std::shared_ptr<ModelCommitTree> getCommitModelPtr();
		std::shared_ptr<ModelBranchList> getBranchModelList();
	private:
		GitApi mGitApi;
		QString mPath;
	};
	
}

#endif // GITREPOSITORY_HPP
