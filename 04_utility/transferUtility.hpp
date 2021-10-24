#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <utility>

namespace transferApp {

	typedef std::pair<std::string, size_t> NameSize_p;
	std::vector<NameSize_p> getFilesFromDir(const std::string &path);

	void readCommandLineArg(int argc, char ** argv, const char *defaultHost, const char *defaultServ);
	
}

#endif // UTILITY_HPP
