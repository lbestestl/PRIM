#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "CrackdownInfo.h"

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidgetItem>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    void compilingWidegts();
    void connectWidgets();
    void initWidgets();

    Ui::MainWindow *ui;
    QVector<QPushButton*> folderSelectionButton;
    QVector<QPushButton*> fileSelectionButton;
    QVector<QLineEdit*> folderPathLine;
    QVector<QLabel*> imgLabel;
    QVector<QTableWidgetItem*> infoCell;
//    std::vector<CrackdownInfo*> info;
    CrackdownInfo info;

private slots:
    void registerData();
    void searchData();
    void modifyData();
    void deleteData();
    void determineData();
    void excelData();
    void option();
    void selectFile(int index);
    void selectFolder(int index);
    void tableSelectionChanged();
};


#endif // MAINWINDOW_H
