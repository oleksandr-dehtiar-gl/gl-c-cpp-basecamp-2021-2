#include "ProcessManager.h"


#ifdef _WIN32

void ProcessManager::UpdateProcessListWIN32()
{
    ProcessHandle hndl = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
	if (hndl)
	{
		PROCESSENTRY32  process = { sizeof(PROCESSENTRY32) };
		Process32First(hndl, &process);
		
		do
		{
			char ch[260];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP, 0, process.szExeFile, -1, ch, 260, &DefChar, NULL);
			std::string processName(ch);
			m_processList[process.th32ProcessID] = processName;



		} while (Process32Next(hndl, &process));

		CloseHandle(hndl);
        
    }

   

}
#else

bool ProcessManager::isNumeric(const std::string& str)
{
    return (std::find_if(str.begin(), str.end(), 
        [](unsigned char element) {return !std::isdigit(element);})) == str.end();
}

void ProcessManager::UpdateProcessListUNIX()
{

    
    std::string cmdLinePath;
    std::string dirName;
    std::string processName;
    std::stringstream file_content;
    struct dirent* dir_entry = NULL;
    DIR * dir_proc = NULL;
    dir_proc = opendir(PROC_DIR);


    while((dir_entry = readdir(dir_proc)))
    {
        if(dir_entry->d_type == DT_DIR)
        {
            dirName = dir_entry->d_name;
            if(isNumeric(dirName))
            {
                cmdLinePath = {};
                cmdLinePath += PROC_DIR;
                cmdLinePath += dirName;
                cmdLinePath += CMDLINE_DIR;
                std::ifstream file(cmdLinePath.data());
                if(!file.fail())
                {
                    
                    file_content << file.rdbuf();
                    processName = file_content.str();
                    file_content.str("");
                    file_content.clear();
                    file_content << dir_entry->d_name;
                    int processID = -1;
                    file_content >> processID;
                    if(processName == "\0")
                    {
                        m_processList[processID] = "Unknown Process " + std::string(dir_entry->d_name);
                    }
                    else
                    {
                        size_t spacePos = processName.find_first_of(' ');
                        if(spacePos != std::string::npos)
                        {
                            processName = processName.substr(0, spacePos);
                        }
                        size_t slashPos = processName.find_last_of('/');
                        m_processList[processID] = slashPos == std::string::npos ? 
                                                            processName : std::string(&processName[++slashPos]);
                       
                    }
                    
                   

                    file_content.str("");
                    file_content.clear();
                }
               
              

            }
        }
    }
    closedir(dir_proc);
}
#endif

bool ProcessManager::TerminateProcess(const std::string & processName)
{
    int result = -1;
    if(!m_processList.empty())
    {
        for(auto it = m_processList.begin(); it != m_processList.end(); it++)
        {
            if(it->second == processName)
            {
                #ifdef _WIN32
                ProcessHandle process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, it->first);
                if(process == NULL)
                {
                    result = -1;
                    break;
                }
                else if(!TerminateProcess(process, 0))
                {
                    CloseHandle(process);
                    result = -1;
                    break;
                }
                CloseHandle(process);
                result = 0;
                #else
                result = kill(it->first, SIGKILL);
                if(result != 0)
                {
                    break;
                }
                #endif
            }
        }
    }
    return result == 0;
}
const std::map<int, std::string> & ProcessManager::GetProcessList(bool needToUpdate)
{

    if(needToUpdate)
    {
        m_processList.clear();
        #ifdef _WIN32 
            UpdateProcessListWIN32();
        #else
            UpdateProcessListUNIX();
        #endif
    }

    return m_processList;
	
}

std::map<int, std::string> ProcessManager::m_processList = {};
