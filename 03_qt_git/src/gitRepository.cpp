#include "gitRepository.hpp"

namespace gitgui {
	
	static void buildCommitTree(QList<QStringList> &commitTree, const QString &commit, sharedTreeCommitNode &currTreeCommitNode);
	
	GitRepository::GitRepository(const QString &path) 
		: mGitApi(path), mPath(path)
	{
	}
	
	std::shared_ptr<ModelBranchList> GitRepository::getBranchModelList() {
		return std::shared_ptr<ModelBranchList>(new ModelBranchList(mGitApi.branchList()));
	}

	std::shared_ptr<ModelCommitTree> GitRepository::getCommitModelPtr() {
		return std::shared_ptr<ModelCommitTree>(new ModelCommitTree(mGitApi.getRootCommitTree()));
	}
	
	void GitRepository::startInitVeiwWindow() {
		emit setModelCommit(getCommitModelPtr());
		emit setModelBranch(getBranchModelList());
		emit showActiveCommit(mGitApi.getActiveCommit());
		emit showActiveBranch(mGitApi.getActiveBranch());
	}
	
	void GitRepository::commitForShowChanges(const SHA& sha) {
		emit showCommitChanges(mGitApi.commitChanges(sha));
	}
	
	void GitRepository::makeCheckoutCommit(const SHA& sha) {
		mGitApi.checkout(sha);
		Branch activeBranch{mGitApi.getActiveBranch()};
		
		emit showActiveCommit(mGitApi.getActiveCommit());
		emit showActiveBranch(activeBranch);
		// ...
		emit setModelBranch(getBranchModelList());
	}
	
	void GitRepository::makeCheckoutBranch(Branch branch) {
		mGitApi.checkout(branch);
		emit showActiveCommit(mGitApi.getActiveCommit());
		emit showActiveBranch(mGitApi.getActiveBranch());
		// ...
		emit setModelBranch(getBranchModelList());
	}
	
	QString GitRepository::cloneRepository(const QString& url, const QString& path) {
		return GitApi::cloneRepository(url, path);
	}
	
}
