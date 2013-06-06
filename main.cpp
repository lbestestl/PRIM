#include "MainWindow.h"
#include "UserSettings.h"
#include "DBManage.h"

#include <QApplication>
#include <QSharedData>
#include <QErrorMessage>
#include <QStyle>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QApplication a(argc, argv);
    a.setApplicationName("PRIM");
    a.setApplicationVersion("1306.1");
    //중복 실행 방지
    QSharedMemory shared("01adf13gmnwe2hj5qhxc");
    if (!shared.create(512, QSharedMemory::ReadWrite)) {
        QErrorMessage em;
        em.showMessage(QString::fromStdString("프로그램이 실행 중입니다"));
        em.exec();
        exit(0);
    }
    MainWindow w;
    w.show();
    
    return a.exec();
}
