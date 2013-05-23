/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 10. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "DBManage.h"

#include <QErrorMessage>
#include <QSqlQuery>
#include <QtDebug>


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
    if (!db.tables().contains("crackdowninfo")) {
        //copy default.sqlite -> crackdowndb.sqlite
        QSqlQuery query(db);
        query.prepare("CREATE TABLE \"crackdowninfo\" ( \"id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"num\" TEXT NOT NULL, \"location\" TEXT NOT NULL, \"time\" TEXT NOT NULL, \"img1\" TEXT, \"img2\" TEXT, \"img3\" TEXT, \"img4\" TEXT, \"division\" TEXT NOT NULL)");
        query.exec();
    }

}


DBManage::~DBManage()
{
    db.close();
    delete instance;
    instance = NULL;
}


DBManage* DBManage::instance = 0;
DBManage* DBManage::Instance()
{
    if (instance == 0)
        instance = new DBManage;
    return instance;
}


void DBManage::addCrackdownInfo(CrackdownInfo* data)
{
    QSqlQuery query(db);
    if (data != NULL) {
        query.prepare("insert into crackdowninfo values (NULL, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(data->num);
        query.addBindValue(data->location);
        query.addBindValue(data->time);
        query.addBindValue(data->img[0]);
        query.addBindValue(data->img[1]);
        query.addBindValue(data->img[2]);
        query.addBindValue(data->img[3]);
        query.addBindValue(data->division);
        query.exec();
    }
}


void DBManage::dropCrackdownInfo(int id)
{
    QSqlQuery query(db);
    query.prepare("delete from crackdowninfo where id = ?");
    query.addBindValue(id);
    query.exec();
}


void DBManage::modifyCrackdownInfo(CrackdownInfo* data)
{
    QSqlQuery query(db);
    query.prepare("update crackdowninfo set num = ?, location = ?, time = ?, img1 = ?, img2 = ?, img3 = ?, img4 =?, division = ? where id = ?");
    query.addBindValue(data->num);
    query.addBindValue(data->location);
    query.addBindValue(data->time);
    query.addBindValue(data->img[0]);
    query.addBindValue(data->img[1]);
    query.addBindValue(data->img[2]);
    query.addBindValue(data->img[3]);
    query.addBindValue(data->division);
    query.addBindValue(data->id);
    query.exec();
}


CrackdownInfo DBManage::searchCrackdownInfo(QString q)
{
    QSqlQuery query(db);
    query.exec(q);
    CrackdownInfo ci;
    return ci;
}


CrackdownInfo DBManage::temp(int id)
{

    QString q = "select * from crackdowninfo where id = " + QString::number(id);
    QSqlQuery query(q, db);
    CrackdownInfo ci;
    ci.id = id;
    if (query.next()) {
        ci.num = query.value(query.record().indexOf("num")).toString();
        ci.location = query.value(query.record().indexOf("location")).toString();
        ci.time = query.value(query.record().indexOf("time")).toString();
        ci.img[0] = query.value(query.record().indexOf("img1")).toString();
        ci.img[1] = query.value(query.record().indexOf("img2")).toString();
        ci.img[2] = query.value(query.record().indexOf("img3")).toString();
        ci.img[3] = query.value(query.record().indexOf("img4")).toString();
        ci.division = query.value(query.record().indexOf("division")).toString();
    }
    return ci;
}
