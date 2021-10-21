#pragma once
#include "MessengerNetworking/tcp_core.h"

class tcpServer:public TCPCORE::tcpCore{
    private:
        void bind() override;
        void connect() override;
    public:
    tcpServer(){}
    void run();
};