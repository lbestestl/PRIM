#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "CrackdownInfo.h"

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QImage>


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
    QVector<QPushButton*> imgLoadButton;
    QVector<QPushButton*> imgMosaicButton;
    QVector<QPushButton*> imgBrightButton;
    QVector<QPushButton*> imgDarkButton;
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
    void aboutAct();
    void helpAct();

    void selectFile(int);
    void selectFolder(int);
    void tableSelectionChanged();
    void tableHorizontalzHeaderClicked(int);
    void mosaicImage(int);
    void brightImage(int);
    void darkImage(int);
};


#endif // MAINWINDOW_H
