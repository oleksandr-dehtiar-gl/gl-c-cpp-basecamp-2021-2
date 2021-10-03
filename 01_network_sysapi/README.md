# C++, Networking, System API

The following approaches are required:
- Console application.
- CMake to build application.
- Language/libraries: C++, usage of additional libraries or 3rd party code is prohibited. For threading, networking should be used platform-dependent API. (details can be discussed individually with the assigned mentor).
- Application should be cross-compile, e.g. should be compilable on Linux OS (Ubuntu 20.04) and Windows OS (Windows 10) without any code modifications.
It's allowed to use standards from C++11 to C++17.

 
Application logic must be divided from Network and System API.
- Platform dependent code must be in a separate module.
- Network dependent code must be in a separate module.
