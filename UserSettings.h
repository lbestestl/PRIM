/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 5. 16. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef USERSETTINGS_H
#define USERSETTINGS_H


#include <QString>


class UserSettings
{
public:
    static UserSettings* Instance();

    void storeToFile();
    void setDefault();

    void setImportPath(QString);

    QString importPath;
    QString exportPath;
    QString workspacePath;
    QString backUpPath;

    int searchStartId;
    int searchEndId;
    QString searchLocation;
    QString searchNum;

private:
    UserSettings();
    static UserSettings* instance;
};


#endif // USERSETTINGS_H
