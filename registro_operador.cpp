#include "registro_operador.h"
#include "ui_registro_operador.h"
#include <QDebug>
#include <QMessageBox>
Registro_operador::Registro_operador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registro_operador)
{
    this->mdb=QSqlDatabase::database("Connection");
    ui->setupUi(this);
}

Registro_operador::~Registro_operador()
{
    delete ui;
}

void Registro_operador::on_CerrarSesion_clicked()
{
    close();
}

void Registro_operador::on_Guardar_clicked()
{
    QString nombre,a_paterno,a_materno,contrasenia,contrasenia2,telefono;
    nombre=ui->Nombre->text();
    a_paterno=ui->ApellidoPat->text();
    a_materno=ui->ApellidoMat->text();
    contrasenia=ui->Contrasea->text();
    contrasenia2=ui->Contrasea_2->text();
    telefono=ui->Telefono->text();
    if(nombre=="" || a_paterno=="" || a_materno=="" || telefono=="" || contrasenia=="" || contrasenia2==""){
        QPalette falta;
        if(nombre==""){
            falta.setColor(ui->Nombre->foregroundRole(),Qt::red);
            ui->Nombre->setPalette(falta);
        }
        if(a_paterno==""){
            falta.setColor(ui->ApellidoPat->foregroundRole(),Qt::red);
            ui->ApellidoPat->setPalette(falta);
        }
        if(a_materno==""){
            falta.setColor(ui->ApellidoMat->foregroundRole(),Qt::red);
            ui->ApellidoMat->setPalette(falta);
        }
        if(contrasenia==""){
            falta.setColor(ui->Contrasea->foregroundRole(),Qt::red);
            ui->Contrasea->setPalette(falta);
        }
        if(contrasenia2==""){
            falta.setColor(ui->Contrasea_2->foregroundRole(),Qt::red);
            ui->Contrasea_2->setPalette(falta);
        }
        if(telefono==""){
            falta.setColor(ui->Telefono->foregroundRole(),Qt::red);
            ui->Telefono->setPalette(falta);
        }

    }
    else if(contrasenia!=contrasenia2){
        QMessageBox::critical(this,"Error","La contraseña no coincide.");
    }
    else{
        if(mdb.open()){
            QSqlQuery correoq(mdb);
            QSqlQuery registro(mdb);
            registro.prepare("call RegistroOper('"+nombre+"','"+a_paterno+"','"+a_materno+"','"
                             +contrasenia+"','"+telefono+"')");
            registro.exec();
            registro.next();
            QSqlQuery idn(mdb);
            idn.prepare("select max(idusuario) from usuario");
            idn.exec();
            idn.next();
            QMessageBox::information(this,"Registro","Registro completado.\nBienvenido a Parking Lite.\nId de Operador: "
                                     +idn.value(0).toString());

            ui->Nombre->clear();
            ui->ApellidoMat->clear();
            ui->ApellidoPat->clear();
            ui->Contrasea->clear();
            ui->Contrasea_2->clear();
            ui->Telefono->clear();

        }
    }
}
