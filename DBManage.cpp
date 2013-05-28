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
    if (data == NULL)
        return;
    QSqlQuery query(db);
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


void DBManage::dropCrackdownInfo(int id)
{
    if (id < 0)
        return;
    QSqlQuery query(db);
    query.prepare("delete from crackdowninfo where id = ?");
    query.addBindValue(id);
    query.exec();
}


void DBManage::modifyCrackdownInfo(int id, bool numCond, QString num, bool locationCond, QString location, bool timeCond, QString time, bool divisionCond, QString division, bool img1Cond, QString img1, bool img2Cond, QString img2, bool img3Cond, QString img3, bool img4Cond, QString img4)
{
    bool condExist = false;;
    QSqlQuery query(db);
    QString q = "update crackdowninfo";
    if (numCond) {
        if (condExist)
            q += ", num = '" + num + "'";
        else
            q += " set num = '" + num + "'";
        condExist = true;
    }
    if (locationCond) {
        if (condExist)
            q += ", location = '" + location + "'";
        else
            q += " set location = '" + location + "'";
        condExist = true;
    }
    if (timeCond) {
        if (condExist)
            q += ", time = '" + time + "'";
        else
            q += " set time = '" + time + "'";
        condExist = true;
    }
    if (divisionCond) {
        if (condExist)
            q += ", division = '" + division + "'";
        else
            q += " set division = '" + division + "'";
        condExist = true;
    }
    if (img1Cond) {
        if (condExist)
            q += ", img1 = '" + img1 + "'";
        else
            q += "set img1 = '" + img1 + "'";
        condExist = true;
    }
    if (img2Cond) {
        if (condExist)
            q += ", img2 = '" + img2 + "'";
        else
            q += "set img2 = '" + img2 + "'";
        condExist = true;
    }
    if (img3Cond) {
        if (condExist)
            q += ", img3 = '" + img3 + "'";
        else
            q += "set img3 = '" + img3 + "'";
        condExist = true;
    }
    if (img4Cond) {
        if (condExist)
            q += ", img4 = '" + img4 + "'";
        else
            q += "set img4 = '" + img4 + "'";
        condExist = true;
    }
    q += " where id = '" + QString::number(id) + "'";
    query.exec(q);
}

void DBManage::modifyCrackdownInfo(CrackdownInfo* data)
{
    if (data == NULL)
        return;
    QSqlQuery query(db);
    query.prepare("update crackdowninfo set num = ?, location = ?, time = ?, img1 = ?, img2 = ?, img3 = ?, img4 = ?, division = ? where id = ?");
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


CrackdownInfo DBManage::getCrackdownInfo(int id)
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


void DBManage::searchCrackdownInfo(bool idCond, int startId, int endId, bool numCond, QString num, bool locationCond, QString location, bool timeCond, QString startTime, QString endTime, bool divisionCond, QString division)
{
    bool condExist = false;
    QSqlQuery query(db);

    QString q = "select id, num, location, time, division from crackdowninfo";
    if (idCond) {
        if (condExist) {
            q += " and id >= " + QString::number(startId) + " and id <= " + QString::number(endId);
        } else {
            q += " where id >= " + QString::number(startId) + " and id <= " + QString::number(endId);
        }
        condExist = true;
    }
    if (numCond) {
        if (condExist) {
            q += " and num like '%" + num + "%'";
        } else {
            q += " where num like '%" + num + "%'";
        }
        condExist = true;
    }
    if (locationCond) {
        if (condExist) {
            q += " and location like '%" + location + "%'";
        } else {
            q += " where location like '%" + location + "%'";
        }
        condExist = true;
    }
    if (timeCond) {
        if (condExist) {
            q += " and time >= '" + startTime + "' and time <= '" + endTime + "'";
        } else {
            q += " where time >= '" + startTime + "' and time <= '" + endTime + "'";
        }
        condExist = true;
    }
    if (divisionCond) {
        if (condExist) {
            q += " and division = '" + division + "'";
        } else {
            q += " where division = '" + division + "'";
        }
        condExist = true;
    }
    condExist = query.exec(q);
    dbq.setQuery(q);
}
