#include "../tcp/hdr/TcpServer.h"
#include "../tcp/hdr/TcpClient.h"
#include "timer.h"

#include <iostream>
#include <mutex>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <regex>


std::vector <std::string> parse(std::string cmdOut)
{
  #ifdef _WIN32
  std::regex exp("Directory of (.+)$");
  #else
  std::regex exp("^(.+)$");
  #endif
  std::smatch matches;
  std::vector <std::string> result;
  std::string::const_iterator searchStart(cmdOut.cbegin());
  while (std::regex_search( searchStart, cmdOut.cend(), matches, exp ) )
  {
      result.push_back(matches[1].str());
      searchStart = matches.suffix().first;
  }
  return result;
}

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    #ifdef _WIN32
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    #else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    #endif
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

#ifdef _WIN32
std::vector<std::string> split(std::string str, std::string token)
{
    std::vector<std::string> result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos)
        {
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}
std::vector<std::string> getDrives()
{
  const std::string command = "wmic logicaldisk get caption";
  const std::string driveList = exec(command.c_str());
  return split(driveList, "\r\n");
}
#endif
//Parse ip to std::string
std::string getHostStr(const TcpServer::Client &client)
{
  uint32_t ip = client.getHost();
  return std::string() + std::to_string(int(reinterpret_cast<char *>(&ip)[0])) + '.' +
         std::to_string(int(reinterpret_cast<char *>(&ip)[1])) + '.' +
         std::to_string(int(reinterpret_cast<char *>(&ip)[2])) + '.' +
         std::to_string(int(reinterpret_cast<char *>(&ip)[3])) + ':' +
         std::to_string(client.getPort());
}

TcpServer server
(
    8080,

    [](DataBuffer data, TcpServer::Client &client)
    { // Data handler

      std::string cmdOut;
      Timer timer;
      const std::function<void()> procLambda = [&]()
      {
        std::string proc = "Processing...";
        client.sendData(proc.c_str(), proc.length()+1);
      };
      timer.start(500, procLambda);
      #ifdef _WIN32
      const auto drives = getDrives();
      for(auto it = drives.begin() + 1, itEnd = drives.end(); it!=itEnd; ++it)
      {
        std::string cmd = "cd /d " + *it + " && cd \\ && dir \"" + std::string((char*)data.data_ptr) + "\" /AD /s";
        cmdOut += exec(cmd.c_str());
      }
      #else
      std::string cmd = "find / -name '" + std::string((char *)data.data_ptr) + "' -type d";
      cmdOut = exec(cmd.c_str());
      #endif
      timer.stop();
      std::cout << "Client " << getHostStr(client) << " send data: " << '\n';
      const auto searchRes = parse(cmdOut);
      if(searchRes.empty())
      {
        std::string reply = "Failure";
        client.sendData(reply.c_str(), reply.length()+1);
      }
      else
      {
        std::string resultPatches = "Success";
        for(auto it = searchRes.begin(), itEnd = searchRes.end(); it!=itEnd; ++it)
        {
          resultPatches +='\n';
          resultPatches += (std::string)(*it);
        }
        client.sendData(resultPatches.c_str(), resultPatches.length() + 1);
      }
    },

    [](TcpServer::Client &client)
    { // Connect handler
      std::cout << "Client " << getHostStr(client) << " connected\n";
    },

    [](TcpServer::Client &client)
    { // Disconnect handler
      std::cout << "Client " << getHostStr(client) << " disconnected\n";
    },

    {1, 1, 1} // Keep alive{idle:1s, interval: 1s, pk_count: 1}
);

void testServer()
{
  //Start server
  if (server.start() == TcpServer::status::up)
  {
    std::cout << "Server listen on port:" << server.getPort() << std::endl;
    server.joinLoop();
  }
  else
  {
    std::cout << "Server start error! Error code:" << int(server.getStatus()) << std::endl;
  }
}

int main()
{
  using namespace std::chrono_literals;
  try
  {

    testServer();

    std::this_thread::sleep_for(30s);
  }
  catch (std::exception &except)
  {
    std::cerr << except.what();
  }
}
