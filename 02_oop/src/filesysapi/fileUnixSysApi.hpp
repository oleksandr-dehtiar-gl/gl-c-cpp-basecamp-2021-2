#ifndef FILEUNIXSYSAPI_HPP
#define FILEUNIXSYSAPI_HPP

#include <string>

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

namespace filesysapi {

	std::string absolutePath(const std::string& path) {
		static char absolutePath[PATH_MAX];
		char *pPath = realpath(path.c_str(), absolutePath);	
		if (pPath == absolutePath)
			return std::string(absolutePath);
		else
			return std::string();	
        }

	class FileHandler {
		DIR *mDirHandle;
		struct dirent *mCurrentFile;
        private:
                void firstFile(const std::string &path) {
			if(path.empty()) {
				throw std::invalid_argument("Path is empty");
				mDirHandle = nullptr;	
			} 
			mDirHandle = opendir(path.c_str());	
			if (!isValid())
				throw std::invalid_argument("Invalid in ctor filesys: " + path);	
                }
                void close() { if (isValid()) closedir(mDirHandle); mDirHandle = nullptr; }
        public:
                FileHandler(const std::string &path) { firstFile(path); }
                ~FileHandler() { close(); }

                bool isValid() const { return mDirHandle == nullptr ? false : true; }
                void setNewPath(const std::string &path) { close(); firstFile(path); }
		bool nextPath() {
			errno = 0;
			if (!isValid())
				throw std::invalid_argument("Read from invalid handle file descriptor!\n");
			mCurrentFile = readdir(mDirHandle);	
			if (mCurrentFile == nullptr) {
				close();	
				if(errno == EBADF)
					throw std::invalid_argument("Can not read next file!\n");	
				return false;	
			}
                        return true;
                }
        public:
                ///*DWORD*/ long fileAttrib() const { return 0;/*findData.dwFileAttributes;*/ }
		bool isDirectory() const { return mCurrentFile->d_type == DT_DIR ? true : false; }
		char* fileName() {
			if (!isValid())
				return nullptr;
			return mCurrentFile->d_name;	
		}
	};
}
	
#endif // FILEUNIXSYSAPI_HPP

	
