/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef CRACKDOWNINFO_H
#define CRACKDOWNINFO_H


#include <string>


class CrackdownInfo
{
public:
//    CrackdownInfo();
    int id;
    std::string num;
    std::string time;
    std::string location;
    std::string img1;
    std::string img2;
    std::string img3;
    std::string img4;
    int division;
};


#endif // CRACKDOWNINFO_H