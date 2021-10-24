#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstdint>

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN 
		#define WIN32_LEAN_AND_MEAN
	#endif // WIN32_LEAN_AND_MEAN
	
	#define _WIN32_WINNT_WIN10  0x0A00
	
	#include <winsock2.h>
	#include <WS2tcpip.h>

	#pragma comment(lib, "Ws2_32.lib")

#endif // _WIN32

namespace network {
	
#define MAX_CONNECTION 5

#ifdef _WIN32
	typedef SOCKET socket_t;
	typedef sockaddr SA;
	typedef sockaddr_in SA_IN;
	typedef sockaddr_storage SA_ST;
	
	typedef SSIZE_T error_t;
	
	enum SHUTDOWN : uint8_t {
		RECEIVE = SD_RECEIVE,
		SEND = SD_SEND,
		BOTH = SD_BOTH
	};
	
	enum ERROR_SOCK : socket_t {
		FAIL_SOCKET = INVALID_SOCKET
	};
	
#endif // _WIN32

#ifdef __linux__

#endif // _WIN32

#ifdef _WIN32
	#define INIT() 	WSADATA wsdata; \
					if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) { \
						printf("Error call WSAStartup!\n"); \
						WSACleanup();\
					}
	#define FREE_INIT()	WSACleanup();
#endif // _WIN32

	class INITNETWORK {
	public:
		INITNETWORK() { INIT(); }
		~INITNETWORK() { FREE_INIT(); }
	};

	/* This function return socket that connection to host whith hostname and servname
	*
	* @param[in] hosname
	*		the address of the machine to which we are connecting
	*
	* @param[in] servname
	*		the port of the machine to which we are connecting
	*
	* @return 
	*		FAIL_SOCKET if not connection. If success valid sock ID
	*/
	socket_t tcpConnect(const char *hosname, const char *servname);
	
	/* This function return listen socket that can accept connections
	* @param[in] hosname
	*		the interface address of the machine that will accept connection(local address)
	*
	* @param[in] servname
	*		the port to which connections will come
	*
	* @return 
	*		FAIL_SOCKET if not connection. If success valid sock ID
	*/
	socket_t tcpListen(const char *hostname, const char *servname);
	
	/* This function return socket that can be used for read/write whith other machine
	*
	* @param[in] s
	*		the interface address of the machine that will accept connection(local address)
	*
	* @return 
	*		FAIL_SOCKET if not connection is established other valid socket_t 
	*/
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
	*		- SHUTDOWN::RECIVE		Shutdown receive operations.
	*		- SHUTDOWN::SEND 		Shutdown send operations.
	*		- SHUTDOWN::BOTH 		Shutdown both send and receive operations.
	*
	* @return 
	*		0 if function called successfully. Otherwise error socket code
	*/
	error_t Shutdown(socket_t s, SHUTDOWN how);
	
	
	// FUNCTIONS FOR CHECK ERROR 
	error_t getLastSocketError();
	bool socetkIsValid(socket_t s);
	void printErrorMessage(error_t codeID);
	
	// Close socket
	error_t socketClose(socket_t s);
	
	uint64_t hostToNet_u64(uint64_t val);
	uint64_t netToHost_u64(uint64_t val);
	
}

#endif // NETWORK_HPP
