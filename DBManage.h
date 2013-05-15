/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DBMANAGE_H
#define DBMANAGE_H


#include "CrackdownInfo.h"
#include <QtSql/QtSql>


class DBManage
{
public:
    DBManage();
    ~DBManage();

    void addCrackdownInfo(CrackdownInfo*);
    void dropCrackdownInfo(CrackdownInfo*);
    void modifyCrackdownInfo(CrackdownInfo*);
    CrackdownInfo* searchCrackdownInfo();

private:
    QSqlDatabase db;

};


#endif // DBMANAGE_H
