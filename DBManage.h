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
    static DBManage* Instance();

    void addCrackdownInfo(CrackdownInfo*);
    void dropCrackdownInfo(CrackdownInfo*);
    void modifyCrackdownInfo(CrackdownInfo*);
    CrackdownInfo* searchCrackdownInfo(QString);

private:
    DBManage();
    ~DBManage();
    QSqlDatabase db;
    static DBManage* instance;

};


#endif // DBMANAGE_H
