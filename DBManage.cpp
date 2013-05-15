/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "DBManage.h"

#include <QErrorMessage>


DBManage::DBManage()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath() + QDir::separator() + "crackdowndb.sqlite");
    db.open();
    if (!db.open()) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("cannot open database"));
        em.exec();
        exit(0);
    }
    if (!db.tables().contains("crackdownInfo")) {
        //copy default.sqlite -> crackdowndb.sqlite
    }
}


DBManage::~DBManage()
{
    db.close();
}


void DBManage::addCrackdownInfo(CrackdownInfo* data)
{

}


void DBManage::dropCrackdownInfo(CrackdownInfo* data)
{
}


void DBManage::modifyCrackdownInfo(CrackdownInfo* data)
{
}


CrackdownInfo* DBManage::searchCrackdownInfo()
{
    return NULL;
}