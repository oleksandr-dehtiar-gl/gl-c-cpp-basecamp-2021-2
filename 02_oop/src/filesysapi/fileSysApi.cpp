#include "fileSysApi.hpp"
#ifdef _WIN32
	#include "fileWinSysApi.hpp"
#endif // _WIN32

#ifdef __linux__
	#include "fileUnixSysApi.hpp"
#endif // __linux__

#include <cstdio>

namespace filesysapi {
	
	std::string getAbsolutePath(const pairPath& path) {
		return std::move(absolutePath(std::get<0>(path)));
	}
	std::string getAbsolutePath(const std::string& path) {
		return std::move(absolutePath(path));
	}
	
	std::string getFilenamePart(const std::string& path) {
		if (path.empty())
			return std::string();
		std::size_t found = path.find_last_of("/\\");
		return std::move(path.substr(found+1));
	}
	std::string getFilenamePart(const pairPath& path) {
		return std::move(getFilenamePart(std::get<0>(path)));
	}
	
	std::string getPathnamePart(const std::string& path) {
		if (path.empty())
			return std::string();
		std::size_t found = path.find_last_of("/\\");
		return std::move(path.substr(0,found));
	}
	std::string getPathnamePart(const pairPath& path) {
		return std::move(getPathnamePart(std::get<0>(path)));
	}
	
	std::string getFileExtension(const std::string path) {
		if (path.empty())
			return std::string();
		std::size_t found = path.find_last_of(".");
		return (found == std::string::npos) ? std::string() : std::move(path.substr(found + 1));
	}
	
	std::string getFileExtension(const pairPath& path) {
		return std::move(getFileExtension(getFilenamePart(std::get<0>(path))));
	}
	
	std::string getFileNameWihtoutExtens(const std::string& path) {
		if (path.empty())
			return std::string();
		std::string name(getFilenamePart(path));
		if (name.empty())
			return std::string();
		std::size_t found = name.find_last_of(".");
		return (found == std::string::npos) ? name : std::move(name.substr(0, found)) ;
	}
	
	size_t getFileList(std::list<std::string> &fileList, const std::string &path) {
		size_t numberOfElement = 0;
		pairPath pathpair;
		std::string &pathName = std::get<0>(pathpair);
		try {
			PathManager d(path);
			while (std::get<1>(pathpair = d.nextPath()) != FileType::NO_MORE_FILES) {
				if (std::get<1>(pathpair) == FileType::DIRECTORY) {
					if ((pathName != ".") && (pathName != "..")) {
						numberOfElement += getFileList(fileList, std::string(path + "/" + pathName));
					}
				} else {
					fileList.push_back(path + "/" + pathName);
					++numberOfElement;
				}
			}
		}
		catch(std::invalid_argument &exc) {
			printf("Uncorrected path :%s\n", path.c_str());
			return numberOfElement;
		}
		return numberOfElement;
	}
	

	PathManager::PathManager(const std::string &path)
		: mHandler(new FileHandler(path + "/"))
	{
	}
	
	pairPath PathManager::nextPath() {
		if (!mHandler->nextPath()) {
			return std::move(std::make_pair(std::string(), FileType::NO_MORE_FILES));
		}
		return std::move(std::make_pair(std::string(mHandler->fileName()), 
							mHandler->isDirectory() ? FileType::DIRECTORY : FileType::FILE));
	}
	
	void PathManager::newPath(const std::string &path) {
		mHandler->setNewPath(path + "/*");
	}
	
	PathManager::operator bool() const {
		return mHandler->isValid();
	}
	
}

