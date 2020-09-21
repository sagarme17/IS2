#include "operador.h"
#include "ui_operador.h"
#include "socio_cliente.h"
#include "cobrar_estacionamiento.h"
operador::operador(QString IdOperador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operador)
{
    ui->setupUi(this);
    this->IdOperador=IdOperador;
}

operador::~operador()
{
    delete ui;
}

void operador::on_CerrarSesion_clicked()
{
    close();
}

void operador::on_RegistrodeVentas_clicked()
{
    Socio_Cliente so_cl(IdOperador);
    so_cl.setWindowTitle("Socio cliente");
    so_cl.exec();
}

void operador::on_Cobrar_clicked()
{
    cobrar_Estacionamiento con(IdOperador,this);
    con.setWindowTitle("Cobrar");
    con.exec();
}
