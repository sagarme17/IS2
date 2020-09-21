#include "actualizar_tarifa.h"
#include "ui_actualizar_tarifa.h"
#include <QDebug>
#include <QtSql>
#include <QMessageBox>

Actualizar_Tarifa::Actualizar_Tarifa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actualizar_Tarifa)
{
    this->mdb1=QSqlDatabase::database("Connection");
    ui->setupUi(this);
}

Actualizar_Tarifa::~Actualizar_Tarifa()
{
    delete ui;
}

void Actualizar_Tarifa::on_ComboBox_activated(const QString &arg1)
{
    qDebug()<<arg1;

            //idespecialidad =  ui->comTarifa->itemData(arl).toString();
    //qDebug() << idespecialidad;
}

void Actualizar_Tarifa::on_comTarifa_currentTextChanged(const QString &arg1)
{
    QSqlQuery getTarifa(mdb1);
    if(arg1 == "Tarifa mensual:"){
        getTarifa.prepare("select TarifaMensual from tarifas where idTarifas=1");
        getTarifa.exec();
        getTarifa.next();
        ui->ActualTarifa->setText("Tarifa actual:    $"+getTarifa.value(0).toString());

    }
    else if(arg1 == "Tarifa por hora:"){
        getTarifa.prepare("select TarifaHora from tarifas where idTarifas=1");
        getTarifa.exec();
        getTarifa.next();
        ui->ActualTarifa->setText("Tarifa actual:    $"+getTarifa.value(0).toString());
    }
    else{
        ui->ActualTarifa->setText("Tarifa actual:");
    }





}

void Actualizar_Tarifa::on_Guardar_clicked()
{
    QString tarifa;
    tarifa = ui->comTarifa->currentText();
    double ntarifa=ui->NuevaTarifa->value();
    QSqlQuery nuevatarifa(mdb1);
    if(tarifa == "Tarifa mensual:"){
        nuevatarifa.prepare("UPDATE tarifas SET TarifaMensual='"+QString::number(ntarifa)+"'");
        nuevatarifa.exec();
        nuevatarifa.next();
        QMessageBox::information(this,"Cambios guardados","Tarifa Mensual Actualizada.");
        ui->comTarifa->setCurrentIndex(0);
        ui->ActualTarifa->setText("Tarifa Actual:");
        ui->NuevaTarifa->setValue(0);
    }
    else if(tarifa == "Tarifa por hora:"){
        nuevatarifa.prepare("UPDATE tarifas SET TarifaHora='"+QString::number(ntarifa)+"'");
        nuevatarifa.exec();
        nuevatarifa.next();
        QMessageBox::information(this,"Cambios guardados","Tarifa por Hora Actualizada.");
        ui->comTarifa->setCurrentIndex(0);
        ui->ActualTarifa->setText("Tarifa Actual:");
        ui->NuevaTarifa->setValue(0);
    }
    else {
        QMessageBox::warning(this,"Tarifa Invalida","Seleccione una tarifa.");
    }

}

void Actualizar_Tarifa::on_Cancelar_clicked()
{
    close();
}
