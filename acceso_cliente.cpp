#include "acceso_cliente.h"
#include "ui_acceso_cliente.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
//Acceso Socio Sin Reservación
Acceso_cliente_socio::Acceso_cliente_socio(QString IdOperador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acceso_cliente_socio)
{
    this->IdOperador=IdOperador;
    this->mdb=QSqlDatabase::database("Connection");
    ui->setupUi(this);
    ui->Matricula->setVisible(false);
    ui->MatriculaDif->setVisible(false);
    ui->Matricula_2->setVisible(false);
}

Acceso_cliente_socio::~Acceso_cliente_socio()
{
    delete ui;
}

void Acceso_cliente_socio::on_BtnRegresar_clicked()
{
    close();
}


void Acceso_cliente_socio::on_BuscarSocio_clicked()
{
    if(mdb.open()){
        qDebug()<<"Entro";
        QString id;
        id=ui->IdSocio->text();
        QSqlQuery idbuscar(mdb);
        idbuscar.prepare("select IdSocio from Socio where IdSocio = '"+id+"'");
        idbuscar.exec();
        if(idbuscar.next()){
            QSqlQuery matricula(mdb);
            matricula.prepare("select Matricula from matricula_registrada where IdSocio='"+id+"'");
            matricula.exec();
            if(matricula.next()){
                ui->Matricula_2->setVisible(true);
                ui->MatriculaDif->setVisible(true);
                ui->Matricula_2->setText("Matricula: "+matricula.value(0).toString());
            }
            else{
                ui->Matricula->setVisible(true);
            }
        }
        else{
            QMessageBox::critical(this,"Error","Id de Socio ivalido.");
        }
    }
}



void Acceso_cliente_socio::on_MatriculaDif_clicked()
{
    if(ui->MatriculaDif->isChecked()){
        ui->Matricula->setVisible(true);
    }
    else{
        ui->Matricula->setVisible(false);
    }
}

void Acceso_cliente_socio::on_Guardar_2_clicked()
{
    if(mdb.open()){
        QString id,matricula,lugare;
        id=ui->IdSocio->text();
        QSqlQuery idbuscar(mdb);
        idbuscar.prepare("select IdSocio from Socio where IdSocio = '"+id+"'");
        idbuscar.exec();
        bool Idexists=idbuscar.next();
        QSqlQuery matriculab(mdb);
        matriculab.prepare("Select Matricula from matricula_registrada where IdSocio='"+id+"'");
        matriculab.exec();
        if(Idexists and matriculab.next()){
            if(ui->MatriculaDif->isChecked() ){
                matricula=ui->Matricula->text();
                if(matricula!=""){
                    QSqlQuery matriculac(mdb);
                    matriculac.prepare("Select Matricula from matricula_registrada where Matricula='"+matricula+"' and IdSocio='"+id+"'");
                    matriculac.exec();
                    if(matriculac.next()){
                        QMessageBox::critical(this,"Error","Matricula ya registrada.");
                    }
                    else{
                        QSqlQuery lugar(mdb);
                        lugar.prepare("select * from Estacionamiento_Socio where Estatus='Libre'");
                        lugar.exec();
                        lugar.next();
                        lugare=lugar.value(0).toString();
                        lugar.clear();
                        lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
                        lugar.exec();
                        lugar.next();
                        lugar.clear();
                        QDateTime actual;
                        actual=QDateTime::currentDateTime();
                        lugar.prepare("call Venta('"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+matricula+"','"+IdOperador+"','"+lugare+"')");
                        lugar.exec();
                        lugar.next();
                        lugar.clear();
                        lugar.prepare("select matricula from vehiculo where matricula='"+matricula+"'");
                        lugar.exec();
                        if(lugar.next()){
                            lugar.clear();
                            lugar.prepare("Insert Into Ingreso_Temporal(IdSocio,Matricula) values('"+id+"','"+matricula+"')");
                            lugar.exec();
                            lugar.next();
                        }
                        else{
                            lugar.clear();
                            lugar.prepare("Insert Into Vehiculo(Matricula) values('"+matricula+"')");
                            lugar.exec();
                            lugar.next();
                            lugar.clear();
                            lugar.prepare("Insert Into Ingreso_Temporal(IdSocio,Matricula) values('"+id+"','"+matricula+"')");
                            lugar.exec();
                            lugar.next();
                        }
                        ui->IdSocio->clear();
                        ui->Matricula->clear();
                        ui->MatriculaDif->click();
                        ui->Matricula_2->clear();
                        ui->Matricula->setVisible(false);
                        ui->MatriculaDif->setVisible(false);
                        ui->Matricula_2->setVisible(false);
                        QMessageBox::information(this,"Acceso Autorizado","Acceso Autorizado.\nIngresar al cajón "+lugare);
                    }
                }
                else{
                    QMessageBox::critical(this,"Error","Debes introducir una matricula.");
                }
            }
            else{
                QSqlQuery lugar(mdb);
                lugar.prepare("select * from Estacionamiento_Socio where Estatus='Libre'");
                lugar.exec();
                lugar.next();
                lugare=lugar.value(0).toString();
                lugar.clear();
                lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
                lugar.exec();
                lugar.next();
                lugar.clear();
                QDateTime actual;
                actual=QDateTime::currentDateTime();
                lugar.prepare("call Venta('"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+matriculab.value(0).toString()+"','"+IdOperador+"','"+lugare+"')");
                lugar.exec();
                lugar.next();
                ui->IdSocio->clear();
                ui->Matricula->clear();
                ui->MatriculaDif->click();
                ui->Matricula_2->clear();
                ui->Matricula->setVisible(false);
                ui->MatriculaDif->setVisible(false);
                ui->Matricula_2->setVisible(false);
                QMessageBox::information(this,"Acceso Autorizado","Acceso Autorizado.\nIngresar al cajón "+lugare);
            }
        }
        else{
            matricula=ui->Matricula->text();
            if(matricula!=""){
                    QSqlQuery lugar(mdb);
                    lugar.prepare("select * from Estacionamiento_Socio where Estatus='Libre'");
                    lugar.exec();
                    lugar.next();
                    lugare=lugar.value(0).toString();
                    lugar.clear();
                    lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
                    lugar.exec();
                    lugar.next();
                    lugar.clear();
                    QDateTime actual;
                    actual=QDateTime::currentDateTime();
                    lugar.prepare("call Venta('"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+actual.toString("yyyy-MM-dd hh:mm:ss")+"','"+matricula+"','"+IdOperador+"','"+lugare+"')");
                    lugar.exec();
                    lugar.next();
                    lugar.clear();
                    lugar.prepare("select matricula from vehiculo where matricula='"+matricula+"'");
                    lugar.exec();
                    if(lugar.next()){
                        lugar.clear();
                        lugar.prepare("Insert Into Ingreso_Temporal(IdSocio,Matricula) values('"+id+"','"+matricula+"')");
                        lugar.exec();
                        lugar.next();
                    }
                    else{
                        lugar.clear();
                        lugar.prepare("Insert Into Vehiculo(Matricula) values('"+matricula+"')");
                        lugar.exec();
                        lugar.next();
                        lugar.clear();
                        lugar.prepare("Insert Into Ingreso_Temporal(IdSocio,Matricula) values('"+id+"','"+matricula+"')");
                        lugar.exec();
                        lugar.next();
                    }
                    ui->IdSocio->clear();
                    ui->Matricula->clear();
                    ui->MatriculaDif->click();
                    ui->Matricula_2->clear();
                    ui->Matricula->setVisible(false);
                    ui->MatriculaDif->setVisible(false);
                    ui->Matricula_2->setVisible(false);
                    QMessageBox::information(this,"Acceso Autorizado","Acceso Autorizado.\nIngresar al cajón "+lugare);

            }
            else{
                QMessageBox::critical(this,"Error","Debes introducir una matricula.");
            }
        }

    }
}
