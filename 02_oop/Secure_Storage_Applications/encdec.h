#ifndef ENCDEC_H
#define ENCDEC_H
#include <QString>

class encdec
{
private:
    QString filePath;
    int key;
    char c;

public:
    encdec(const QString& filePath) : filePath(filePath){};
    void encrypt(int password);
    void decrypt(int password);
};

#endif // ENCDEC_H
