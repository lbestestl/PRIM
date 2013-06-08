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
    int len = plainText.length() + AES_BLOCK_SIZE;
    AES_KEY encKey;
    unsigned char* out = new unsigned char[len];
    const unsigned char* uckey = reinterpret_cast<const unsigned char*>(key.c_str());
    const unsigned char* in = reinterpret_cast<const unsigned char*>(plainText.c_str());
    AES_set_encrypt_key(akey, 128, &encKey);
    AES_encrypt(in, out, &encKey);

    if (out != NULL) {
        std::stringstream ss;
        ss << out;
        result = ss.str();
    }
    int i;
    printf("original:\t");
    for(i=0;*(in+i)!=0x00;i++)
        printf("%X ",*(in+i));
    printf("\nencrypted:\t");
    for(i=0;*(out+i)!=0x00;i++)
        printf("%X ",*(out+i));
    printf("\n");
    std::cout << out <<std::endl;
    delete out;
    return result;
}


std::string prim_security::decipherAES256(std::string cipherText, std::string key)
{
    std::string result;
    int len = cipherText.length();
    AES_KEY decKey;
    unsigned char* out = new unsigned char[len];
    const unsigned char* uckey = reinterpret_cast<const unsigned char*>(key.c_str());
    const unsigned char* in = reinterpret_cast<const unsigned char*>(cipherText.c_str());
    AES_set_decrypt_key(akey, 128, &decKey);
    AES_decrypt(in, out, &decKey);

    if (out != NULL) {
        std::stringstream ss;
        ss << out;
        result = ss.str();
    }
    int i;
    std::cout << in << std::endl;
    printf("encrypted:\t");
    for(i=0;*(in+i)!=0x00;i++)
        printf("%X ",*(in+i));
    printf("\ndecrypted:\t");
    for(i=0;*(out+i)!=0x00;i++)
        printf("%X ",*(out+i));
    printf("\n");
    delete out;
    return result;
}
