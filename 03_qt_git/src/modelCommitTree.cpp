#include "modelCommitTree.hpp"

namespace gitgui {

	// Implementation ModelCommitTree methods	
	ModelCommitTree::ModelCommitTree(const sharedTreeCommitNode &rootTreeCommit, QObject *pobj) 
		: QAbstractItemModel(pobj), mRootTreeCommit(rootTreeCommit)
	{
		
	}

	ModelCommitTree::~ModelCommitTree() {}

	// Overload model function
	QModelIndex ModelCommitTree::index(int row, int column, const QModelIndex& index) const {
		TreeCommitNode *parent;
		if (!index.isValid())
			parent = mRootTreeCommit.get();
		else
			parent = static_cast<TreeCommitNode*>(index.internalPointer());

		if (!parent)
			return QModelIndex();

		sharedTreeCommitNode children = parent->child(row);
		if (children)
			return createIndex(row, column, children.get());

		return QModelIndex();
	}

	QModelIndex ModelCommitTree::parent(const QModelIndex &index) const {
		if (!index.isValid())
			return QModelIndex();

		TreeCommitNode *child = static_cast<TreeCommitNode*>(index.internalPointer());
		sharedTreeCommitNode parent = child->parent(); 

		if ((parent == mRootTreeCommit) || !parent)
			return QModelIndex();
		
		return createIndex(parent->row(), 0, parent.get());
	}

	int ModelCommitTree::rowCount(const QModelIndex &parent) const {
		TreeCommitNode *parentIteam;
		if (parent.column() > 0)
			return 0;
		if (!parent.isValid())
			parentIteam = mRootTreeCommit.get();
		else
			parentIteam = static_cast<TreeCommitNode*>(parent.internalPointer()); 
		return	parentIteam->childCount(); 
	}

	int ModelCommitTree::columnCount(const QModelIndex &index) const {
		if (index.isValid())
			return static_cast<TreeCommitNode*>(index.internalPointer())->columnCount();
		return mRootTreeCommit->columnCount();
	}

	QVariant ModelCommitTree::data(const QModelIndex &index, int Role) const {
		if (index.isValid() && Role != Qt::DisplayRole) 
			return QVariant();
		TreeCommitNode *parent = static_cast<TreeCommitNode*>(index.internalPointer());
		if (!parent)
			return QString();
		return parent->getCommit().sha();
	}

	QVariant ModelCommitTree::headerData(int nSection, Qt::Orientation orientation, int nRole) const {
		if (nRole != Qt::DisplayRole) 
			return QVariant();
		return (orientation == Qt::Horizontal) ? QString("Commits") : QString::number(nSection);
	}

	Commit ModelCommitTree::getCommit(const QModelIndex& index) {
		Commit{QString{}};
		if (!index.isValid())
			return Commit{QString{}};

		TreeCommitNode *commitNode = static_cast<TreeCommitNode*>(index.internalPointer());
		if (!commitNode) 
			return Commit{QString{}};
		if (!commitNode->parent())
			return Commit{QString{}};

		Commit indexCommit(commitNode->getCommit());
		if (indexCommit.sha() == allCommit || indexCommit.sha() == treeCommit)
			return Commit{QString{}};
		return indexCommit;
	}
}