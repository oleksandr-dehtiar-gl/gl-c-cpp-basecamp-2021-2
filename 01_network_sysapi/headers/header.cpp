#include "header.hpp"

namespace transfer {
	
	std::ostream& operator<<(std::ostream& out, FileListHeader& header) {
		out << "FileListHeader: \n";
		out << "- type: " << (header.mHeader.type == headerType::ANSWER_FILELIST ? "ANSWER_FILELIST" : "ERROR! TYPE IS NOT ANSWER_FILELIST") << std::endl;
		out << "- totalFileCount: " << header.mHeader.numFiles  << std::endl;
		out << "- size Pakcet: " << header.mHeader.sizePacket;
		return out;
	}
	
	std::ostream& operator<<(std::ostream &out, FileInfoHeader& header) {
		out << "FileInfoHeader: \n";
		out << "- type: " << (header.mHeader.type == headerType::SELECT_FILE ? "SELECT_FILE" : "ERROR! TYPE IS NOT SELECT_FILE") << std::endl;
		out << "- nameLength: " << header.mHeader.nameLength  << std::endl;
		out << "- size fileSize: " << header.mHeader.fileSize;
		return out;
	}
	
}
