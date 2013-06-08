/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef SECURITY_H
#define SECURITY_H


#include <QString>
#include <openssl/aes.h>
#include <openssl/sha.h>


enum SslMode {
    AES256,
    SHA256
};


class Security
{
public:
    Security();
    QString cipher(QString);
    QString decipher(QString);
    QString cipher(SslMode, QString);
    QString decipher(SslMode, QString);
};


#endif // SECURITY_H
