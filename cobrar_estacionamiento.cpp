#include "cobrar_estacionamiento.h"
#include "ui_cobrar_estacionamiento.h"
#include <QMessageBox>
cobrar_Estacionamiento::cobrar_Estacionamiento(QString IdOperador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cobrar_Estacionamiento)
{
    ui->setupUi(this);
    this->IdOperador=IdOperador;
    this->mdb=QSqlDatabase::database("Connection");
}

cobrar_Estacionamiento::~cobrar_Estacionamiento()
{
    delete ui;
}

void cobrar_Estacionamiento::on_BtnRegresar_clicked()
{
    close();

}

void cobrar_Estacionamiento::on_BtnCobrar_clicked()
{
    if(mdb.open()){
        QSqlQuery venta(mdb);
        QString idventa,lugar;
        QDateTime actual,inicio;
        actual=QDateTime::currentDateTime();
        venta.prepare("select * from venta where matricula='"+ui->LineMatricula->text()+"' and FechaInicio between '"+actual.toString("yyyy-MM-dd")+" 00:00:00' and '"+actual.toString("yyyy-MM-dd")+" 23:59:59'");
        venta.exec();
        if(venta.next()){
            idventa=venta.value(0).toString();
            lugar=venta.value(6).toString();
            inicio=venta.value(1).toDateTime();
            venta.clear();
            venta.prepare("update venta set FechaFinal ='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' where IdVenta='"+idventa+"'");
            venta.exec();
            venta.next();
            venta.clear();
            venta.prepare("update estacionamiento_cliente set estatus='Libre' where idEstacionamiento_Cliente='"+lugar+"'");
            venta.clear();
            venta.prepare("select tarifaHora from tarifas where idtarifas=1");
            venta.exec();
            venta.next();
            double total=(inicio.time().hour()-actual.time().hour())*venta.value(0).toDouble();

            QMessageBox::information(this,"Cobrar","Hora de entrada: "+inicio.toString("hh:mm")+"\nHora de salida: "+actual.toString("hh:mm")+"\n Total a cobrar: $"+QString::number(total));
            ui->LineMatricula->clear();
        }
        else{
            QMessageBox::critical(this,"Error","Matricula invalida.");
            ui->LineMatricula->clear();
        }
    }
}
