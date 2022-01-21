#include <iostream>

#include <network/socket.h>
#include <network/message.h>
#include <sys_api/mousetracker.h>
#include <sys_api/time.h>

constexpr int DEFAULT_PORT = 5577;
constexpr int CHECK_MOUSE_INTERVAL = 5;         //secs

int main()
{
//    GLMouseTracker mouseTracker;
//    while(1)
//    {
//        if(mouseTracker.checkMouseActivity())
//        {
//            std::cout << "Active\n";
//        }else
//        {
//            std::cout << "Passive\n";
//        }
//        sleep(5);
//    }

    MouseTracker mouseTracker;
    while(true)
    {
        Socket socket(AF_INET, SOCK_STREAM, 0);
        if(socket.get_socket_descriptor() < 0)
        {
            perror("Socket connection error: ");
            exit(1);
        }

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(DEFAULT_PORT);
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if(socket.connect((struct sockaddr*)&address,
                          sizeof(address)) < 0)
        {
            perror("Socket connection error: ");
            exit(2);
        }

        Message message;
        message.type = MessageType::UserMouseActivity;
        if(mouseTracker.checkMouseActivity())
        {
            message.message.mouseActivityStatus = MessageMouseActivityStatus::Active;
        }else
        {
            message.message.mouseActivityStatus = MessageMouseActivityStatus::Passive;
        }
//        std::cerr << socket.get_socket_descriptor() << ' ';
        std::cerr << socket.send((char*)(&message), sizeof(message), 0) << ' ';
//        std::cerr << (int)message.type << '\n';
        sleep(CHECK_MOUSE_INTERVAL);
        socket.close();
    }

    return 0;
}
