# C++, Networking, System API

----

The following approaches are required:
- Console application.
- CMake to build application.
- Language/libraries: C++, usage of additional libraries or 3rd party code is prohibited. For threading, networking should be used platform-dependent API. (details can be discussed individually with the assigned mentor).
- Application should be cross-compile, e.g. should be compilable on Linux OS (Ubuntu 20.04) and Windows OS (Windows 10) without any code modifications.
It's allowed to use standards from C++11 to C++17.

 
Application logic must be divided from Network and System API.
- Platform dependent code must be in a separate module.
- Network dependent code must be in a separate module.

----

# Sub-Task 9. Client/Server application to check system (disk) space on remote host.
- Communication in between client and server should be done via port 5555
- Client has to get HDD space information from the system.
- Server will request this information via port 5555.
- Client has to replay each 5 seconds with the following information:
	PC-name / HDD size / Free space
	
----

## The folder "Server"

* **[WinAPI/Srver/Server.cpp](WinAPI/Srver/Server.cpp)** Multi-threaded server socket prototype. WinSock. (Windows only)
The catalog contains the source code and the assembly file.

## The folder "Client"

* **[WinAPI/Client/Client.cpp](WinAPI/Client/Client.cpp)** A prototype of a multi-threaded client. WinSock. (Windows only)
Communicates with the Server application before the "exit" command is issued.

----

Assembly is performed by standard means CMake, Make, NMake.
