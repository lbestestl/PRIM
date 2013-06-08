/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef SECURITY_H
#define SECURITY_H


#include <QString>


namespace prim_security {
enum SslMode {
    AES256,
    SHA256
};
QString cipher(SslMode, QString);
QString decipher(SslMode, QString);
//std::string cipher(SslMode, std::string);
//std::string decipher(SslMode, std::string);
std::string cipherSHA256(std::string);
std::string cipherAES256(std::string, std::string);
std::string decipherAES256(std::string, std::string);
static const unsigned char akey[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};
}


#endif // SECURITY_H
