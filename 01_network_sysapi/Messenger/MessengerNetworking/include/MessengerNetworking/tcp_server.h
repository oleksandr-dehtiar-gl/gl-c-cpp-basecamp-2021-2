#pragma once
#include "MessengerNetworking/tcp_core.h"

class tcpServer:public TCPCORE::tcpCore{
    private:
        void bind() override;
        void bind(SOCKET sock);
        void disconnect(SOCKET sock);
        void connect() override;
    public:
    tcpServer(){}
};