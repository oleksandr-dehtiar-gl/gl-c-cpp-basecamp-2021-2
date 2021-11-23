#ifndef FILESYSAPI_HPP
#define FILESYSAPI_HPP

#include <string>
#include <utility>
#include <memory>
#include <list>

namespace filesysapi {
	
	enum FileType : uint8_t {
		NO_MORE_FILES = 0,
		DIRECTORY,
		FILE
	};

	typedef std::pair<std::string, FileType> pairPath;
	
	// public method path manipulator
	std::string getAbsolutePath(const pairPath& path);
	std::string getAbsolutePath(const std::string& path);
	
	std::string getFilenamePart(const pairPath& path);
	std::string getFilenamePart(const std::string& path);
	
	std::string getPathnamePart(const pairPath& path);
	std::string getPathnamePart(const std::string& path);
	
	std::string getFileExtension(const pairPath& path);
	std::string getFileExtension(const std::string fileName);
	
	size_t getFileList(std::list<std::string> &fileList, const std::string &path);
	
	class FileHandler;
	
	class PathManager {
		std::shared_ptr<FileHandler> mHandler;
	public:
		explicit PathManager(const std::string &path);
	public:
		operator bool() const;
		pairPath nextPath();
		void newPath(const std::string &path);
	};

}

#endif // FILESYSAPI_HPP
