#include "recibo.h"
#include "ui_recibo.h"

recibo::recibo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recibo)
{
    ui->setupUi(this);
}

recibo::~recibo()
{
    delete ui;
}

void recibo::setRecibo(QString recibo)
{
    ui->outRecibo->appendPlainText(recibo);
}
