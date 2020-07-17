#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QObject>

class Producto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int codigo READ codigo )
    Q_PROPERTY(float precio READ precio WRITE setPrecio)
    Q_PROPERTY(QString nombre READ nombre )


public:
    explicit Producto(QObject *parent = nullptr);
   Producto(int codigo, QString nombre, float precio);

   //Gters
   int codigo() const;
   float precio()const;
   QString nombre()const;

   //Setters
   void setPrecio(float precio);


signals:

private:
   int m_codigo;
   float m_precio;
   QString m_nombre;

};

#endif // PRODUCTO_H
