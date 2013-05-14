#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include <QFileDialog>
#include <QSignalMapper>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    compilingWidegts();
    connectWidgets();
    initWidgets();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::compilingWidegts()
{
    fileSelectionButton.push_back(ui->pushButton_8);
    fileSelectionButton.push_back(ui->pushButton_9);
    fileSelectionButton.push_back(ui->pushButton_10);
    fileSelectionButton.push_back(ui->pushButton_11);

    folderSelectionButton.push_back(ui->pushButton_15);
    folderSelectionButton.push_back(ui->pushButton_16);
    folderSelectionButton.push_back(ui->pushButton_17);
    folderSelectionButton.push_back(ui->pushButton_18);

    folderPathLine.push_back(ui->lineEdit_5);
    folderPathLine.push_back(ui->lineEdit_6);
    folderPathLine.push_back(ui->lineEdit_7);
    folderPathLine.push_back(ui->lineEdit_8);

    imgLable.push_back(ui->label);
    imgLable.push_back(ui->label_2);
    imgLable.push_back(ui->label_3);
    imgLable.push_back(ui->label_4);
}

void MainWindow::connectWidgets()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(registerData()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(excelData()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(searchData()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(modifyData()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(determineData()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(option()));
    QSignalMapper* sigMapFile = new QSignalMapper(this);
    for (int i = 0; i < fileSelectionButton.size(); ++i) {
        connect(fileSelectionButton[i], SIGNAL(clicked()), sigMapFile, SLOT(map()));
        sigMapFile->setMapping(fileSelectionButton[i], i);
    }
    connect(sigMapFile, SIGNAL(mapped(int)), this, SLOT(selectFile(int)));

    QSignalMapper* sigMapFolder = new QSignalMapper(this);
    for (int i = 0; i < folderSelectionButton.size(); ++i) {
        connect(folderSelectionButton[i], SIGNAL(clicked()), sigMapFolder, SLOT(map()));
        sigMapFolder->setMapping(folderSelectionButton[i], i);
    }
    connect(sigMapFolder, SIGNAL(mapped(int)), this, SLOT(selectFolder(int)));
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(tableSelectionChanged()));

}


void MainWindow::initWidgets()
{
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
    ui->lineEdit_5->setText("a");
    ui->lineEdit_6->setText("b");
    ui->lineEdit_7->setText("c");
    ui->lineEdit_8->setText("d");

    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setColumnWidth(3, 240);
    ui->tableWidget->setColumnWidth(4, 70);
}


void MainWindow::registerData()
{
    CrackdownInfo *data = new CrackdownInfo();
    CrackdownInfo *b = new CrackdownInfo();
    data->num = "11가1234";
    data->time = "2013-02-07 15:59:23";
    data->location = "apple street";
    data->img1 = "/home/lbestestl/Pictures/move/export_img/A.jpg";
    b->num = "991234";
    b->time = "2013-03-01 15:58:42";
    b->location = "banana street";
    b->img1 = "/home/lbestestl/Pictures/move/export_img/b.jpg";
    info.push_back(data);
    info.push_back(b);

}


void MainWindow::searchData()
{
    int c = ui->tableWidget->columnCount();
    infoCell.clear();
    for (; ui->tableWidget->rowCount() > 0; ) {
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
    for (int i = 0; i < info.size(); i++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        infoCell.push_back(new QTableWidgetItem);
        ui->tableWidget->setItem(i, 0, infoCell[c*i]);
        ui->tableWidget->item(i, 0)->setText(QString::number(info[i]->id));
        infoCell.push_back(new QTableWidgetItem);
        ui->tableWidget->setItem(i, 1, infoCell[c*i+1]);
        ui->tableWidget->item(i, 1)->setText(QString::fromStdString(info[i]->num));
        infoCell.push_back(new QTableWidgetItem);
        ui->tableWidget->setItem(i, 2, infoCell[c*i+2]);
        ui->tableWidget->item(i, 2)->setText(QString::fromStdString(info[i]->time));
        infoCell.push_back(new QTableWidgetItem);
        ui->tableWidget->setItem(i, 3, infoCell[c*i+3]);
        ui->tableWidget->item(i, 3)->setText(QString::fromStdString(info[i]->location));
        infoCell.push_back(new QTableWidgetItem);
        ui->tableWidget->setItem(i, 4, infoCell[c*i+4]);
        ui->tableWidget->item(i, 4)->setText(QString::number(info[i]->division));
    }
}


void MainWindow::modifyData()
{
    int r = ui->tableWidget->currentRow();
    if (r >= 0) {
        info[r]->num = ui->lineEdit->text().toStdString();
        ui->tableWidget->item(r, 1)->setText(QString::fromStdString(info[r]->num));
        info[r]->time = ui->dateTimeEdit_3->text().toStdString();
        ui->tableWidget->item(r, 2)->setText(QString::fromStdString(info[r]->time));
        info[r]->location = ui->lineEdit_2->text().toStdString();
        ui->tableWidget->item(r, 3)->setText(QString::fromStdString(info[r]->location));
//      info[r]->division = ui->comboBox_3->currentText().toInt();
//      ui->tableWidget->item(r, 4)->setText(QString::number(info[r]->division));
    }
}


void MainWindow::deleteData()
{
    int r = ui->tableWidget->currentRow();
    int c = ui->tableWidget->columnCount();
    if (r >= 0) {
        for (int i = 0; i < c; i++) {
            delete infoCell[c*r + i];
        }
        infoCell.remove(c*r, c);
        ui->tableWidget->removeRow(r);

        delete info[r];
        info.erase(info.begin()+r, info.begin()+r+1);
    }
    if (r < ui->tableWidget->rowCount())
        ui->tableWidget->selectRow(r);
}


void MainWindow::determineData()
{

}


void MainWindow::excelData()
{

}


void MainWindow::option()
{

}


void MainWindow::selectFile(int index)
{
    QString fileName = QFileDialog::getOpenFileName(this);
    imgLable[index]->setPixmap(QPixmap(fileName));
}


void MainWindow::selectFolder(int index)
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    folderPathLine[index]->setText(dir);
}


void MainWindow::tableSelectionChanged()
{
    int row = ui->tableWidget->currentRow();
    int col = ui->tableWidget->currentColumn();
    if (row >= 0) {
        ui->lineEdit->setText(ui->tableWidget->item(row, 1)->text());
        ui->lineEdit_2->setText(ui->tableWidget->item(row, 3)->text());
        ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(ui->tableWidget->item(row, 2)->text(), "yyyy-MM-dd hh:mm:ss"));
        imgLable[0]->setPixmap(QPixmap(QString::fromStdString(info[row]->img1)));
        imgLable[1]->setPixmap(QPixmap(QString::fromStdString(info[row]->img2)));
        imgLable[2]->setPixmap(QPixmap(QString::fromStdString(info[row]->img3)));
        imgLable[3]->setPixmap(QPixmap(QString::fromStdString(info[row]->img4)));
    }
}
