#ifndef MODELBRANCHLIST_HPP
#define MODELBRANCHLIST_HPP

#include <QtWidgets>
#include "gitObjects.hpp"

namespace gitgui {
	
	class ModelBranchList : public QAbstractListModel {
		Q_OBJECT
	public:
		explicit ModelBranchList(std::list<Branch> branchList, QObject *pobj = nullptr);
		virtual ~ModelBranchList() override;
		ModelBranchList(const ModelBranchList&) = delete;
		ModelBranchList& operator=(const ModelBranchList&) = delete;
	private:
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	public:
		Branch getBranch(const QModelIndex& index);
	private:
		std::list<Branch> mBranches;
	};
	
}

#endif // MODELBRANCHLIST_HPP
