#include "encdec.h"
#include "passwordwindow.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
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



    // Reading original file till
    // end of file
    std::vector<char> test;
    while (iFile >> std::noskipws >> c) {
        int temp = (c + key);

        // Write temp as char in
        // output file
        test.push_back(char(temp));
    }
    iFile.close();
    oFile.open(filePath.toStdString(), std::fstream::out);
    for(char i : test)
    {
        oFile << i;
    }

    // Closing both files

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



    // Reading original file till
    // end of file
    std::vector<char> test;
    while (iFile >> std::noskipws >> c) {
        int temp = (c - key);

        // Write temp as char in
        // output file
        test.push_back(char(temp));
    }
    iFile.close();
    oFile.open(filePath.toStdString(), std::fstream::out);
    for(char i : test)
    {
        oFile << i;
    }

    // Closing both files

    oFile.close();
}
