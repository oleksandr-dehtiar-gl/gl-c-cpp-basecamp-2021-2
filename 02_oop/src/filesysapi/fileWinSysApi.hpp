#ifndef FILEWINSYSAPI_HPP
#define FILEWINSYSAPI_HPP

#include <windows.h>
#include <stdexcept>
#include <strsafe.h>
#include <new>

#pragma comment(lib, "User32.lib")

namespace filesysapi {
	
	std::string absolutePath(const std::string& path) {
		if (path.empty())
			return std::string();
		static char buf[MAX_PATH];
		unsigned int uiResult = GetFullPathNameA(path.c_str(), MAX_PATH, buf, nullptr);
		if (uiResult <= MAX_PATH)
			return std::move(std::string(buf, uiResult));
		try {
			char *newBuf = new char[uiResult];
			uiResult = GetFullPathNameA(path.c_str(), uiResult, newBuf, nullptr);
			return std::move(std::string(newBuf, uiResult));
		} catch(...) {}
		return std::string();
	}
	
	class FileHandler {
		HANDLE handle;
		WIN32_FIND_DATA findData;
	private:
		void firstFile(const std::string &path) { 
			if (path.length() > MAX_PATH)
				throw std::invalid_argument("Path length greate than MAX value!\n");
			if ((handle = FindFirstFile(path.c_str(), &findData)) == INVALID_HANDLE_VALUE)
				throw std::invalid_argument("Invalid Path: " + path);
		}
		void close() { if (isValid()) FindClose(handle); handle = INVALID_HANDLE_VALUE; }
	public:
		FileHandler(const std::string &path) { firstFile(path); }
		~FileHandler() { close(); }
		
		bool isValid() const { return handle == INVALID_HANDLE_VALUE ? false : true; }
		void setNewPath(const std::string &path) { close(); firstFile(path); }
		
		bool nextPath() {
			if (handle == INVALID_HANDLE_VALUE)
				throw std::invalid_argument("Read from invalid handle file descriptor!\n");
			if (FindNextFile(handle, &findData) == 0) {
				if (GetLastError() == ERROR_NO_MORE_FILES) {
					close();
					return false;
				} else {
					throw std::runtime_error("Can not read next file!\n");
				}
			}
			return true;
		}
	public:
		DWORD fileAttrib() const { return findData.dwFileAttributes; }
		bool isDirectory() const { return findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY ? true : false; }
		char* fileName() { return findData.cFileName; }
	};

}

#endif //FILEWINSYSAPI_HPP
