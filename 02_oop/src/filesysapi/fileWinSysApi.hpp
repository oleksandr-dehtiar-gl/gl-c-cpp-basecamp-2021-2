#ifndef FILEWINSYSAPI_HPP
#define FILEWINSYSAPI_HPP

#include <windows.h>
#include <stdexcept>
#include <strsafe.h>

#pragma comment(lib, "User32.lib")

namespace filesysapi {
	
	class FileHandler {
		HANDLE handle;
		WIN32_FIND_DATA findData;
	private:
		void firstFile(const std::string &path) { handle = FindFirstFile(path.c_str(), &findData); }
		void close() { if (isValid()) FindClose(handle); handle = INVALID_HANDLE_VALUE; }
	public:
		FileHandler(const std::string &path) { firstFile(path); }
		~FileHandler() { close(); }
		
		bool isValid() const { return handle == INVALID_HANDLE_VALUE ? false : true; }
		void setNewPath(const std::string &path) { close(); firstFile(path); }
		
		bool nextFile() {
			if (handle == INVALID_HANDLE_VALUE)
				throw std::runtime_error("Read from invalid handle file descriptor!\n");
			
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
		char* fileName() { return findData.cFileName; }
	};

}

#endif //FILEWINSYSAPI_HPP
