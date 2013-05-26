#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DBManage.h"
#include "UserSettings.h"
#include "Dialog.h"

#include <QDateTime>
#include <QFileDialog>
#include <QSignalMapper>
#include <QIcon>


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

    imgLabel.push_back(ui->label);
    imgLabel.push_back(ui->label_2);
    imgLabel.push_back(ui->label_3);
    imgLabel.push_back(ui->label_4);
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
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection & )), this, SLOT(tableSelectionChanged()));

}


void MainWindow::initWidgets()
{
    QIcon icon;
    icon.addFile(QStringLiteral("icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
    this->setWindowTitle("주정차단속관리 프로그램");

    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());

    ui->lineEdit_5->setText(UserSettings::Instance()->getImportPath());
    ui->lineEdit_6->setText(UserSettings::Instance()->getWorkspacePath());
    ui->lineEdit_7->setText(UserSettings::Instance()->getBackUpPath());
    ui->lineEdit_8->setText(UserSettings::Instance()->getExportPath());

    ui->lineEdit_3->setText(UserSettings::Instance()->getSearchLocation());
    ui->lineEdit_4->setText(UserSettings::Instance()->getSearchNum());

    ui->spinBox->setValue(UserSettings::Instance()->getSearchStartId());
    ui->spinBox_2->setValue(UserSettings::Instance()->getSearchEndId());

    ui->tableView->setModel(&DBManage::Instance()->getDbq());
/*    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 220);
    ui->tableView->setColumnWidth(3, 160);
    ui->tableView->setColumnWidth(4, 120);
    ui->tableView->show();*/ //not working

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::registerData()
{
    if (!showPopup("자료들을 등록하시겠습니까?"))
        return;

    CrackdownInfo *data = new CrackdownInfo();
    data->num = "21가1234";
    data->time = "2013-03-07 14:29:43";
    data->location = "apple street";
    data->img[0] = "A.jpg";
    data->img[1] = "B.jpg";
    data->img[2] = "C.jpg";
    data->img[3] = "D.jpg";//dummy data
    data->division = "";

    DBManage::Instance()->addCrackdownInfo(data);
    delete data;
    searchData();
}


void MainWindow::searchData()
{
    DBManage::Instance()->searchCrackdownInfo(ui->checkBox->isChecked(), ui->spinBox->value(), ui->spinBox_2->value(), ui->checkBox_4->isChecked(), ui->lineEdit_4->text(), ui->checkBox_3->isChecked(), ui->lineEdit_3->text(), ui->checkBox_2->isChecked(), ui->dateTimeEdit->text(), ui->dateTimeEdit_2->text(), ui->checkBox_5->isChecked(), ui->comboBox->currentText());
}


void MainWindow::modifyData()
{
    if (!showPopup("선택한 자료를 수정하시겠습니까?"))
        return;

    info.num = ui->lineEdit->text();
    info.location = ui->lineEdit_2->text();
    info.time = ui->dateTimeEdit_3->text();
    DBManage::Instance()->modifyCrackdownInfo(&info);
    searchData();
}


void MainWindow::deleteData()
{
    if (!showPopup("선택한 자료들을 삭제하시겠습니까?"))
        return;

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.empty())
        return;

    for (int i = 0; i < indexes.count(); i++) {
        int r = indexes.at(i).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        DBManage::Instance()->dropCrackdownInfo(id);
    }
    searchData();
}


void MainWindow::determineData()
{
    if (!showPopup("선택한 자료들을 확정하시겠습니까?"))
        return;

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.empty())
        return;

    for (int i = 0; i < indexes.count(); i++) {
        int r = indexes.at(i).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        CrackdownInfo deti = DBManage::Instance()->getCrackdownInfo(id);
        QFile a(deti.img[0]);
        /*QChar exfile[70];

        exfile[0] = deti.time.at(0);
        exfile[1] = deti.time.at(1);
        exfile[2] = deti.time.at(2);
        exfile[3] = deti.time.at(3);
        exfile[4] = deti.time.at(5);
        exfile[5] = deti.time.at(6);
        exfile[6] = deti.time.at(8);
        exfile[7] = deti.time.at(9);
        exfile[8] = deti.time.at(11);
        exfile[9] = deti.time.at(12);
        exfile[10] = deti.time.at(14);
        exfile[11] = deti.time.at(15);
        exfile[12] = deti.time.at(17);
        exfile[13] = deti.time.at(18);

        exfile[14] = deti.num.at(0);
        exfile[15] = deti.num.at(1);
        exfile[16] = deti.num.at(2);
        exfile[17] = deti.num.at(3);
        exfile[18] = deti.num.at(4);
        exfile[19] = deti.num.at(5);
        exfile[20] = (deti.num.size() > 6)? deti.num.at(6) : ' ';
        exfile[21] = (deti.num.size() > 7)? deti.num.at(7) : ' ';*/
        //a.copy(deti.time+""+deti.num+"_"+deti.location);
        QString exfile;
        exfile += deti.time;
        exfile += deti.num;
        exfile.insert(35, deti.location);
        a.copy(QString(exfile));
    }
}


void MainWindow::excelData()
{

}


void MainWindow::option()
{
    UserSettings::Instance()->setImportPath(ui->lineEdit_5->text());
    UserSettings::Instance()->setWorkspacePath(ui->lineEdit_6->text());
    UserSettings::Instance()->setBackUpPath(ui->lineEdit_7->text());
    UserSettings::Instance()->setExportPath(ui->lineEdit_8->text());
    UserSettings::Instance()->setSearchStartId(ui->spinBox->value());
    UserSettings::Instance()->setSearchEndId(ui->spinBox_2->value());
    UserSettings::Instance()->setSearchLocation(ui->lineEdit_3->text());
    UserSettings::Instance()->setSearchNum(ui->lineEdit_4->text());
    UserSettings::Instance()->storeToFile();
}


void MainWindow::selectFile(int index)
{
    QString fileName = QFileDialog::getOpenFileName(this);
    info.img[index] = fileName;
    imgLabel[index]->setPixmap(QPixmap(fileName));
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
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.empty())
        return;
    int r = indexes.at(0).row();
    int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
    info = DBManage::Instance()->getCrackdownInfo(id);
    ui->lineEdit->setText(info.num);
    ui->lineEdit_2->setText(info.location);
    ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(info.time, "yyyy-MM-dd hh:mm:ss"));
    imgLabel[0]->setPixmap(QPixmap(info.img[0]));
    imgLabel[1]->setPixmap(QPixmap(info.img[1]));
    imgLabel[2]->setPixmap(QPixmap(info.img[2]));
    imgLabel[3]->setPixmap(QPixmap(info.img[3]));
}


bool MainWindow::showPopup(const QString str) {
    Dialog d;
    d.setLabel(str);
    return (d.exec() != 0);
}
