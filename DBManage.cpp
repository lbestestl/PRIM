/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "DBManage.h"

#include <QErrorMessage>
#include <QSqlQuery>


DBManage::DBManage()
{
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName(QDir::currentPath() + QDir::separator() + "crackdowndb.sqlite");
    db->open();
    if (!db->open()) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("cannot open database"));
        em.exec();
        exit(0);
    }
    if (!db->tables().contains("crackdowninfo")) {
        //copy default.sqlite -> crackdowndb.sqlite
        QSqlQuery query(*db);
        query.prepare("CREATE TABLE \"crackdownInfo\" ( \"id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"num\" TEXT NOT NULL, \"location\" TEXT NOT NULL, \"time\" TEXT NOT NULL, \"img1\" TEXT, \"img2\" TEXT, \"img3\" TEXT, \"img4\" TEXT, \"division\" INTEGER NOT NULL)");
        query.exec();
    }
}


DBManage::~DBManage()
{
    db->close();
}


DBManage* DBManage::instance = 0;
DBManage* DBManage::Instance()
{
    if (instance == 0)
        instance == new DBManage();
    return instance;
}


void DBManage::addCrackdownInfo(CrackdownInfo* data)
{
    QSqlQuery query(*db);
//    QString q = "insert into crackdownInfo values(NULL, '" + data->num + "', '" + data->location + "', '" + data->time + "', '" + data->img1 + "', '" + data->img2 + "', '" + data->img3 + "', '" + data->img4 + "', " + QString::number(data->division) + ")";
//    query.exec(q);
    query.prepare("insert into crackdowninfo values(NULL, 'n', 'l', '2013-01-01 13:45:23', 'i1', 'i2', 'i3', 'i4', 1)");
    query.exec();
}


void DBManage::dropCrackdownInfo(CrackdownInfo* data)
{
    QSqlQuery query;
    QString q = "delete from crackdownInfo where id = " + data->id;
    query.exec(q);
}


void DBManage::modifyCrackdownInfo(CrackdownInfo* data)
{
    QSqlQuery query;
    query.prepare("update crackdownInfo set num = ?, set location = ?, set time = ?, set img1 = ?, set img2 = ?, set img3 = ?, set img4 =?, set division = ? where id = ?");
    query.addBindValue(data->num);
    query.addBindValue(data->location);
    query.addBindValue(data->time);
    query.addBindValue(data->img1);
    query.addBindValue(data->img2);
    query.addBindValue(data->img3);
    query.addBindValue(data->img4);
    query.addBindValue(data->division);
    query.addBindValue(data->id);
    query.exec();
}


CrackdownInfo* DBManage::searchCrackdownInfo()
{
    return NULL;
}
