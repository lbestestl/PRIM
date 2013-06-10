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
//    AES256,
    SHA256
};
QString cipher(SslMode, QString);
QString decipher(SslMode, QString);
std::string cipherSHA256(std::string);
//std::string cipherAES256(std::string, std::string);
//std::string decipherAES256(std::string, std::string);
}


#endif // SECURITY_H
