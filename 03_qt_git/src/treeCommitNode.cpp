#include "treeCommitNode.hpp"
#include <iterator>

namespace gitgui {
	
	// TreeCommitNode methods implemantation
	TreeCommitNode::TreeCommitNode(const Commit &commit) 
		: mCommit(commit), mParent(nullptr)
	{
	}
	
	TreeCommitNode::TreeCommitNode(const Commit &commit, const sharedTreeCommitNode &parent) 
		: mCommit(commit), mParent(parent.get())
	{
	}
	
	TreeCommitNode::TreeCommitNode(const Commit &commit, TreeCommitNode *parent) 
		: mCommit(commit), mParent(parent)
	{
	}
	
	sharedTreeCommitNode TreeCommitNode::addChild(const Commit &commit) {
		sharedTreeCommitNode newNode = sharedTreeCommitNode(new TreeCommitNode(commit, this));
		mNodeChilds.push_back(newNode);
		++mChildCount;
		return newNode;
	}
	
	int TreeCommitNode::childCount() const {
		return mChildCount;
	}
	
	sharedTreeCommitNode TreeCommitNode::child(int num) {
		if (mNodeChilds.empty() || (num >= mChildCount))
			return sharedTreeCommitNode{};
		
		auto child = mNodeChilds.begin();
		std::advance(child, num);
		return *child;
	}
	
	int TreeCommitNode::row() {
		auto begin = mParent->mNodeChilds.begin();
		auto end = mParent->mNodeChilds.end();
		int numRow = -1;
		auto itResult = std::find_if(begin, end,
										[&](auto &val) {
										++numRow;
										return val.get() == this;
									});
		return (itResult == end) ? -1 : numRow;
	}

	sharedTreeCommitNode TreeCommitNode::parent() { 
		return std::shared_ptr<TreeCommitNode>(mParent, [](TreeCommitNode*){}); 
	}
	
	const Commit& TreeCommitNode::getCommit() { 
		return mCommit; 
	}
	
	int TreeCommitNode::columnCount() const { 
		return 1; 
	}
	
}
