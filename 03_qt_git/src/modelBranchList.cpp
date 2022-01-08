#include "modelBranchList.hpp"

namespace gitgui {
	
	ModelBranchList::ModelBranchList(std::list<Branch> branchList, QObject *pobj) 
		: mBranches{branchList}, QAbstractListModel(pobj)
	{
	}
	
	ModelBranchList::~ModelBranchList() {}
	
	int ModelBranchList::rowCount(const QModelIndex &parent) const {
		return mBranches.size();
	}
	
	QVariant ModelBranchList::data(const QModelIndex &index, int role) const {
		if (!index.isValid())
			return {};
		
		if (index.row() >= mBranches.size())
			return {};
		
		auto iter(mBranches.begin());
		std::advance(iter, index.row());
		auto branchname = *iter;
		QString resultBranchName{branchname.sha() + QString{" --> "} + branchname.name()};
		return (role == Qt::DisplayRole || role == Qt::EditRole) ? resultBranchName : QVariant{};
	}
	
	QVariant ModelBranchList::headerData(int section, Qt::Orientation orientation, int role) const {
		if (role != Qt::DisplayRole)
			return {};
		return (orientation == Qt::Horizontal) ? QString{"Banches"} : QString::number(section);
	}
	
	Branch ModelBranchList::getBranch(const QModelIndex& index) {
		if ((!index.isValid()) || (index.row() >= mBranches.size()))
			return Branch{QString{}, QString{}};

		auto iter(mBranches.begin());
		std::advance(iter, index.row());
		return *iter;
	}
	
}