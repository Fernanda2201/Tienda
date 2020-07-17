#include "principal.h"
#include "ui_principal.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    inicializarDatos();
    m_subtotal=0;
}


Principal::~Principal()
{
    delete ui;
}

void Principal::mostrarPrecio(int index)
{
    float precio = m_productos.at(index)->precio();
    ui->outPrecio->setText("$" + QString::number(precio));
}

void Principal::agregarProducto()
{
    //Obteniendo datos desde la interfaz
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);
    int cantidad = ui->inCantidad->value();

    if(cantidad==0)
        return;

    //Calculando el subtotal
    float subtotal = cantidad * p->precio();
    //  Buscar y actulizar productos repetidos
    if (!buscar(p, cantidad)){
        //Agregar datos a la tabla
        int posicion = ui->outDetalle->rowCount();
        ui->outDetalle->insertRow(posicion);
        ui->outDetalle->setItem(posicion,0, new QTableWidgetItem(QString::number(cantidad)));
        ui->outDetalle->setItem(posicion,1, new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(posicion,2, new QTableWidgetItem(QString::number(subtotal)));
    }
    //Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();



    // Calcular valores y mostrar
    calcular(subtotal);
}

void Principal::validarCedula()
{
    int   pares,impares,total,dec=0;
    int a,b,c,d,e,f,g,h,i,j;
    long cedula;
    cedula=ui->inCedula->text().toLong();



    a=cedula/1000000000;
    cedula=cedula-(a*1000000000);
    b=cedula/100000000;
    cedula=cedula-(b*100000000);
    c=cedula/10000000;
    cedula=cedula-(c*10000000);
    d=cedula/1000000;
    cedula=cedula-(d*1000000);
    e=cedula/100000;
    cedula=cedula-(e*100000);
    f=cedula/10000;
    cedula=cedula-(f*10000);
    g=cedula/1000;
    cedula=cedula-(g*1000);
    h=cedula/100;
    cedula=cedula-(h*100);
    i=cedula/10;
    cedula=cedula-(i*10);
    j=cedula/1;
    cedula=cedula-(j*1);

    if (cedula>2400000000){
        ui->inCedula->setStyleSheet("color : red");

    }else{

        pares=b+d+f+h;

        a=a*2;
        if (a>9){
            a=a%10+a/10;
        }

        c=c*2;
        if (c>9){
            c=c%10+c/10;
        }

        e=e*2;
        if (e>9){
            e=e%10+e/10;
        }

        g=g*2;
        if (g>9){
            g=g%10+g/10;
        }

        i=i*2;
        if (i>9){
            i=i%10+i/10;
        }

        impares=a+c+e+g+i;

        total=pares+impares;



        while (dec-total!=j && dec<total+10){
            dec=dec+10;
        }

        if (dec-total==j){
            ui->inCedula->setStyleSheet("color: green");
        }else {
            ui->inCedula->setStyleSheet("color: red");
            ui->statusbar->showMessage("Numero de cedula invalido",5000);
        }
    }


}

void Principal::validarValores()
{
    QString nombre=ui->intNombre->text();
    QString telefono=ui->intTelefono->text();
    QString correo=ui->intEmail->text();
    QString cedula=ui->inCedula->text();
    if(nombre==""){
        ui->intNombre->setStyleSheet("background-color: red");

    }else{
        ui->intNombre->setStyleSheet("background-color: green");
    }
    if(telefono==""){
        ui->intTelefono->setStyleSheet("background-color: red");
    }else{
        ui->intTelefono->setStyleSheet("background-color: green");
    }
    if(correo==""){
        ui->intEmail->setStyleSheet("background-color: red");
    }else{
        ui->intEmail->setStyleSheet("background-color: green");
    }
    if(cedula==""){
        ui->inCedula->setStyleSheet("background-color: red");
    }else{
        ui->inCedula->setStyleSheet("background-color: green");

    }
    if(nombre=="" || telefono=="" || correo=="" || cedula==""){
        QMessageBox vacio;
        vacio.setText("No se han ingresado ciertos datos porfavor verifique");
        vacio.exec();
    }
}

void Principal::reciboCompra()
{
    //Obtener datos
    QString nombre=ui->intNombre->text();
    QString telefono=ui->intTelefono->text();
    QString correo=ui->intEmail->text();
    QString cedula=ui->inCedula->text();
    QString direccion=ui->IntDireccion->toPlainText();
    QString subTotalCompra=ui->outSubtotal->text();
    QString iva= ui->outIva->text();
    QString totalCompra=ui->outTotal->text();





    if(nombre=="" || telefono=="" || correo=="" || cedula==""){
        return;
    }else {
        //Modelo de recibo
        recibo *dlgRecibo= new recibo;
        QString resultado= "Nombre: " + nombre + "\n";
        resultado += "Cedula: " + cedula + "\n";
        resultado += "Telefono: " + telefono + "\n";
        resultado += "Correo: " + correo + "\n";
        resultado += "Direccion: "+ direccion +"\n";
        resultado += "Subtotal: $"+ subTotalCompra +"\n";
        resultado += "Iva: "+ iva +"\n";
        resultado += "Total a pagar: $"+ totalCompra +"\n";


        //Plantear Recibo en una ventana
        dlgRecibo->setRecibo(resultado);
        dlgRecibo->show();
}
}


void Principal::inicializarDatos()
{
    //Abrir archivo de productos
    QFile archivo("productos.csv");

    if(archivo.open(QFile::ReadOnly)){
        QTextStream in(&archivo);
        while(!in.atEnd()){
            QString linea = in.readLine();
            //Separar Datos por ';'
            QStringList datos =linea.split(';');
            int codigo = datos[0].toInt();
            float precios= datos[2].toFloat();
            //Crear y agregar productos a la lista
            m_productos.append(new Producto(codigo,datos[1],precios));
        }
    }else{
        qDebug()<< "Error al abrir al archivo";
    }
    archivo.close();

    //Invocar al metodo para inicializar los widgets

    inicializarWidgets();
}

void Principal::inicializarWidgets()
{
    //Agregar nombre de los productos al combo box
    for(int i=0; i<m_productos.length(); ++i){
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }

    //Colocar cabecera en la tabla
    QStringList cabecera = {"Cantidad" , "Producto" , "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);


    //  Eventos
    connect(ui->inProducto, SIGNAL(currentIndexChanged(int)),
            this, SLOT(mostrarPrecio(int)));
    connect(ui->cmdAgregar, SIGNAL(clicked(bool)),
            this, SLOT(agregarProducto()));
    connect(ui->inCedula, SIGNAL(editingFinished()), this, SLOT(validarCedula()));

    connect(ui->cmdFinalizar, SIGNAL(clicked(bool)),this, SLOT(validarValores()));
    connect(ui->cmdFinalizar, SIGNAL(clicked(bool)),this, SLOT(reciboCompra()));

    //Mostrar el precio del primer producto
    mostrarPrecio(0);
}

void Principal::calcular(float subtotal)
{
    m_subtotal +=subtotal;
    float iva =m_subtotal*0.12;
    float total =m_subtotal + iva;
    ui->outSubtotal->setText(QString::number(m_subtotal));
    ui->outIva->setText(QString::number(iva));
    ui->outTotal->setText(QString::number(total));
}

bool Principal::buscar(Producto *producto, int cantidad)
{
    // Recorrer la tabla
    int numFilas= ui->outDetalle->rowCount();
    for (int i=0;i<numFilas;++i) {
        //Otener el item en la fila y columna 1 (Nombre del producto)
        QTableWidgetItem *item=ui->outDetalle->item(i,1);
        //Obtener el texto
        QString dato= item->data(Qt::DisplayRole).toString();

        //Comparar
        if(dato == producto->nombre()){
            //Obtener la cantidad del producto que ya esta el detalle
            QTableWidgetItem *item=ui->outDetalle->item(i,0);
            int cantidadActual = item->data(Qt::DisplayRole).toInt();
            // sumar la cantidad
            int cantidadNueva= cantidadActual + cantidad;
            //calcular nuevo subtotal
            float subtotal = cantidadNueva *producto->precio();
            qDebug() << cantidadNueva<<subtotal;
            //Actulizar en la tabla
            ui->outDetalle->setItem(i,0, new QTableWidgetItem(QString::number(cantidadNueva)));
            ui->outDetalle->setItem(i,2, new QTableWidgetItem(QString::number(subtotal)));
            return true;

        }
    }
    return false;
}

void Principal::on_actionAcerca_de_triggered()
{
    Acerca_de ayuda;
    ayuda.setModal(true);
    ayuda.exec();

}
