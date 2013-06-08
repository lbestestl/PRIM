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

    inline void setId(QString str) {id = str;}
    inline QString getId() {return id;}
    inline void setPassword(QString str) {password = str;}
    inline QString getPassword() {return password;}
    inline void setImportPath(QString str) {importPath = str;}
    inline QString getImportPath() {return importPath;}
    inline void setExportPath(QString str) {exportPath = str;}
    inline QString getExportPath() {return exportPath;}
    inline void setWorkspacePath(QString str) {workspacePath = str;}
    inline QString getWorkspacePath() {return workspacePath;}
    inline void setBackUpPath(QString str) {backUpPath = str;}
    inline QString getBackUpPath() {return backUpPath;}
    inline void setSearchStartId(int val) {searchStartId = val;}
    inline int getSearchStartId() {return searchStartId;}
    inline void setSearchEndId(int val) {searchEndId = val;}
    inline int getSearchEndId() {return searchEndId;}
    inline void setSearchLocation(QString str) {searchLocation = str;}
    inline QString getSearchLocation() {return searchLocation;}
    inline void setSearchNum(QString str) {searchNum = str;}
    inline QString getSearchNum() {return searchNum;}

private:
    UserSettings();
    ~UserSettings();

    static UserSettings* instance;
    QString id;
    QString password;

    QString importPath;
    QString exportPath;
    QString workspacePath;
    QString backUpPath;

    int searchStartId;
    int searchEndId;
    QString searchLocation;
    QString searchNum;
};


#endif // USERSETTINGS_H
