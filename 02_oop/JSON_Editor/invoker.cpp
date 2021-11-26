#include "invoker.h"

void Invoker::exec(Command *command_){
    command = command_;
    try{
    command->exec();
    }
    catch(...){

    }
}
Invoker::~Invoker(){
    delete command;
}
