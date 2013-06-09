/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#include "Security.h"
#include "UserSettings.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <QDebug>


QString prim_security::cipher(SslMode m, QString plainText)
{
    if (m == prim_security::AES256)
        return QString::fromStdString(cipherAES256(plainText.toStdString(), UserSettings::Instance()->getPassword().toStdString()));
    else if (m == prim_security::SHA256)
        return QString::fromStdString(cipherSHA256(plainText.toStdString()));
    else
        return "";
}


QString prim_security::decipher(SslMode m, QString cipherText)
{
    if (m == prim_security::AES256)
        return QString::fromStdString(decipherAES256(cipherText.toStdString(), UserSettings::Instance()->getPassword().toStdString()));
    else
        return "";
}


std::string prim_security::cipherSHA256(std::string plainText)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, plainText.c_str(), plainText.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}


std::string prim_security::cipherAES256(std::string plainText, std::string key)
{
    std::string result;
    AES_KEY encKey;
    const unsigned char* uckey = reinterpret_cast<const unsigned char*>(key.c_str());
    const unsigned char* in = reinterpret_cast<const unsigned char*>(plainText.c_str());
    int len = strlen((const char*)in) + AES_BLOCK_SIZE;
    unsigned char* out = new unsigned char[len];
    AES_set_encrypt_key(uckey, 256, &encKey);
    AES_encrypt(in, out, &encKey);

    if (out != NULL) {
        std::stringstream ss;
        ss << out;
        result = ss.str();
    }
    printf("\noriginal:\t");
    for(int i=0;*(in+i)!=0x00;i++)
        printf("%X ",*(in+i));
    printf("\nencrypted:\t");
    for(int i=0;*(out+i)!=0x00;i++)
        printf("%X ",*(out+i));

    delete out;
    return result;
}


std::string prim_security::decipherAES256(std::string cipherText, std::string key)
{
    std::string result;
    AES_KEY decKey;
    const unsigned char* uckey = reinterpret_cast<const unsigned char*>(key.c_str());
    const unsigned char* in = reinterpret_cast<const unsigned char*>(cipherText.c_str());
    int len = strlen((const char*)in);
    unsigned char* out = new unsigned char[len];

    AES_set_decrypt_key(uckey, 256, &decKey);
    AES_decrypt(in, out, &decKey);

    if (out != NULL) {
        std::stringstream ss;
        ss << out;
        result = ss.str();
    }
    printf("\nencrypted:\t");
    for(int i=0;*(in+i)!=0x00;i++)
        printf("%X ",*(in+i));
    printf("\ndecrypted:\t");
    for(int i=0;*(out+i)!=0x00;i++)
        printf("%X ",*(out+i));

    delete out;
    return result;
}
