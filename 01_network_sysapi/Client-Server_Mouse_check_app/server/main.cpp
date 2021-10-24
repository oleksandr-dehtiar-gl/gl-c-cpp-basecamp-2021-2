#include <iostream>
#include <chrono>

#include <network/socket.h>
#include <network/message.h>

constexpr int DEFAULT_PORT = 5577;
constexpr int BACK_LOG = 1;

int main()
{
    using std::chrono::system_clock;
    Socket listener_socket(AF_INET, SOCK_STREAM, 0);
    if(listener_socket.get_socket_descriptor() < 0)
    {
        perror("Socket connection error: ");
        exit(1);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(DEFAULT_PORT);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(listener_socket.bind((struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Socket binding error: ");
        exit(2);
    }

    listener_socket.listen(BACK_LOG);

    Socket socket;

    while(true)
    {
        socket.set_socket_descriptor(listener_socket.accept(nullptr, nullptr));
        if(socket.get_socket_descriptor() < 0)
        {
            perror("Soccet accept error: ");
            exit(3);
        }
        Message message;
        socket.receive((void *)&message, sizeof(message), 0);
//        std::cerr << socket.get_socket_descriptor() << ' ';
//        std::cerr << (int)message.type << ' ';
//        std::cerr << (int)message.message.mouseActivityStatus << '\n';
//        std::cerr << buf << '\n';
//        std::cerr << (int)MessageType::UserMouseActivity;
        if(message.type == MessageType::UserMouseActivity)
        {
            auto currentMoment = system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(currentMoment);
            std::cout << std::ctime(&time) << ' ';
            if(message.message.mouseActivityStatus == MessageMouseActivityStatus::Active)
            {
                std::cout << "Active\n";
            }else
            {
                std::cout << "Passive\n";
            }
        }
        socket.send_all((char *)&message, sizeof (message), 0);
        socket.close();
    }

    return 0;
}
