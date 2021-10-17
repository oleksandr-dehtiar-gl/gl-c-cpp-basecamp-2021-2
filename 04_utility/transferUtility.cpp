#include <iostream>
#include <filesystem>

#include "transferUtility.hpp"

namespace transferUtil {
	
	namespace fs = std::filesystem;
	
	std::vector<fileNameSize_p> getFilesFromDir(const std::string &path) {
		std::vector<fileNameSize_p> fileVec;
		try {
			fs::directory_iterator iterDir(path);
			fileNameSize_p filePair;
			for (const auto & entity : iterDir) {
				if (fs::is_directory(entity.path()))
					continue;
				if (path == ".")
					std::get<0>(filePair) = entity.path().filename().string();
				else {
					std::get<0>(filePair) = entity.path().relative_path().string();
				}
				std::get<1>(filePair) = fs::file_size(entity.path());
				fileVec.push_back(filePair);
			}
		} catch(fs::filesystem_error &exc) {
			std::cout << exc.what() << std::endl;
			return std::vector<fileNameSize_p>();
		}
		return fileVec;
	}

}

