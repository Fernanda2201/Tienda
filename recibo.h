#ifndef RECIBO_H
#define RECIBO_H

#include <QDialog>

namespace Ui {
class recibo;
}

class recibo : public QDialog
{
    Q_OBJECT

public:
    explicit recibo(QWidget *parent = nullptr);
    ~recibo();
    void setRecibo(QString recibo);

private:
    Ui::recibo *ui;
};

#endif // RECIBO_H
