#include <iostream>

#include "transferUtiltiy.hpp"

extern const char *host;
extern const char *serv;

namespace transfer {
	
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
	
	std::vector<nameSize_p> getFileList(const std::string &namedir) {
		std::vector<nameSize_p> files;
		try {
			for(auto const& dir_entry: fs::directory_iterator{namedir.c_str()}) {
				if (!fs::is_directory(dir_entry.path())) 
					files.push_back(std::make_pair(dir_entry.path().filename().string(), fs::file_size(dir_entry.path())));
			}
		} catch(std::exception &exc) {
			std::cerr << "ERROR! Read list of file from current directory\n";
			std::cerr << exc.what() << std::endl;
		}
		return std::move(files);
	}
	
}
