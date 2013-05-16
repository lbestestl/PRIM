#include "MainWindow.h"
#include "UserSettings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    theUserSettings();
    
    return a.exec();
}
