#include "validator.h"
#include <exception>
bool Validator::exec(QString str_) {
    try{
    i=0;
    str_.remove(' ');
    str_.remove('\n');
    str_.remove('\t');
    str_.squeeze();
    this->str = str_;
    return S();
    }
    catch(...){
        return false;
    }
}
bool Validator::S(){
    if(str[i] =='{')
    {
        i++;
        if(EXP())
        {
            i++;
            if(str[i]=='}')
                return true;
        }
    }
    throw new std::exception;
}
bool Validator::EXP(){
    if(str[i]=='\"')
    {
        i++;
        if(VAR())
        {
            if(str[i]==':'){
                i++;
                if(VAL())
                {
                    if(str[i+1]==',' || str[i+1]=='}')
                    {
                        if(EXP())
                            return true;
                    }
                }
            }
        }
    }
    throw new std::exception;
}
bool Validator::VAR(){
    if(CH()){
        i++;
        if(VAR1())
            i++;
        i--;
        if(str[i]=='\"'){
            i++;
            return true;
        }
    }
    throw new std::exception;
}
bool Validator::VAR1(){
    if(CH()){
        i++;
        if(VAR1())
            return true;
    }
    if(C0()){
        i++;
        if(VAR1())
            return true;
    }
    if(str[i]=='-'){
        i++;
        if(VAR1())
            return true;
    }
    if(str[i]=='_'){
        i++;
        if(VAR1())
            return true;
    }
    return false;
}
bool Validator::VAL(){
    if((QString(str[i]) + str[i+1]+str[i+2]+str[i+3])=="true"){
        i+=4;
        return true;
    }
    if((QString(str[i]) + str[i+1]+str[i+2]+str[i+3])=="null"){
        i+=4;
        return true;
    }
    if((QString(str[i]) + str[i+1]+str[i+2]+str[i+3] + str[i+4])=="false"){
        i+=5;
        return true;
    }
    auto temp = i;
    if(NUM())
        return true;
    i = temp;
    if(S())
        return true;
    i = temp;
    if(str[i]=='\"'){
        i++;
        if(!STR()){
            if(i > str.size())
                return false;
            i++;
            return true;
        }
    }
    i = temp;
    if(str[i]=='[')
        if(ARR())
            if(str[i]==']')
                return true;
    throw new std::exception;
}
bool Validator::ARR(){
        if(S()){
            if(str[i+1]==','){
                i++;
                return ARR();
            }
        else return true;
        }
        return false;
}
bool Validator::CH(){
    if(str[i].isLetter()){
        i++;
        return true;
    }
    return false;
}
bool Validator::NUM(){
    if(C()){
        K();
        return true;
    }
    else return false;
}
bool Validator::C(){
    if(str[i].isDigit() && str[i]!='0'){
        i++;
        return true;
    }
    return false;
}
bool Validator::C0(){
    if(str[i].isDigit()){
        i++;
        return true;
    }
    return false;
}
bool Validator::K(){
    if(C0()){
        return K();
    }
    else return false;
}
bool Validator::STR(){
    auto temp = i;
    if(CH())
        if(STR())
            return true;
    i = temp;
    if(NUM())
        if(STR())
            return true;
    i = temp;
    if(i > str.size())
        return false;
    if(str[i]!='\"')
        if(STR())
            return true;
    return false;
}
