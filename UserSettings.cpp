/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 16. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "UserSettings.h"

#include <QFile>
#include <QTextStream>
#include <QErrorMessage>


UserSettings::UserSettings()
{
    QFile f("settings.dat");
    if (!f.exists()) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("Does not exist file. settings.dat"));
        em.exec();
    } else if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("cannot open or create settings.dat"));
        em.exec();
        exit(0);
    } else {
        QTextStream in(&f);
        importPath = in.readLine();
        workspacePath = in.readLine();
        backUpPath = in.readLine();
        exportPath = in.readLine();
        searchStartId = in.readLine().toInt();
        searchEndId = in.readLine().toInt();
        searchLocation = in.readLine();
        searchNum = in.readLine();
    }
}


UserSettings* UserSettings::instance = 0;
UserSettings* UserSettings::Instance()
{
    if (instance == 0)
        instance = new UserSettings();
    return instance;
}


void UserSettings::storeToFile() {
    QFile f("settings.dat");
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("cannot open or create settings.dat"));
        em.exec();
        exit(0);
    } else {
        QTextStream out(&f);
        out << importPath << "\n"
            << workspacePath << "\n"
            << backUpPath << "\n"
            << exportPath << "\n"
            << searchStartId << "\n"
            << searchEndId << "\n"
            << searchLocation << "\n"
            << searchNum;
    }
}


void UserSettings::setImportPath(QString a)
{
    importPath = a;
}
