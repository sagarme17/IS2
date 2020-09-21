#include "socio_cliente.h"
#include "ui_socio_cliente.h"
#include "accesos_socio.h"
#include "acceso_cliente.h"
#include <QMessageBox>
#include <QDateTime>
Socio_Cliente::Socio_Cliente(QString IdOperador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Socio_Cliente)
{
    this->mdb=QSqlDatabase::database("Connection");
    this->IdOperador=IdOperador;
    ui->setupUi(this);
}

Socio_Cliente::~Socio_Cliente()
{
    delete ui;
}


void Socio_Cliente::on_BtnRegresar_clicked()
{
    close();
}

void Socio_Cliente::on_Socio_sin_reservacion_clicked()
{
    if(mdb.open()){
        QSqlQuery espacio(mdb);
        espacio.prepare("Select * from Estacionamiento_Socio where Estatus='Libre'");
        espacio.exec();
        if(espacio.next()){
            Acceso_cliente_socio a(IdOperador,this);
            a.setWindowTitle("Socio sin reservación");
            a.exec();
        }
        else{
            QMessageBox::warning(this,"Estacionamiento Lleno","Estacionamiento a su máxima capacidad.");
        }
    }

}

void Socio_Cliente::on_Socio_con_reservacion_clicked()
{
    if(mdb.open()){
        QDateTime actual;
        actual=QDateTime::currentDateTime();
        QSqlQuery espacio(mdb);
        espacio.prepare("select * from reservación inner join estacionamiento_socio on reservación.idestacionamiento_socio=estacionamiento_socio.idestacionamiento_socio where Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Estatus='Reservado'");
        espacio.exec();
        if(espacio.next()){
            accesos_socio a(IdOperador,this);
            a.setWindowTitle("Socio con reservación");
            a.exec();
        }
        else{
            QMessageBox::critical(this,"Error","Sin reservaciones registradas.");
        }
    }
}
