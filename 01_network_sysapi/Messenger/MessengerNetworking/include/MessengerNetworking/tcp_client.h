#pragma once
#include "tcp_core.h"
class tcpClient:public TCPCORE::tcpCore{
    private:
        void bind() override;
        void connect() override;
        std::string ipAdress;
    public:
    tcpClient(std::string ipAdress_):ipAdress(ipAdress_){}
};