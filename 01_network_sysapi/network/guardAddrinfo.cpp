#include <iostream>
#include <map>
#include <utility>

#include "guardAddrinfo.hpp"

namespace network {

	static std::map<int, const char*> flagsStr = {
		std::make_pair(AI_PASSIVE, "AI_PASSIVE"),
		std::make_pair(AI_CANONNAME, "AI_CANONNAME"),
		std::make_pair(AI_NUMERICHOST, "AI_NUMERICHOST"),
		std::make_pair(AI_ALL, "AI_ALL"),
		std::make_pair(AI_ADDRCONFIG, "AI_ADDRCONFIG"),
		std::make_pair(AI_V4MAPPED, "AI_V4MAPPED"),
		std::make_pair(AI_NON_AUTHORITATIVE, "AI_NON_AUTHORITATIVE"),
		std::make_pair(AI_SECURE, "AI_SECURE"),
		std::make_pair(AI_RETURN_PREFERRED_NAMES, "AI_RETURN_PREFERRED_NAMES"),
		std::make_pair(AI_FQDN, "AI_FQDN"),
		std::make_pair(AI_FILESERVER, "AI_FILESERVER")
	};
	
	static std::map<int, const char*> familyStr = {
		std::make_pair(AF_UNSPEC, "AF_UNSPEC"),
		std::make_pair(AF_INET, "AF_INET"),
		std::make_pair(AF_NETBIOS, "AF_NETBIOS"),
		std::make_pair(AF_INET6, "AF_INET6"),
		std::make_pair(AF_IRDA, "AF_IRDA"),
		std::make_pair(AF_BTH, "AF_BTH")
	};
	
	static std::map<int, const char*> socktypeStr = {
		std::make_pair(SOCK_STREAM, "SOCK_STREAM"),
		std::make_pair(SOCK_DGRAM, "SOCK_DGRAM"),
		std::make_pair(SOCK_RAW, "SOCK_RAW"),
		std::make_pair(SOCK_RDM, "SOCK_RDM"),
		std::make_pair(SOCK_SEQPACKET, "SOCK_SEQPACKET")
	};
	
	static std::map<int, const char*> protocolStr = {
		std::make_pair(IPPROTO_TCP, "IPPROTO_TCP"),
		std::make_pair(IPPROTO_UDP, "IPPROTO_UDP")
	};
	
	void guard_addrinfo::print() {
		int numAddr = 0;
		for(auto &addri : mListAInfo) {
			std::cout << "Addrinfo [" << numAddr << "]:  \n";
			std::cout << " - ai_flags    : " << flagsStr[addri->ai_flags] << std::endl;
			std::cout << " - ai_family   : " << familyStr[addri->ai_family] << std::endl;
			std::cout << " - ai_socktype : " << flagsStr[addri->ai_socktype] << std::endl;
			std::cout << " - ai_addrlen  : " << addri->ai_addrlen << std::endl;
			std::cout << " - ai_addr: \n";
			std::cout << "   - sin_port  : " << ntohs(port(numAddr)) << std::endl;
			std::cout << "   - sin_addr  : " << addrToString(numAddr) << std::endl;
			++numAddr;
		}
	}
	
	bool guard_addrinfo::checkNum(int num) { 
		if ((num < 0) || (num > size()))
			throw std::out_of_range("ERROR! Out of range addrinfo number structure!\n");
		return true; 
	}
	
	std::string guard_addrinfo::addrToString(int num) {
		checkNum(num);
		struct addrinfo * addri= mListAInfo[num];
		const int sizeAddrstr = 50;
		char addrstr[sizeAddrstr];
		std::string addr;
		switch(addri->ai_family) {
			case AF_INET:
				addr = inet_ntop(addri->ai_family, &(((struct sockaddr_in*)(addri->ai_addr))->sin_addr), addrstr, sizeAddrstr);
				break;
			case AF_INET6:
				break;
				addr = inet_ntop(addri->ai_family, &(((struct sockaddr_in6 *)(addri->ai_addr))->sin6_addr), addrstr, sizeAddrstr);
			default:
				break; // ...
		}
		return addr;
	}
	
	guard_addrinfo::guard_addrinfo(const char *host, const char* serv, const addrinfo* hint) {
		if (getaddrinfo(host, serv, hint, &mRootAInfo) != 0) {
			throw std::domain_error("ERROR! Getaddrinfo failed: %d\n");
		}
		struct addrinfo *currentAinfo = mRootAInfo;
		try {
			while(currentAinfo != NULL) {
				mListAInfo.push_back(currentAinfo);
				currentAinfo = currentAinfo->ai_next;
			}
		} catch(std::exception& exc) {
			printf("EXCEPTION! %", exc.what());
			// std::cerr << exc.what() << std::endl;
			freeaddrinfo(mRootAInfo);
			throw;
		}
	}
	
}

