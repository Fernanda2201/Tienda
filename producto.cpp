#include "producto.h"

Producto::Producto(QObject *parent) : QObject(parent)
{
    m_codigo = 0;
    m_nombre = "";
    m_precio =0.0;
}

Producto::Producto(int codigo, QString nombre, float precio)
{
 m_codigo = codigo;
 m_nombre = nombre;
 m_precio = precio;
}

int Producto::codigo() const{
    return m_codigo;
}

float Producto::precio() const
{
    return m_precio;
}

QString Producto::nombre() const
{
    return m_nombre;
}

void Producto::setPrecio(float precio){
    m_precio = precio;
}
