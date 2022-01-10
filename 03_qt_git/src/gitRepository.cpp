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
		emit setIndexFiles(mGitApi.getIndexFilesList());
	}
	
	void GitRepository::commitForShowChanges(const SHA& sha) {
		emit showCommitChanges(mGitApi.commitChanges(sha));
	}
	
	void GitRepository::makeCheckoutCommit(const SHA& sha) {
		mGitApi.checkout(sha);
		emit showActiveCommit(mGitApi.getActiveCommit());
		emit showActiveBranch(mGitApi.getActiveBranch());
		emit setModelBranch(getBranchModelList());
	}
	
	void GitRepository::makeCheckoutBranch(Branch branch) {
		mGitApi.checkout(branch);
		emit showActiveCommit(mGitApi.getActiveCommit());
		emit showActiveBranch(mGitApi.getActiveBranch());
		emit setModelBranch(getBranchModelList());
	}
	
	QString GitRepository::cloneRepository(const QString& url, const QString& path) {
		return GitApi::cloneRepository(url, path);
	}
	
	void GitRepository::findCommitsThatContainText(const QString& text) {
		auto listCommit{mGitApi.getCommitsWhenTextChanged(text)};
		if (listCommit.empty())
			return;
		emit commitsThatHaveTextChanges(listCommit);
	}

	void GitRepository::showCommitWhereFindText(const SHA& sha) {
		emit showCommitWithFindText(mGitApi.commitChanges(sha));
	}
	
	void GitRepository::addToIndexingStage(const std::list<IndexFile> &list) {
		if (list.empty()) 
			return;
		mGitApi.addToIndexStage(list);
		emit setIndexFiles(mGitApi.getIndexFilesList());
	}
	
	void GitRepository::removeFromIndexingStage(const std::list<IndexFile> &list) {
		if (list.empty())
			return;
		mGitApi.removeFromIndexStage(list);
		emit setIndexFiles(mGitApi.getIndexFilesList());
	}
	
	void GitRepository::refreshEditWindow() {
		emit setIndexFiles(mGitApi.getIndexFilesList());
	}
	
	void GitRepository::makeCommit(const QString &msg) {
		auto statusResult{mGitApi.makeCommit(msg)};
		if (statusResult.isEmpty())
			return;
		startInitVeiwWindow();
		emit setStatusMakeCommit(statusResult);
	}
	
}
