#include "inicio_de_sesion.h"
#include "ui_inicio_de_sesion.h"
#include "admin.h"
#include "operador.h"
#include "socio.h"
#include "registro_cliente.h"
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

Inicio_De_Sesion::Inicio_De_Sesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inicio_De_Sesion)
{
    this->mdb=QSqlDatabase::database("Connection");
    ui->setupUi(this);
}

Inicio_De_Sesion::~Inicio_De_Sesion()
{
    delete ui;
}

void Inicio_De_Sesion::on_Inicio_sesion_clicked()
{
    QString id,contrasenia,aux;
    id=ui->Usuario->text();
    contrasenia=ui->Contrasena->text();
    if(id==""||contrasenia==""){
        QPalette falta;
        if(id==""){
            falta.setColor(ui->Usuario->foregroundRole(),Qt::red);
            ui->Usuario->setPalette(falta);
        }
        if(contrasenia==""){
            falta.setColor(ui->Contrasena->foregroundRole(),Qt::red);
            ui->Contrasena->setPalette(falta);
        }
    }
    else{
        if(mdb.open()){
            qDebug() << "Conexión exitosa";
            QSqlQuery query1(mdb),query2(mdb),query3(mdb);
            query1.prepare("select IdAdministrador from Administrador where IdAdministrador='"+id+"'");
            query1.exec();
            query2.prepare("select IdOperador from Operador where IdOperador='"+id+"'");
            query2.exec();
            query3.prepare("select IdSocio from Socio where IdSocio='"+id+"'");
            query3.exec();
            if(query1.next()){
               query1.clear();
               query1.prepare("select Contraseña from Usuario inner join Administrador on IdAdministrador=IdUsuario where IdUsuario='"+id+"'");
               query1.exec();
               query1.next();
               if(contrasenia==query1.value(0).toString()){
                   admin admi(id);
                   admi.setWindowTitle("Administrador");
                   admi.setModal(false);
                   this->setVisible(false);
                   admi.exec();
                   this->setVisible(true);
                   ui->Usuario->clear();
                   ui->Contrasena->clear();
               }
               else{
                   QMessageBox::critical(this,"Error","Contraseña incorrecta");
                   ui->Contrasena->clear();
               }
            }
            else if (query2.next()) {
                query2.clear();
                query2.prepare("select Contraseña from Usuario inner join Operador on IdOperador=IdUsuario where IdUsuario='"+id+"'");
                query2.exec();
                query2.next();
                if(contrasenia==query2.value(0).toString()){
                    operador operador(id);
                    operador.setWindowTitle("Operador");
                    operador.setModal(false);
                    this->setVisible(false);
                    operador.exec();
                    this->setVisible(true);
                    ui->Usuario->clear();
                    ui->Contrasena->clear();
                }
                else{
                    QMessageBox::critical(this,"Error","Contraseña incorrecta");
                    ui->Contrasena->clear();
                }
            }
            else if (query3.next()) {
                query3.clear();
                query3.prepare("select Contraseña from Usuario inner join Socio on IdSocio=IdUsuario where IdUsuario='"+id+"'");
                query3.exec();
                query3.next();
                if(contrasenia==query3.value(0).toString()){
                    socio socio(id);
                    socio.setWindowTitle("Socio");
                    socio.setModal(false);
                    this->setVisible(false);
                    socio.exec();
                    this->setVisible(true);
                    ui->Usuario->clear();
                    ui->Contrasena->clear();
                }
                else{
                    QMessageBox::critical(this,"Error","Contraseña incorrecta");
                    ui->Contrasena->clear();
                }
            }
            else{
               QMessageBox::critical(this,"Error","Id de usuario invalido");
            }


        }
        else
            qDebug()<< "Estan muy weyes";
    }

}
void Inicio_De_Sesion::on_Registrarse_clicked()
{
    Registro_cliente registro;
    registro.setWindowTitle("Registrarse");
    registro.exec();
}
