#ifndef NETWORK_HPP
#define NETWORK_HPP

#define MAX_CONNECTION 5
#define MSS_DEFAULT_SIZE 1200

#include <cstdint>

// INCLUDE PLATFORM DEPENDENT HEADER FILES
// =======================================
#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN 
		#define WIN32_LEAN_AND_MEAN
	#endif // WIN32_LEAN_AND_MEAN
	
	#define _WIN32_WINNT 0x501
	
	#include <windows.h>

	#include <winsock2.h>
	#include <ws2tcpip.h>
	
	#ifdef __MINGW32__
		#include <basetsd.h>
	#else
		#include <BaseTsd.h>
	#endif // __MINGW32__
	
	#ifdef _MSC_VER
		#pragma comment(lib, "Ws2_32.lib")
	#endif // _MSC_VER
#endif // _WIN32

namespace network {
	
// TYPEDEF FOR TYPES AND DATA STRUCTURE
// ====================================
#ifdef _WIN32
	typedef SOCKET socket_t;
	typedef sockaddr SA;
	typedef sockaddr_in SA_IN;
	typedef sockaddr_storage SA_ST;
	
	typedef SSIZE_T error_t;
	
	enum SHDWN : uint8_t {
		RECEIVE = SD_RECEIVE,
		SEND = SD_SEND,
		BOTH = SD_BOTH
	};
	
#endif // _WIN32

#ifdef __linux__
	typedef int socket_t;
#endif // _WIN32

// MACROS FUNCTIONS 
// ================
#ifdef _WIN32
	#define INIT() 	WSADATA wsdata; \
					if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) { \
						printf("Error call WSAStartup!\n"); \
						WSACleanup(); return 1;  \
					}
#endif // _WIN32
	
// NETWORK FUNCTION WRAPPERS
// =========================
	
	/* This function get sockaddr structure name of remote host 
	*
	* @param[in] s
	*		this is a socket that having successfull connection whith
	*		remote host
	*
	* @param[out] name
	*		in this argument function saves socket address structure from remote host
	*
	* @param[in, out] namelen
	*		On call, the namelen parameter contains the size, in bytes, of the name buffer. 
	* 		On return, the namelen parameter contains the actual size, in bytes, of the name parameter returned.
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	error_t getPeerName(socket_t s, SA *name, int *namelen);
	*/
	
	// SOCKET FUNCTIONS
	socket_t tcpConnect(char *hosname, char *servname);
	socket_t tcpListen(char *hostname, char *servname);
	socket_t Accept(socket_t s);
	
	/* This function read n data as much as possible
	*
	* @param[in] s
	*		this is a socket that having successfull connection
	*
	* @param[in] vptr
	*		pointer to recive buffer
	*
	* @param[in, out] n
	*		[in] number of read data. [out] amount of data that can be received
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*		if return value is 0 and receive data is 0 connection successfully closed
	*/
	error_t Read(socket_t s, void *vptr, unsigned int *n);

	/* If no error ocure all n data will be reed
	*
	* @param[in] s
	*		this is a socket that having successfull connection
	*
	* @param[in] vptr
	*		pointer to recive buffer
	*
	* @param[in, out] n
	*		[in] number of read data. [out] amount of recive data must be the same as the initial value if no error occurred
	*		Another return amount recive data
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*		if return value is 0 and receive data is 0 connection successfully closed
	*/
	error_t Readn(socket_t s, void *vptr, unsigned int *n);
	
	/* This function write count n data as much as possible
	*
	* @param[in] s
	*		this is a socket that having successfull connection 
	*
	* @param[in] cvptr
	*		pointer to buffer whith data for send
	*
	* @param[in, out] n
	*		[in] number of write data. [out] amount of data send if an error occurred
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*/
	error_t Write(socket_t s, const void *cvptr, unsigned int *n);
	
	/* This function write all data to the socket if no error occurred
	*
	* @param[in] s
	*		this is a socket that having successfull connection
	*
	* @param[in] cvptr
	*		pointer to buffer whith data for send
	*
	* @param[in, out] n
	*		[in] number of write data. [out] amount of data send if an error occurred
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*/
	error_t Writen(socket_t s, const void *cvptr, unsigned int *n);
	
	/* Function disables sends or receives on a socket
	*
	* @param[in] s
	*		this is a socket that having successfull connection
	*
	* @param[in] how
	*		flag that describes what types of operation will no longer be allowed.
	*		- SHDWN::RECIVE		Shutdown receive operations.
	*		- SHDWN::SEND 		Shutdown send operations.
	*		- SHDWN::BOTH 		Shutdown both send and receive operations.
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*/
	error_t Shutdown(socket_t s, SHDWN how);
	
	
	// FUNCTIONS FOR CHECK ERROR 
	error_t getLastSocketError();
	bool socetkIsValid(socket_t s);
	void printErrorMessage(error_t codeID);
	
	// Close socket
	error_t closesocket(socket_t s);
	
}

#endif // NETWORK_HPP
