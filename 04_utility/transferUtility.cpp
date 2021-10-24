#include <iostream>
#include <filesystem>

#include "transferUtility.hpp"

extern const char *host;
extern const char *serv;

namespace transferApp {
	
	namespace fs = std::filesystem;
	
	std::vector<NameSize_p> getFilesFromDir(const std::string &path) {
		std::vector<NameSize_p> fileVec;
		try {
			fs::directory_iterator iterDir(path);
			NameSize_p filePair;
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
			return std::vector<NameSize_p>();
		}
		return fileVec;
	}
	
	void readCommandLineArg(int argc, char ** argv, const char *defaultHost, const char *defaultServ) {
		// std::cout << "-- SINOPSYS: <app_name> [[host] | [serv]]\n";
		if (argc == 3) {
			host = argv[1];
			serv = argv[2];
		} else if (argc == 2) {
			host = defaultHost;
			serv = argv[1];
		} else if (argc == 1) {
			host = defaultHost;
			serv = defaultServ;
		} else {
			std::cerr << "FATAL ERROR! INVALID INPUT VARIBLES.\n";
			std::cerr << "server/client sinopsys: <app_name> [[host] serv]\n";
			exit(EXIT_FAILURE);
		}
		std::cout << "arguments list host serv: " << (host ? host : "NULL")
				  << " " << (serv ? serv : "NULL") << std::endl; 
	}
	
}
