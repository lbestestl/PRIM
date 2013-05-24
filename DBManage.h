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
#include <QString>


class DBManage
{
public:
    static DBManage* Instance();

    void addCrackdownInfo(CrackdownInfo*);
    void dropCrackdownInfo(int id);
    void modifyCrackdownInfo(CrackdownInfo*);
    CrackdownInfo searchCrackdownInfo(QString);
    CrackdownInfo searchCrackdownInfo(int id);
    CrackdownInfo searchCrackdownInfo(bool, int, int, bool, QString, bool, QString, bool, QString, QString, bool, QString);
    QSqlDatabase db;
    QSqlQueryModel dbq;

private:
    DBManage();
    ~DBManage();

    static DBManage* instance;
};


#endif // DBMANAGE_H
