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
    void compilingWidgets();
    void connectWidgets();
    void initWidgets();
    bool showPopup(const QString);

    Ui::MainWindow *ui;
    QVector<QPushButton*> folderSelectionButton;
    QVector<QPushButton*> imageSelectionButton;
    QVector<QPushButton*> mosaicButton;
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
    void savePreference();
    void selectFile(int index);
    void selectFolder(int index);
    void tableSelectionChanged();
    void tableHorizontalzHeaderClicked(int);
    void savePreference
};


#endif // MAINWINDOW_H
