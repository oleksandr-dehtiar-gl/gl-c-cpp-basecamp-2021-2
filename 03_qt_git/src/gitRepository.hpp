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
	public slots:
		void commitForShowChanges(const SHA& sha);
		void makeCheckout(const SHA& sha);
	signals:
		void setModelCommit(std::shared_ptr<ModelCommitTree> model);
		void setModelBranch(std::shared_ptr<ModelBranchList> model);
		void showCommitChanges(const QString& changes);
		void showActiveCommit(const SHA& sha);
		void showActiveBranch(const Branch& branch);
	private:
		std::shared_ptr<ModelCommitTree> getCommitModelPtr();
		std::shared_ptr<ModelBranchList> getBranchModelList();
	private:
		GitApi mGitApi;
		QString mPath;
	};
	
}

#endif // GITREPOSITORY_HPP