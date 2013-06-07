/**************************************************************************
** Qt Creator license header template
**   Special keywords: owner 2013. 6. 7. 2013
**   Environment variables: 
**   To protect a percent sign, use '%'.
**************************************************************************/


#include "Login.h"
#include "ui_Login.h"

#include "MainWindow.h"
#include <QDebug>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connectWidgets();
}


Login::~Login()
{
    delete ui;
}


void Login::connectWidgets()
{
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(modifyButtonClicked()));
}


void Login::loginButtonClicked()
{
    QString id = "cctv";
    QString pw = "12345678";
    if ((ui->idLineEdit->text() == id) && (ui->pwLineEdit->text() == pw)) {
        qDebug() <<"OK";
        this->close();
    }
}


void Login::cancelButtonClicked()
{
    qDebug() << "exit";
    exit(0);
}


void Login::modifyButtonClicked()
{
}


bool Login::isCorrectPw()
{
//    QString id = "cctv";
//    QString pw = "12345678";
//    while (!(ui->idLineEdit->text() == id) && (ui->pwLineEdit->text() == pw))
    return true;
}