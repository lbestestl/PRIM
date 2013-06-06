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
#include <QMessageBox>


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
    imgLoadButton.push_back(ui->img1LoadButton);
    imgLoadButton.push_back(ui->img2LoadButton);
    imgLoadButton.push_back(ui->img3LoadButton);
    imgLoadButton.push_back(ui->img4LoadButton);

    folderSelectionButton.push_back(ui->importFolderButton);
    folderSelectionButton.push_back(ui->workspaceFolderButton);
    folderSelectionButton.push_back(ui->backUpFolderButton);
    folderSelectionButton.push_back(ui->exportFolderLabel);

    folderPathLine.push_back(ui->importPathEdit);
    folderPathLine.push_back(ui->workspacePathEdit);
    folderPathLine.push_back(ui->backUpPathEdit);
    folderPathLine.push_back(ui->exportPathEdit);

    imgLabel.push_back(ui->img1Label);
    imgLabel.push_back(ui->img2Label);
    imgLabel.push_back(ui->img3Label);
    imgLabel.push_back(ui->img4Label);

    imgMosaicButton.push_back(ui->img1MosaicButton);
    imgMosaicButton.push_back(ui->img2MosaicButton);
    imgMosaicButton.push_back(ui->img3MosaicButton);
    imgMosaicButton.push_back(ui->img4MosaicButton);

    imgBrightButton.push_back(ui->img1BrightButton);
    imgBrightButton.push_back(ui->img2BrightButton);
    imgBrightButton.push_back(ui->img3BrightButton);
    imgBrightButton.push_back(ui->img4BrightButton);

    imgDarkButton.push_back(ui->img1DarkButton);
    imgDarkButton.push_back(ui->img2DarkButton);
    imgDarkButton.push_back(ui->img3DarkButton);
    imgDarkButton.push_back(ui->img4DarkButton);
}


void MainWindow::initWidgets()
{
    QIcon mainIcon;
    mainIcon.addFile(QStringLiteral("main_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(mainIcon);
    this->setWindowTitle("주정차단속관리 프로그램");

    ui->searchStartTimeEdit->setDate(QDate::currentDate());
    ui->searchEndTimeEdit->setDate(QDate::currentDate());
    ui->editTimeEdit->setDateTime(QDateTime::currentDateTime());

    ui->importPathEdit->setText(UserSettings::Instance()->getImportPath());
    ui->workspacePathEdit->setText(UserSettings::Instance()->getWorkspacePath());
    ui->backUpPathEdit->setText(UserSettings::Instance()->getBackUpPath());
    ui->exportPathEdit->setText(UserSettings::Instance()->getExportPath());

    ui->searchLocationLineEdit->setText(UserSettings::Instance()->getSearchLocation());
    ui->searchNumLineEdit->setText(UserSettings::Instance()->getSearchNum());
    ui->searchStartIdSpinBox->setValue(UserSettings::Instance()->getSearchStartId());
    ui->searchEndIdSpinBox->setValue(UserSettings::Instance()->getSearchEndId());

    ui->tableView->setModel(&DBManage::Instance()->getDbq());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);

    QIcon imgLoadIcon;
    imgLoadIcon.addFile(QStringLiteral("image_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    for (int i = 0; i < imgLoadButton.size(); i++)
        imgLoadButton[i]->setIcon(imgLoadIcon);

    QIcon arrowUpIcon;
    arrowUpIcon.addFile(QStringLiteral("arrup_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    for (int i = 0; i < imgBrightButton.size(); i++)
        imgBrightButton[i]->setIcon(arrowUpIcon);

    QIcon arrowDownIcon;
    arrowDownIcon.addFile(QStringLiteral("arrdown_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    for (int i = 0; i < imgDarkButton.size(); i++)
        imgDarkButton[i]->setIcon(arrowDownIcon);

    QIcon paletteIcon;
    paletteIcon.addFile(QStringLiteral("palette_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    for (int i = 0; i < imgMosaicButton.size(); i++)
        imgMosaicButton[i]->setIcon(paletteIcon);
}


void MainWindow::connectWidgets()
{
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(registerData()));
    connect(ui->excelButton, SIGNAL(clicked()), this, SLOT(excelData()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchData()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(modifyData()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(ui->determineButton, SIGNAL(clicked()), this, SLOT(determineData()));
    connect(ui->savePreferenceButton, SIGNAL(clicked()), this, SLOT(savePreference()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(aboutAct()));

    QSignalMapper* sigMapFile = new QSignalMapper(this);
    for (int i = 0; i < imgLoadButton.size(); ++i) {
        connect(imgLoadButton[i], SIGNAL(clicked()), sigMapFile, SLOT(map()));
        sigMapFile->setMapping(imgLoadButton[i], i);
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

    QSignalMapper* sigMapMosaicButton = new QSignalMapper(this);
    for (int i = 0; i < imgMosaicButton.size(); i++) {
         connect(imgMosaicButton[i], SIGNAL(clicked()), sigMapMosaicButton, SLOT(map()));
         sigMapMosaicButton->setMapping(imgMosaicButton[i], i);
    }
    connect(sigMapMosaicButton, SIGNAL(mapped(int)), this, SLOT(mosaicImage(int)));

    QSignalMapper* sigMapBrightButton = new QSignalMapper(this);
    for (int i = 0; i < imgBrightButton.size(); i++) {
         connect(imgBrightButton[i], SIGNAL(clicked()), sigMapBrightButton, SLOT(map()));
         sigMapBrightButton->setMapping(imgBrightButton[i], i);
    }
    connect(sigMapBrightButton, SIGNAL(mapped(int)), this, SLOT(brightImage(int)));

    QSignalMapper* sigMapDarkButton = new QSignalMapper(this);
    for (int i = 0; i < imgDarkButton.size(); i++) {
         connect(imgDarkButton[i], SIGNAL(clicked()), sigMapDarkButton, SLOT(map()));
         sigMapDarkButton->setMapping(imgDarkButton[i], i);
    }
    connect(sigMapDarkButton, SIGNAL(mapped(int)), this, SLOT(darkImage(int)));
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
    DBManage::Instance()->searchCrackdownInfo(ui->searchOpIdCheckBox->isChecked(), ui->searchStartIdSpinBox->value(), ui->searchEndIdSpinBox->value(), ui->searchOpNumCheckBox->isChecked(), ui->searchNumLineEdit->text(), ui->searchOpLocationCheckBox->isChecked(), ui->searchLocationLineEdit->text(), ui->searchOpTimeCheckBox->isChecked(), ui->searchStartTimeEdit->text(), ui->searchEndTimeEdit->text(), ui->searchOpDivisionCheckBox->isChecked(), ui->searchDivisionComboBox->currentText(), ui->tableView->horizontalHeader()->sortIndicatorSection(), ui->tableView->horizontalHeader()->sortIndicatorOrder());
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
        DBManage::Instance()->modifyCrackdownInfo(ui->tableView->model()->data(ui->tableView->model()->index(indexes.at(0).row(), 0)).toInt(), ui->editOpNumCheckBox->isChecked(), ui->editNumLineEdit->text(), ui->editOpLocationCheckBox->isChecked(), ui->editLocationLineEdit->text(), ui->editOpTimeCheckBox->isChecked(), ui->editTimeEdit->text(), ui->editOpDivisionCheckBox->isChecked(), ui->editDivisionComboBox->currentText(), ui->editOpImg1CheckBox->isChecked(), info.img[0], ui->editOpImg2CheckBox->isChecked(), info.img[1], ui->editOpImg3CheckBox->isChecked(), info.img[2], ui->editOpImg4CheckBox->isChecked(), info.img[3]);
    } else {
        //선택한 자료가 복수일 경우 (일시의 경우 날짜만 수정)
        for (int i = 0; i < indexes.count(); i++) {
            int id = ui->tableView->model()->data(ui->tableView->model()->index(indexes.at(i).row(), 0)).toInt();
            QString dt = ui->editTimeEdit->date().toString("yyyy-MM-dd") + " " + QDateTime::fromString(DBManage::Instance()->getCrackdownInfo(id).time, "yyyy-MM-dd hh:mm:ss").time().toString("hh:mm:ss");
            DBManage::Instance()->modifyCrackdownInfo(id, ui->editOpNumCheckBox->isChecked(), ui->editNumLineEdit->text(), ui->editOpLocationCheckBox->isChecked(), ui->editLocationLineEdit->text(), ui->editOpTimeCheckBox->isChecked(), dt, ui->editOpDivisionCheckBox->isChecked(), ui->editDivisionComboBox->currentText(), ui->editOpImg1CheckBox->isChecked(), info.img[0], ui->editOpImg2CheckBox->isChecked(), info.img[1], ui->editOpImg3CheckBox->isChecked(), info.img[2], ui->editOpImg4CheckBox->isChecked(), info.img[3]);
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
    }
}


void MainWindow::excelData()
{

}


void MainWindow::savePreference()
{
    UserSettings::Instance()->setImportPath(ui->importPathEdit->text());
    UserSettings::Instance()->setWorkspacePath(ui->workspacePathEdit->text());
    UserSettings::Instance()->setBackUpPath(ui->backUpPathEdit->text());
    UserSettings::Instance()->setExportPath(ui->exportPathEdit->text());
    UserSettings::Instance()->setSearchStartId(ui->searchStartIdSpinBox->value());
    UserSettings::Instance()->setSearchEndId(ui->searchEndIdSpinBox->value());
    UserSettings::Instance()->setSearchNum(ui->searchNumLineEdit->text());
    UserSettings::Instance()->setSearchLocation(ui->searchLocationLineEdit->text());
    UserSettings::Instance()->storeToFile();
}


void MainWindow::aboutAct()
{
    QMessageBox::about(this, tr("About PRIM"), QString("<b>PRIM</b> version: %1 <br> "
                               "<br>Copyright (c) 2013 %3<br>"
                               "<br> Authors:"
                               "<li><a href=\"mailto:%2\">%3</a> (%3) </li>").arg(tr("1306.1")).arg(tr("lbestestl@gmail.com")).arg(tr("lbestestl")));
}


void MainWindow::helpAct()
{
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
        ui->editOpNumCheckBox->setCheckState(Qt::Checked);
        ui->editOpLocationCheckBox->setCheckState(Qt::Checked);
        ui->editOpTimeCheckBox->setCheckState(Qt::Checked);
        ui->editOpDivisionCheckBox->setCheckState(Qt::Checked);
        ui->editOpNumCheckBox->setChecked(true);
        ui->editOpLocationCheckBox->setChecked(true);
        ui->editOpTimeCheckBox->setChecked(true);
        ui->editOpDivisionCheckBox->setChecked(true);
        ui->editOpImg1CheckBox->setHidden(false);
        ui->editOpImg2CheckBox->setHidden(false);
        ui->editOpImg3CheckBox->setHidden(false);
        ui->editOpImg4CheckBox->setHidden(false);
        ui->editTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

        info = DBManage::Instance()->getCrackdownInfo(ui->tableView->model()->data(ui->tableView->model()->index(indexes.at(0).row(), 0)).toInt());
        ui->editNumLineEdit->setText(info.num);
        ui->editLocationLineEdit->setText(info.location);
        ui->editTimeEdit->setDateTime(QDateTime::fromString(info.time, "yyyy-MM-dd hh:mm:ss"));
        for (int i = 0; i < imgLabel.size(); i++)
            imgLabel[i]->setPixmap(QPixmap(info.img[i]));
    } else {
        ui->editOpNumCheckBox->setCheckState(Qt::Unchecked);
        ui->editOpLocationCheckBox->setCheckState(Qt::Unchecked);
        ui->editOpTimeCheckBox->setCheckState(Qt::Unchecked);
        ui->editOpDivisionCheckBox->setCheckState(Qt::Unchecked);
        ui->editOpNumCheckBox->setChecked(false);
        ui->editOpLocationCheckBox->setChecked(false);
        ui->editOpTimeCheckBox->setChecked(false);
        ui->editOpDivisionCheckBox->setChecked(false);
        ui->editOpImg1CheckBox->setCheckState(Qt::Unchecked);
        ui->editOpImg2CheckBox->setCheckState(Qt::Unchecked);
        ui->editOpImg3CheckBox->setCheckState(Qt::Unchecked);
        ui->editOpImg4CheckBox->setCheckState(Qt::Unchecked);
        ui->editOpImg1CheckBox->setHidden(true);
        ui->editOpImg2CheckBox->setHidden(true);
        ui->editOpImg3CheckBox->setHidden(true);
        ui->editOpImg4CheckBox->setHidden(true);

        ui->editTimeEdit->setDisplayFormat("yyyy-MM-dd");
        ui->editNumLineEdit->setText("");
        ui->editLocationLineEdit->setText("");
        for (int i = 0; i < imgLabel.size(); i++)
            imgLabel[i]->setPixmap(QPixmap(""));
    }
}


void MainWindow::tableHorizontalzHeaderClicked(int i)
{
    DBManage::Instance()->searchCrackdownInfo(ui->searchOpIdCheckBox->isChecked(), ui->searchStartIdSpinBox->value(), ui->searchEndIdSpinBox->value(), ui->searchOpNumCheckBox->isChecked(), ui->searchNumLineEdit->text(), ui->searchOpLocationCheckBox->isChecked(), ui->searchLocationLineEdit->text(), ui->searchOpTimeCheckBox->isChecked(), ui->searchStartTimeEdit->text(), ui->searchEndTimeEdit->text(), ui->searchOpDivisionCheckBox->isChecked(), ui->searchDivisionComboBox->currentText(), i, ui->tableView->horizontalHeader()->sortIndicatorOrder());
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 110);
    ui->tableView->setColumnWidth(2, 220);
    ui->tableView->setColumnWidth(3, 160);
    ui->tableView->setColumnWidth(4, 120);
}


void MainWindow::mosaicImage(int i)
{
    setMouseTracking(true);

}


void MainWindow::brightImage(int i)
{
}


void MainWindow::darkImage(int i)
{
}


bool MainWindow::showPopup(const QString str)
{
    Dialog d;
    d.setLabel(str);
    return (d.exec() != 0);
}
