#pragma once

#include "ProcessHandle.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>


class ProcessManager
{
public:
    static const std::map<int, std::string> & GetProcessList(bool needToUpdate = true);
    static bool TerminateProcess(const std::string & processName);
    
private:

#ifdef _WIN32
    static void UpdateProcessListWIN32();
#else 

    #define PROC_DIR "/proc/"
    #define CMDLINE_DIR "/cmdline"
    static  void UpdateProcessListUNIX();
    static bool isNumeric(const std::string& str);
#endif
    static std::map<int, std::string> m_processList;

};

