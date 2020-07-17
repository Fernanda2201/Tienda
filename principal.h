#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "producto.h"
#include "recibo.h"
#include "acerca_de.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

public slots:
    void mostrarPrecio(int);
    void agregarProducto();
    void validarCedula();
    void validarValores();
    void reciboCompra();

private slots:
    void on_actionAcerca_de_triggered();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;

    void inicializarDatos();
    void inicializarWidgets();
    float m_subtotal;

    void calcular(float);
    bool buscar(Producto *producto, int cantidad);

};
#endif // PRINCIPAL_H
