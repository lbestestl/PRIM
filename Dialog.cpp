#include "Dialog.h"
#include "ui_Dialog.h"

#include <QPushButton>
#include <QDebug>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("확인");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("취소");
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setLabel(const QString str)
{
    ui->label->setText(str);
}
