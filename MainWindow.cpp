#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DBManage.h"
#include "UserSettings.h"
#include "Dialog.h"

#include <QDateTime>
#include <QFileDialog>
#include <QSignalMapper>
#include <QIcon>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    compilingWidgets();
    initWidgets();
    connectWidgets();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::compilingWidgets()
{
    imageSelectionButton.push_back(ui->pushButton_8);
    imageSelectionButton.push_back(ui->pushButton_9);
    imageSelectionButton.push_back(ui->pushButton_10);
    imageSelectionButton.push_back(ui->pushButton_11);

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

    mosaicButton.push_back(ui->pushButton_21);
    mosaicButton.push_back(ui->pushButton_24);
    mosaicButton.push_back(ui->pushButton_27);
    mosaicButton.push_back(ui->pushButton_30);
}

void MainWindow::connectWidgets()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(registerData()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(excelData()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(searchData()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(modifyData()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(determineData()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(savePreference()));
    QSignalMapper* sigMapFile = new QSignalMapper(this);
    for (int i = 0; i < imageSelectionButton.size(); ++i) {
        connect(imageSelectionButton[i], SIGNAL(clicked()), sigMapFile, SLOT(map()));
        sigMapFile->setMapping(imageSelectionButton[i], i);
    }
    connect(sigMapFile, SIGNAL(mapped(int)), this, SLOT(selectFile(int)));

    QSignalMapper* sigMapFolder = new QSignalMapper(this);
    for (int i = 0; i < folderSelectionButton.size(); ++i) {
        connect(folderSelectionButton[i], SIGNAL(clicked()), sigMapFolder, SLOT(map()));
        sigMapFolder->setMapping(folderSelectionButton[i], i);
    }
    connect(sigMapFolder, SIGNAL(mapped(int)), this, SLOT(selectFolder(int)));
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection & )), this, SLOT(tableSelectionChanged()));
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(tableHorizontalzHeaderClicked(int)));
}


void MainWindow::initWidgets()
{
    QIcon mainIcon;
    mainIcon.addFile(QStringLiteral("main_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(mainIcon);
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
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);

    QIcon imageIcon;
    imageIcon.addFile(QStringLiteral("image_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->pushButton_8->setIcon(imageIcon);
    ui->pushButton_9->setIcon(imageIcon);
    ui->pushButton_10->setIcon(imageIcon);
    ui->pushButton_11->setIcon(imageIcon);

    QIcon arrowUpIcon;
    arrowUpIcon.addFile(QStringLiteral("arrup_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui->pushButton_19->setIcon(arrowUpIcon);

    QIcon arrowDownIcon;
    arrowDownIcon.addFile(QStringLiteral("arrdown_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->pushButton_20->setIcon(arrowDownIcon);

    QIcon paletteIcon;
    paletteIcon.addFile(QStringLiteral("palette_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    for (int i = 0; i < mosaicButton.size(); i++)
        mosaicButton[i]->setIcon(paletteIcon);
}


void MainWindow::registerData()
{
    if (!showPopup("자료를 등록하시겠습니까?"))
        return;
    QDir dir;
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.gif";
    dir.setNameFilters(filters);
    dir.setPath(UserSettings::Instance()->getImportPath());

    QFileInfoList list = dir.entryInfoList();
    while (!list.empty()) {
        QFileInfo fileInfo = list.first();
        list.pop_front();
        QFile f(fileInfo.filePath());
        f.copy(UserSettings::Instance()->getWorkspacePath() + QDir::separator() + fileInfo.fileName());
        f.remove();
        qDebug() << fileInfo.fileName().toLocal8Bit().left(14).trimmed();
        qDebug() << fileInfo.fileName().toLocal8Bit().mid(26, 22).trimmed();
    }

    //DBManage::Instance()->addCrackdownInfo(data);
    searchData();
}


void MainWindow::searchData()
{
    DBManage::Instance()->searchCrackdownInfo(ui->checkBox->isChecked(), ui->spinBox->value(), ui->spinBox_2->value(), ui->checkBox_4->isChecked(), ui->lineEdit_4->text(), ui->checkBox_3->isChecked(), ui->lineEdit_3->text(), ui->checkBox_2->isChecked(), ui->dateTimeEdit->text(), ui->dateTimeEdit_2->text(), ui->checkBox_5->isChecked(), ui->comboBox->currentText(), ui->tableView->horizontalHeader()->sortIndicatorSection(), ui->tableView->horizontalHeader()->sortIndicatorOrder());
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 110);
    ui->tableView->setColumnWidth(2, 220);
    ui->tableView->setColumnWidth(3, 160);
    ui->tableView->setColumnWidth(4, 120);
}


void MainWindow::modifyData()
{
    if (!showPopup("선택한 자료를 수정하시겠습니까?"))
        return;

    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    if (indexes.empty()) {
        //선택한 자료가 없을 경우
        return;
    } else if (indexes.count() == 1) {
        //선택한 자료가 1개일 경우
        int r = indexes.at(0).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        DBManage::Instance()->modifyCrackdownInfo(id, ui->checkBox_6->isChecked(), ui->lineEdit->text(), ui->checkBox_7->isChecked(), ui->lineEdit_2->text(), ui->checkBox_8->isChecked(), ui->dateTimeEdit_3->text(), ui->checkBox_9->isChecked(), ui->comboBox_3->currentText(), ui->checkBox_10->isChecked(), info.img[0], ui->checkBox_11->isChecked(), info.img[1], ui->checkBox_12->isChecked(), info.img[2], ui->checkBox_13->isChecked(), info.img[3]);
    } else {
        //선택한 자료가 복수일 경우 (일시의 경우 날짜만 수정)
        for (int i = 0; i < indexes.count(); i++) {
            int r = indexes.at(i).row();
            int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
            QString dt = ui->dateTimeEdit_3->date().toString("yyyy-MM-dd");
            dt += " " + QDateTime::fromString(DBManage::Instance()->getCrackdownInfo(id).time, "yyyy-MM-dd hh:mm:ss").time().toString("hh:mm:ss");
            DBManage::Instance()->modifyCrackdownInfo(id, ui->checkBox_6->isChecked(), ui->lineEdit->text(), ui->checkBox_7->isChecked(), ui->lineEdit_2->text(), ui->checkBox_8->isChecked(), dt, ui->checkBox_9->isChecked(), ui->comboBox_3->currentText(), ui->checkBox_10->isChecked(), info.img[0], ui->checkBox_11->isChecked(), info.img[1], ui->checkBox_12->isChecked(), info.img[2], ui->checkBox_13->isChecked(), info.img[3]);
        }
    }
    searchData();
}


void MainWindow::deleteData()
{
    if (!showPopup("선택한 자료를 삭제하시겠습니까?"))
        return;

    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
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
    if (!showPopup("선택한 자료를 확정하시겠습니까?"))
        return;

    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < indexes.count(); i++) {
        int r = indexes.at(i).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        CrackdownInfo deti = DBManage::Instance()->getCrackdownInfo(id);

        QByteArray exfile;
        exfile += QDateTime::fromString(deti.time, "yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss");
        exfile += deti.num;
        exfile.insert(26, "00000");
        exfile.insert(31, deti.location);
        exfile.insert(56, "999");
        exfile.insert(65, "A");
        exfile.insert(66, ".jpg");
        QFile a(deti.img[0]);
        a.copy(UserSettings::Instance()->getExportPath() + QDir::separator() + exfile);
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
        /*QString exfile;
        exfile += QDateTime::fromString(deti.time, "yyyy-MM-dd hh:mm:ss").toString("yyyyMMddhhmmss");
        exfile += deti.num;
        exfile.insert(26, "00000");
        exfile.insert(31, deti.location);
        qDebug() << deti.location.size();
        qDebug() << deti.location.length();
        qDebug() << deti.location.
        exfile.insert(56, "999");
        exfile.insert(65, "A");
        exfile.insert(66, ".jpg");
        a.copy(exfile);*/
    }
    /*QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.empty())
        return;

    for (int i = 0; i < indexes.count(); i++) {
        int r = indexes.at(i).row();
        int id = ui->tableView->model()->data(ui->tableView->model()->index(r, 0)).toInt();
        CrackdownInfo deti = DBManage::Instance()->getCrackdownInfo(id);
        QFile a(deti.img[0]);
    }*/
}


void MainWindow::excelData()
{

}


void MainWindow::savePreference()
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
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    folderPathLine[index]->setText(dir);
}


void MainWindow::tableSelectionChanged()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    if (indexes.empty()) {
        return;
    } else if (indexes.count() == 1) {
        ui->checkBox_6->setCheckState(Qt::Checked);
        ui->checkBox_7->setCheckState(Qt::Checked);
        ui->checkBox_8->setCheckState(Qt::Checked);
        ui->checkBox_9->setCheckState(Qt::Checked);
        ui->checkBox_6->setChecked(true);
        ui->checkBox_7->setChecked(true);
        ui->checkBox_8->setChecked(true);
        ui->checkBox_9->setChecked(true);
        ui->checkBox_10->setHidden(false);
        ui->checkBox_11->setHidden(false);
        ui->checkBox_12->setHidden(false);
        ui->checkBox_13->setHidden(false);
        ui->dateTimeEdit_3->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

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
    } else {
        ui->checkBox_6->setCheckState(Qt::Unchecked);
        ui->checkBox_7->setCheckState(Qt::Unchecked);
        ui->checkBox_8->setCheckState(Qt::Unchecked);
        ui->checkBox_9->setCheckState(Qt::Unchecked);
        ui->checkBox_6->setChecked(false);
        ui->checkBox_7->setChecked(false);
        ui->checkBox_8->setChecked(false);
        ui->checkBox_9->setChecked(false);
        ui->checkBox_10->setCheckState(Qt::Unchecked);
        ui->checkBox_11->setCheckState(Qt::Unchecked);
        ui->checkBox_12->setCheckState(Qt::Unchecked);
        ui->checkBox_13->setCheckState(Qt::Unchecked);
        ui->checkBox_10->setHidden(true);
        ui->checkBox_11->setHidden(true);
        ui->checkBox_12->setHidden(true);
        ui->checkBox_13->setHidden(true);

        ui->dateTimeEdit_3->setDisplayFormat("yyyy-MM-dd");
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        imgLabel[0]->setPixmap(QPixmap(""));
        imgLabel[1]->setPixmap(QPixmap(""));
        imgLabel[2]->setPixmap(QPixmap(""));
        imgLabel[3]->setPixmap(QPixmap(""));
    }
}


void MainWindow::tableHorizontalzHeaderClicked(int i)
{
    DBManage::Instance()->searchCrackdownInfo(ui->checkBox->isChecked(), ui->spinBox->value(), ui->spinBox_2->value(), ui->checkBox_4->isChecked(), ui->lineEdit_4->text(), ui->checkBox_3->isChecked(), ui->lineEdit_3->text(), ui->checkBox_2->isChecked(), ui->dateTimeEdit->text(), ui->dateTimeEdit_2->text(), ui->checkBox_5->isChecked(), ui->comboBox->currentText(), i, ui->tableView->horizontalHeader()->sortIndicatorOrder());
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 110);
    ui->tableView->setColumnWidth(2, 220);
    ui->tableView->setColumnWidth(3, 160);
    ui->tableView->setColumnWidth(4, 120);
}


bool MainWindow::showPopup(const QString str)
{
    Dialog d;
    d.setLabel(str);
    return (d.exec() != 0);
}
