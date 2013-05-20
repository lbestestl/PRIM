#include "MainWindow.h"
#include "UserSettings.h"
#include "DBManage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    UserSettings::Instance();
    DBManage::Instance();
    
    return a.exec();
}
