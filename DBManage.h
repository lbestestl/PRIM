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
    void modifyCrackdownInfo(int, bool, QString, bool, QString, bool, QString, bool, QString, bool, QString, bool, QString, bool, QString, bool, QString);
    CrackdownInfo getCrackdownInfo(int id);
    void searchCrackdownInfo(bool, int, int, bool, QString, bool, QString, bool, QString, QString, bool, QString, int, Qt::SortOrder);

    inline QSqlQueryModel& getDbq() {return dbq;}

private:
    DBManage();
    ~DBManage();

    QSqlDatabase db;
    QSqlQueryModel dbq;

    static DBManage* instance;
};


#endif // DBMANAGE_H
