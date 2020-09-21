#include "socio.h"
#include "ui_socio.h"
#include "tramitar_membresia.h"
#include <QMessageBox>
socio::socio(QString IdSocio,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::socio)
{
    ui->setupUi(this);
    this->IdSocio=IdSocio;
    this->mdb=QSqlDatabase::database("Connection");
}

socio::~socio()
{
    delete ui;
}

void socio::on_CerrarSesion_clicked()
{
    close();
}

void socio::on_ReservaMnesual_clicked()
{
    if(mdb.open()){
        QSqlQuery membresia(mdb);
        QDateTime actual;
        actual=QDateTime::currentDateTime();
        membresia.prepare("select FechaFinal from membresia where idSocio='"+IdSocio+"' and FechaFinal >='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"'");
        membresia.exec();
        if(membresia.next()){
            QMessageBox::warning(this,"Reservación Mensual","Usted ya cuenta con una reservación mensual que finaliza el "+membresia.value(0).toDate().toString("dd-MM-yyyy"));
        }
        else{
            tramitar_Membresia men(IdSocio,this);
            men.setWindowTitle("Reservación Mensual");
            men.exec();
        }
    }
}
