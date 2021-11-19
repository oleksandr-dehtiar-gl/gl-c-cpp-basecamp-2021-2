#include "../tcp/hdr/TcpClient.h"

#include <iostream>
#include <stdlib.h>
#include <thread>
// #include <string>

// using namespace std;

// std::string getHostStr(uint32_t ip, uint16_t port) {
//     return std::string() + std::to_string(int(reinterpret_cast<char*>(&ip)[0])) + '.' +
//             std::to_string(int(reinterpret_cast<char*>(&ip)[1])) + '.' +
//             std::to_string(int(reinterpret_cast<char*>(&ip)[2])) + '.' +
//             std::to_string(int(reinterpret_cast<char*>(&ip)[3])) + ':' +
//             std::to_string( port );
// }


void client(std::string foldername)
{
  // using namespace std::chrono_literals;
  TcpClient client;
  client.connectTo(LOCALHOST_IP, 8080);
  client.sendData(foldername.c_str(), foldername.length()+1); //+1 for line-ending char

  DataBuffer data = client.loadData();
  std::string reply  = (const char*)data.data_ptr;
  while(reply == "Processing...")
  {
    std::cout << reply << std::endl;
    data = client.loadData();
    reply  = (const char*)data.data_ptr;
  }
  std::cout << "Client[ " << data.size << " bytes ]: " << reply << '\n';
  client.disconnect();
  std::clog << "Socket closed!\n";
}

int main()
{
  std::cout<< "Enter folder name: " << std::endl;
  std::string name;
  std::cin >> name;
  std::thread th1(client, name);
  th1.join();
}
