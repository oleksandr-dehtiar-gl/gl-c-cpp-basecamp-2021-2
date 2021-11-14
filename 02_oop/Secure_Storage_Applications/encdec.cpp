#include "encdec.h"
#include "passwordwindow.h"
#include <fstream>
#include <vector>

void encdec::encrypt(int password)
{
    key = password;

    // Input stream
    std::ifstream iFile;
    std::ofstream oFile;

    // Open input file
    // ios::binary- reading file
    // character by character
    iFile.open(filePath.toStdString(), std::fstream::in);

    // Reading file till
    // end of file
    std::vector<char> test;
    while (iFile >> std::noskipws >> c)
    {
        int temp = (c + key); //Encrypt char
        // Add temp as char in vector
        test.push_back(char(temp));
    }
    iFile.close();

    //Write characters from vector in file
    oFile.open(filePath.toStdString(), std::fstream::out);
    for(char i : test)
    {
        oFile << i;
    }
    oFile.close();
}

void encdec::decrypt(int password)
{
    key = password;

    // Input stream
    std::ifstream iFile;
    std::ofstream oFile;

    // Open input file
    // ios::binary- reading file
    // character by character
    iFile.open(filePath.toStdString(), std::fstream::in);

    // Reading file till end of file
    std::vector<char> test;
    while (iFile >> std::noskipws >> c)
    {
        int temp = (c - key);//Decrypt char

        // Add temp as char in vector
        test.push_back(char(temp));
    }
    iFile.close();

    oFile.open(filePath.toStdString(), std::fstream::out);
    for(char i : test)
    {
        oFile << i;
    }
    oFile.close();
}
