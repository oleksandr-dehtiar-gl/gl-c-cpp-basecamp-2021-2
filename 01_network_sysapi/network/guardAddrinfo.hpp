#ifndef GUARDADDRINFO_HPP
#define GUARDADDRINFO_HPP

#include <cstdio>
#include <stdexcept>
#include <vector>

#include "network.hpp"

namespace network {
	
	class guard_addrinfo {
		struct addrinfo *mRootAInfo;
		std::vector<struct addrinfo *> mListAInfo;
	private:
		bool checkNum(int num);
	public:
		guard_addrinfo(const char *host, const char* serv, const addrinfo* hint);
		~guard_addrinfo() { freeaddrinfo(mRootAInfo); }
	public:
		int size() {
			return mListAInfo.size(); 
		}
		int flags(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_flags;
		}
		int family(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_family;
		}
		int socktype(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_socktype;
		}
		int protocol(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_protocol;
		}
		int addrlen(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_addrlen;
		}
		const struct sockaddr* addr(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_addr;
		}
		const char* canonname(int num) {
			checkNum(num);
			return mListAInfo[num]->ai_canonname;
		}
		unsigned short port(int num) {
			checkNum(num);
			return ((struct sockaddr_in*)mListAInfo[num]->ai_addr)->sin_port;
		}
		
		std::string addrToString(int num);
		void print();
	};
	
}

#endif // GUARDADDRINFO_HPP

