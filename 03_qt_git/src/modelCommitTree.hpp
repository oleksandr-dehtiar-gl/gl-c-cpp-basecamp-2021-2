#ifndef MODELCOMMITTREE_HPP
#define MODELCOMMITTREE_HPP

#include <QtWidgets>
#include "treeCommitNode.hpp"

namespace gitgui {
	
	class ModelCommitTree : public QAbstractItemModel {
		Q_OBJECT
	public:
		explicit ModelCommitTree(const sharedTreeCommitNode &rootTreeCommit, QObject *pobj = nullptr);
		virtual ~ModelCommitTree() override;
		ModelCommitTree(const ModelCommitTree&) = delete;
		ModelCommitTree& operator=(const ModelCommitTree&) = delete;
	private:
		virtual QModelIndex index(int row, int column, const QModelIndex& index) const override;
		virtual QModelIndex parent(const QModelIndex &index) const override;
		virtual int rowCount(const QModelIndex &parent) const override;
		virtual int columnCount(const QModelIndex &index) const override;
		virtual QVariant data(const QModelIndex &index, int Role) const override;
		QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
	public:
		Commit getCommit(const QModelIndex& index);
	private:
		sharedTreeCommitNode mRootTreeCommit;
	};
	
}

#endif // MODELCOMMITTREE_HPP