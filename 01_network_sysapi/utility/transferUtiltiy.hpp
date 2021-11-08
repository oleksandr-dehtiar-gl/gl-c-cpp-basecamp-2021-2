#ifndef TRANSFERUTILTIY_HPP
#define TRANSFERUTILTIY_HPP

#include <utility>
#include <string>
#include <filesystem>

namespace transfer {

	namespace fs = std::filesystem;
	typedef std::pair<std::string, size_t> nameSize_p;
	
	std::vector<nameSize_p> getFileList(const std::string &namedir);

	void readCommandLineArg(int argc, char ** argv, const char *defaultHost, const char *defaultServ);

}

#endif // TRANSFERUTILTIY_HPP
