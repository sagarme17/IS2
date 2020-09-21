#include "ventas_diarias.h"
#include "ui_ventas_diarias.h"
#include <QDebug>
#include <QtSql>
Ventas_Diarias::Ventas_Diarias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ventas_Diarias)
{
    this->mdb1=QSqlDatabase::database("Connection");
    ui->setupUi(this);

}

Ventas_Diarias::~Ventas_Diarias()
{
    delete ui;
}

void Ventas_Diarias::on_Calendario_clicked(const QDate &date)
{
    if(mdb1.open()){
        ui->Tabla_ventas->setRowCount(0);
        QSqlQuery queryv(mdb1),queryb(mdb1);
        QString fecha;
        int anio, mes,dia;
        mes=date.month();
        anio=date.year();
        dia=date.day();
        fecha=QString::number(anio)+"-"+QString::number(mes)+"-"+QString::number(dia);
        queryv.prepare("SELECT FechaInicio,FechaFinal FROM VENTA where FechaInicio between '"+fecha+" 00:00:00' and '"+fecha+" 23:59:59'");
        queryv.exec();
        queryb.prepare("select tarifahora from tarifas where idtarifas=1");
        queryb.exec();
        queryb.next();
        double tarifa=queryb.value(0).toDouble();

        QTime inicio,final;
        while(queryv.next()){
            inicio=queryv.value(0).toTime();
            final=queryv.value(1).toTime();
            QTableWidgetItem *uno=new QTableWidgetItem(fecha);
            QTableWidgetItem *dos=new QTableWidgetItem(inicio.toString());
            QTableWidgetItem *tres=new QTableWidgetItem(final.toString());
            QTableWidgetItem *cuatro=new QTableWidgetItem("$"+QString::number(((final.hour()-inicio.hour())*tarifa)));
            ui->Tabla_ventas->setRowCount(ui->Tabla_ventas->rowCount()+1);
            ui->Tabla_ventas->setItem(ui->Tabla_ventas->rowCount()-1,0,uno);
            ui->Tabla_ventas->setItem(ui->Tabla_ventas->rowCount()-1,1,dos);
            ui->Tabla_ventas->setItem(ui->Tabla_ventas->rowCount()-1,2,tres);
            ui->Tabla_ventas->setItem(ui->Tabla_ventas->rowCount()-1,3,cuatro);
        }
    }
}

void Ventas_Diarias::on_pushButton_clicked()
{
    close();
}
