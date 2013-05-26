#include "MainWindow.h"
#include "UserSettings.h"
#include "DBManage.h"

#include <QApplication>
#include "mcheck.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
