#include "registro_cliente.h"
#include "ui_registro_cliente.h"
#include <QDebug>
#include <QMessageBox>
Registro_cliente::Registro_cliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registro_cliente)
{
    this->mdb=QSqlDatabase::database("Connection");
    ui->setupUi(this);
}

Registro_cliente::~Registro_cliente()
{
    delete ui;
}

void Registro_cliente::on_CerrarSesion_clicked()
{
    close();
}

void Registro_cliente::on_Guardar_clicked()
{
    QString nombre,a_paterno,a_materno,contrasenia,contrasenia2,correo,telefono,numtarjeta,titulartarjeta,matricula;
    nombre=ui->Nombre->text();
    a_paterno=ui->ApellidoPat->text();
    a_materno=ui->ApellidoMat->text();
    correo=ui->Correo->text();
    contrasenia=ui->Contrasea->text();
    contrasenia2=ui->Contrasea_2->text();
    telefono=ui->Telefono->text();
    numtarjeta=ui->NumeroTarjeta->text();
    titulartarjeta=ui->Titular->text();
    matricula=ui->Matricula->text();
    if(nombre=="" || a_paterno=="" || a_materno=="" || correo=="" || telefono=="" || contrasenia==""
       || contrasenia2=="" || numtarjeta=="" || titulartarjeta==""){
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
        if(correo==""){
            falta.setColor(ui->Correo->foregroundRole(),Qt::red);
            ui->Correo->setPalette(falta);
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
        if(numtarjeta==""){
            falta.setColor(ui->NumeroTarjeta->foregroundRole(),Qt::red);
            ui->NumeroTarjeta->setPalette(falta);
        }
        if(titulartarjeta==""){
            falta.setColor(ui->Titular->foregroundRole(),Qt::red);
            ui->Titular->setPalette(falta);
        }
    }
    else if(contrasenia!=contrasenia2){
        QMessageBox::critical(this,"Error","La contraseña no coincide.");
    }
    else{
        if(matricula!=""){
            if(mdb.open()){
                QSqlQuery correoq(mdb);
                correoq.prepare("select Correo from Socio where Correo = '"+correo+"'");
                correoq.exec();
                if(correoq.next()){
                    QMessageBox::critical(this,"Error","Correo registrado con otra cuenta");
                }
                else{
                    QSqlQuery registro(mdb);
                    registro.prepare("call RegistroSocio('"+nombre+"','"+a_paterno+"','"+a_materno+"','"
                                     +contrasenia+"','"+telefono+"','"+correo+"','"+numtarjeta+"','"+titulartarjeta+"')");
                    registro.exec();
                    registro.next();
                    QSqlQuery idn(mdb);
                    idn.prepare("select max(idusuario) from usuario");
                    idn.exec();
                    idn.next();
                    QSqlQuery matriculaid(mdb);
                    matriculaid.prepare("Insert Into matricula_registrada (IdSocio,Matricual) value('"+idn.value(0).toString()+
                                        "','"+matricula+"'");
                    QMessageBox::information(this,"Registro","Registro completado.\nBienvenido a Parking Lite.\nId de Socio: "
                                                 +idn.value(0).toString());
                    close();
                }
            }
        }
        else{
            if(mdb.open()){
                QSqlQuery correoq(mdb);
                correoq.prepare("select Correo from Socio where Correo = '"+correo+"'");
                correoq.exec();
                if(correoq.next()){
                    QMessageBox::critical(this,"Error","Correo registrado con otra cuenta");
                }
                else{
                    QSqlQuery registro(mdb);
                    registro.prepare("call RegistroSocio('"+nombre+"','"+a_paterno+"','"+a_materno+"','"
                                     +contrasenia+"','"+telefono+"','"+correo+"','"+numtarjeta+"','"+titulartarjeta+"')");
                    registro.exec();
                    registro.next();
                    QSqlQuery idn(mdb);
                    idn.prepare("select max(idusuario) from usuario");
                    idn.exec();
                    idn.next();
                    QMessageBox::information(this,"Registro","Registro completado.\nBienvenido a Parking Lite.\nId de Socio: "
                                                 +idn.value(0).toString());
                    close();
                }
            }



        }
    }
}
