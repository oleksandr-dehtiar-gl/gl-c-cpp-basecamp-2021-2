#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <utility>

namespace transferUtil {
	
	typedef std::pair<std::string, uintmax_t> fileNameSize_p;
	
	std::vector<fileNameSize_p> getFilesFromDir(const std::string &path);

}

#endif // UTILITY_HPP
