#include "fileSysApi.hpp"

#include "fileWinSysApi.hpp"

namespace filesysapi {
	
	DirContainer::DirContainer(const std::string &path)
		: mHandler(new FileHandler(path + "\\*"))
	{
	}
	
	nameType_pr DirContainer::nextFile() {
		if (!mHandler->nextFile()) {
			return std::move(std::make_pair(std::string(), FileType::NO_MORE_FILES));
		}
		return std::move(std::make_pair(std::string(mHandler->fileName()), 
							(mHandler->fileAttrib() == FILE_ATTRIBUTE_DIRECTORY) ? FileType::DIRECTORY : FileType::FILE));
	}
	
	void DirContainer::newPath(const std::string &path) {
		mHandler->setNewPath(path + "\\*");
	}
	
	DirContainer::operator bool() const {
		return mHandler->isValid();
	}
	
}

