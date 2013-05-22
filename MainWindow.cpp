#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DBManage.h"
#include "UserSettings.h"

#include <QDateTime>
#include <QFileDialog>
#include <QSignalMapper>
#include <QErrorMessage>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWidgets();
    compilingWidegts();
    connectWidgets();
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
    connect(ui->tableView, SIGNAL(selectionChanged(const QItemSelection & )), this, SLOT(tableSelectionChanged()));

}


void MainWindow::initWidgets()
{
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());

    ui->lineEdit_5->setText(UserSettings::Instance()->importPath);
    ui->lineEdit_6->setText(UserSettings::Instance()->workspacePath);
    ui->lineEdit_7->setText(UserSettings::Instance()->backUpPath);
    ui->lineEdit_8->setText(UserSettings::Instance()->exportPath);

    ui->lineEdit_3->setText(UserSettings::Instance()->searchLocation);
    ui->lineEdit_4->setText(UserSettings::Instance()->searchNum);

    ui->spinBox->setValue(UserSettings::Instance()->searchStartId);
    ui->spinBox_2->setValue(UserSettings::Instance()->searchEndId);

    ui->tableView->setModel(&DBManage::Instance()->dbq);
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 220);
    ui->tableView->setColumnWidth(3, 160);
    ui->tableView->setColumnWidth(4, 120);
    ui->tableView->show();

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::registerData()
{

    CrackdownInfo *data = new CrackdownInfo();
    data->num = "11가1234";
    data->time = "2013-02-07 15:59:23";
    data->location = "apple street";
    data->img1 = "/home/lbestestl/Pictures/move/export_img/A.jpg";
    data->img2 = "/home/lbestestl/Pictures/move/export_img/B.jpg";
    data->img3 = "/home/lbestestl/Pictures/move/export_img/C.jpg";
    data->img4 = "/home/lbestestl/Pictures/move/export_img/D.jpg";

    DBManage::Instance()->addCrackdownInfo(data);
    delete data;

}


void MainWindow::searchData()
{
    bool cond = false;
    QString q = "Select id, num, location, time, division from crackdowninfo";
    if (ui->checkBox->isChecked()) {
        //순번
        if (!cond) {
            q += " where id >= " + QString::number(ui->spinBox->value()) + " and id <= " + QString::number(ui->spinBox_2->value());
        } else {
            q += " and id >= " + QString::number(ui->spinBox->value()) + " and id <= " + QString::number(ui->spinBox_2->value());
        }
        cond = true;
    }
    if (ui->checkBox_2->isChecked()) {
        //시간
        if (!cond) {
            q += " where time >= '" + ui->dateTimeEdit->text() + "' and time <= '" + ui->dateTimeEdit_2->text() + "'";
        } else {
            q += " and time >= '" + ui->dateTimeEdit->text() + "' and time <= '" + ui->dateTimeEdit_2->text() + "'";
        }
        cond = true;
    }
    if (ui->checkBox_3->isChecked()) {
        //장소
        if (!cond) {
            q += " where location like '%" + ui->lineEdit_3->text() + "%'";
        } else {
            q += " and location like '%" + ui->lineEdit_3->text() + "%'";
        }
        cond = true;
    }
    if (ui->checkBox_4->isChecked()) {
        //번호
        if (!cond) {
            q += " where num like '%" + ui->lineEdit_4->text() + "%'";
        } else {
            q += " and num like '%" + ui->lineEdit_4->text() + "%'";
        }
        cond = true;
    }
    if (ui->checkBox_5->isChecked()) {
        if (!cond) {
            q += " where division = '" + ui->comboBox->currentText() + "'";
        } else {
            q += " and division = '" + ui->comboBox->currentText() + "'";
        }
        cond = true;
    }
    ui->label_23->setText(q);
    DBManage::Instance()->dbq.setQuery(q);


    DBManage::Instance()->searchCrackdownInfo(q);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->show();
}


void MainWindow::modifyData()
{

}


void MainWindow::deleteData()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    for (int i = 0; i < indexes.count(); i++) {
        int r = indexes.at(i).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        DBManage::Instance()->dropCrackdownInfo(id);
    }
    searchData();
}


void MainWindow::determineData()
{

}


void MainWindow::excelData()
{

}


void MainWindow::option()
{
    UserSettings::Instance()->importPath = ui->lineEdit_5->text();
    UserSettings::Instance()->workspacePath = ui->lineEdit_6->text();
    UserSettings::Instance()->backUpPath = ui->lineEdit_7->text();
    UserSettings::Instance()->exportPath = ui->lineEdit_8->text();
    UserSettings::Instance()->searchStartId = ui->spinBox->value();
    UserSettings::Instance()->searchEndId = ui->spinBox_2->value();
    UserSettings::Instance()->searchLocation = ui->lineEdit_3->text();
    UserSettings::Instance()->searchNum = ui->lineEdit_4->text();
    UserSettings::Instance()->storeToFile();
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
    ui->tableView->currentIndex();
    int row = 0;
    if (row >= 0) {
//        ui->lineEdit->setText(ui->tableView->item(row, 1)->text());
//        ui->lineEdit_2->setText(ui->tableView->item(row, 3)->text());
//        ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(ui->tableView->item(row, 2)->text(), "yyyy-MM-dd hh:mm:ss"));
        imgLable[0]->setPixmap(QPixmap(info[row]->img1));
        imgLable[1]->setPixmap(QPixmap(info[row]->img2));
        imgLable[2]->setPixmap(QPixmap(info[row]->img3));
        imgLable[3]->setPixmap(QPixmap(info[row]->img4));
    }
}
