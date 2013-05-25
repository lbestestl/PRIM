/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef CRACKDOWNINFO_H
#define CRACKDOWNINFO_H


#include <QString>


class CrackdownInfo
{
public:
    int id;
    QString num;
    QString time;
    QString location;
    QString img[4];
    QString division;
};


#endif // CRACKDOWNINFO_H
