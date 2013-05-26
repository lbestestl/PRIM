#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "CrackdownInfo.h"

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


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
    bool showPopup(const QString);

    Ui::MainWindow *ui;
    QVector<QPushButton*> folderSelectionButton;
    QVector<QPushButton*> fileSelectionButton;
    QVector<QLineEdit*> folderPathLine;
    QVector<QLabel*> imgLabel;
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
