/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#include "Login.h"
#include "ui_Login.h"

#include "MainWindow.h"
#include "Security.h"
#include "UserSettings.h"

#include <QLineEdit>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QRegExp rx("[A-Za-z0-9_]{0,31}");
    validator = new QRegExpValidator(rx, this);
    initWidgets();
    connectWidgets();
}


Login::~Login()
{
    delete validator;
    delete ui;
}


void Login::initWidgets()
{
    isLoginState = true;
    ui->idLineEdit->clear();
    ui->idLineEdit->setEchoMode(QLineEdit::Normal);
    ui->pwLineEdit->clear();
    ui->pwLineEdit->setEchoMode(QLineEdit::Password);
    ui->reLineEdit->clear();
    ui->reLineEdit->setEchoMode(QLineEdit::Password);
    ui->reLabel->setEnabled(false);
    ui->reLabel->setHidden(true);
    ui->reLineEdit->setEnabled(false);
    ui->reLineEdit->setHidden(true);
    ui->registerButton->setEnabled(true);
    ui->registerButton->setHidden(false);
    ui->idLabel->setGeometry(QRect(20, 30, 90, 25));
    ui->idLineEdit->setGeometry(QRect(120, 30, 140, 25));
    ui->pwLabel->setGeometry(QRect(20, 80, 90, 25));
    ui->pwLineEdit->setGeometry(QRect(120, 80, 140, 25));
    ui->idLineEdit->setValidator(validator);
    ui->pwLineEdit->setValidator(validator);
    ui->reLineEdit->setValidator(validator);
}

void Login::connectWidgets()
{
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(registerButtonClicked()));
    connect(ui->pwLineEdit, SIGNAL(textEdited(QString)), this, SLOT(passwordLengthCheck(QString)));
}


void Login::passwordLengthCheck(QString pw)
{
    if (pw.length() < 8)
        ui->loginButton->setEnabled(false);
    else
        ui->loginButton->setEnabled(true);
}


void Login::loginButtonClicked()
{
    if (isLoginState) {
        //id, pw 저장
    }
    //id, pw 불러옴
//    UserSettings::Instance()->setId(prim_security::cipher(prim_security::SHA256, ui->idLineEdit->text()));
//    UserSettings::Instance()->setPassword(prim_security::cipher(prim_security::SHA256, ui->pwLineEdit->text()));
//    UserSettings::Instance()->storeToFile();
    QString id = UserSettings::Instance()->getId();
    QString pw = UserSettings::Instance()->getPassword();
    if ((prim_security::cipher(prim_security::SHA256, ui->idLineEdit->text()) == id) && (prim_security::cipher(prim_security::SHA256, ui->pwLineEdit->text()) == pw)) {
        emit accept();
    }
}


void Login::cancelButtonClicked()
{
    if (isLoginState)
        emit reject();
    else
        initWidgets();
}


void Login::registerButtonClicked()
{
    ui->idLineEdit->clear();
    ui->pwLineEdit->clear();
    ui->reLineEdit->clear();
    ui->reLabel->setEnabled(true);
    ui->reLabel->setHidden(false);
    ui->reLineEdit->setEnabled(true);
    ui->reLineEdit->setHidden(false);
    ui->registerButton->setEnabled(false);
    ui->registerButton->setHidden(true);
    ui->idLabel->setGeometry(QRect(20, 20, 90, 25));
    ui->idLineEdit->setGeometry(QRect(120, 20, 140, 25));
    ui->pwLabel->setGeometry(QRect(20, 60, 90, 25));
    ui->pwLineEdit->setGeometry(QRect(120, 60, 140, 25));
    isLoginState = false;
}
