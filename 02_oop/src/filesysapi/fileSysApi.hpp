#ifndef FILESYSAPI_HPP
#define FILESYSAPI_HPP

#include <string>
#include <utility>
#include <memory>

namespace filesysapi {
	
	enum FileType : uint8_t {
		NO_MORE_FILES = 0,
		DIRECTORY,
		FILE
	};
	
	typedef std::pair<std::string, FileType> nameType_pr;
	
	class FileHandler;
	
	class DirContainer {
		std::shared_ptr<FileHandler> mHandler;
	public:
		explicit DirContainer(const std::string &path);
	public:
		operator bool() const;
		nameType_pr nextFile();
		void newPath(const std::string &path);
	};

}

#endif // FILESYSAPI_HPP
