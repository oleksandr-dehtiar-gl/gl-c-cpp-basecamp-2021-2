#ifndef TREECOMMIT_HPP
#define TREECOMMIT_HPP

#include "gitObjects.hpp"

namespace gitgui {

	class TreeCommitNode;
	using sharedTreeCommitNode = std::shared_ptr<TreeCommitNode>;
	
	class TreeCommitNode {
	public:
		explicit TreeCommitNode(const Commit &commit);
		TreeCommitNode(const Commit &commit, const sharedTreeCommitNode &parent);
		
		TreeCommitNode(const TreeCommitNode &) = delete;
		TreeCommitNode& operator=(const TreeCommitNode &) = delete;
	private:
		TreeCommitNode(const Commit &commit, TreeCommitNode *parent);
	public:
		sharedTreeCommitNode addChild(const Commit &commit);
		sharedTreeCommitNode child(int num);
		sharedTreeCommitNode parent();
		const Commit& getCommit();
		int childCount() const;
		int columnCount() const;
		int row();
	private:
		int mChildCount = 0;
		Commit mCommit;
		TreeCommitNode *mParent;
		std::list<sharedTreeCommitNode> mNodeChilds;
	};
	
}

#endif // TREECOMMIT_HPP
