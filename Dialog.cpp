#include "Dialog.h"
#include "ui_Dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setLabel(const QString str)
{
    ui->label->setText(str);
}
