#include "accesos_socio.h"
#include "ui_accesos_socio.h"
#include <QMessageBox>
#include <QDateTime>
//Acceso Socio Con Reservación
accesos_socio::accesos_socio(QString IdOperador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accesos_socio)
{
    this->mdb=QSqlDatabase::database("Connection");
    this->IdOperador=IdOperador;
    ui->setupUi(this);
    ui->Matricula->setVisible(false);
    ui->MatriculaDif->setVisible(false);
    ui->Matricula_2->setVisible(false);
}

accesos_socio::~accesos_socio()
{
    delete ui;
}



void accesos_socio::on_Buscar_clicked()
{
    if(mdb.open()){
        ui->Reservaciones->setRowCount(0);
        ui->Matricula->clear();
        ui->Matricula_2->clear();
        ui->Matricula->setVisible(false);
        ui->MatriculaDif->setVisible(false);
        ui->Matricula_2->setVisible(false);
        QString id;
        id=ui->IdSocio->text();
        QSqlQuery idbuscar(mdb),reserva(mdb);
        idbuscar.prepare("select IdSocio from Socio where IdSocio = '"+id+"'");
        idbuscar.exec();
        QDateTime actual;
        actual=QDateTime::currentDateTime();
        if(idbuscar.next()){
            reserva.prepare("select * from reservación inner join estacionamiento_socio on reservación.idestacionamiento_socio=estacionamiento_socio.idestacionamiento_socio where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Estatus='Reservado'");
            reserva.exec();
            if(reserva.next()){
                QSqlQuery matricula(mdb),reservaciones(mdb);
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
                reservaciones.prepare("select IdReservación, Inicio, Final,IdEstacionamiento_Socio from Reservación where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"'");
                reservaciones.exec();
                QTime inicio,final;
                ui->Reservaciones->setRowCount(0);
                while (reservaciones.next()) {
                    inicio=reservaciones.value(1).toTime();
                    final=reservaciones.value(2).toTime();
                    QTableWidgetItem *uno=new QTableWidgetItem(reservaciones.value(0).toString());
                    QTableWidgetItem *dos=new QTableWidgetItem(inicio.toString("hh:mm"));
                    QTableWidgetItem *tres=new QTableWidgetItem(final.toString("hh:mm"));
                    QTableWidgetItem *cuatro=new QTableWidgetItem(reservaciones.value(3).toString());
                    ui->Reservaciones->setRowCount(ui->Reservaciones->rowCount()+1);
                    ui->Reservaciones->setItem(ui->Reservaciones->rowCount()-1,0,uno);
                    ui->Reservaciones->setItem(ui->Reservaciones->rowCount()-1,1,dos);
                    ui->Reservaciones->setItem(ui->Reservaciones->rowCount()-1,2,tres);
                    ui->Reservaciones->setItem(ui->Reservaciones->rowCount()-1,3,cuatro);
                }
            }
            else{
                QMessageBox::warning(this,"Atención","Socio sin reservación programada.");
                ui->Reservaciones->setRowCount(0);
                ui->IdSocio->clear();
                ui->Matricula->clear();
                ui->MatriculaDif->click();
                ui->Matricula_2->clear();
                ui->Matricula->setVisible(false);
                ui->MatriculaDif->setVisible(false);
                ui->Matricula_2->setVisible(false);
            }

        }
        else{
            QMessageBox::critical(this,"Error","Id de Socio ivalido.");
        }
    }
}

void accesos_socio::on_MatriculaDif_clicked()
{
    if(ui->MatriculaDif->isChecked()){
        ui->Matricula->setVisible(true);
    }
    else{
        ui->Matricula->setVisible(false);
    }
}

void accesos_socio::on_BtnRegresar_clicked()
{
    close();
}

void accesos_socio::on_Permitir_acceso_clicked()
{
    if(mdb.open()){

        QString id,matricula,lugare;
        id=ui->IdSocio->text();
        QSqlQuery idbuscar(mdb),reserva(mdb),matriculab(mdb);
        QDateTime actual;
        actual=QDateTime::currentDateTime();
        idbuscar.prepare("select IdSocio from Socio where IdSocio = '"+id+"'");
        idbuscar.exec();
        reserva.prepare("select * from reservación inner join estacionamiento_socio on reservación.idestacionamiento_socio=estacionamiento_socio.idestacionamiento_socio where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Estatus='Reservado'");
        reserva.exec();
        bool idexists=idbuscar.next(),reservaexists=reserva.next();
        if(idexists and reservaexists){
            matriculab.prepare("Select Matricula from matricula_registrada where IdSocio='"+id+"'");
            matriculab.exec();
            if(matriculab.next()){
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
                            lugar.prepare("select IdEstacionamiento_Socio from Reservación where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"'");
                            lugar.exec();
                            lugar.next();
                            lugare=lugar.value(0).toString();
                            lugar.clear();
                            lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
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
                            ui->Reservaciones->setRowCount(0);
                            ui->IdSocio->clear();
                            ui->Matricula->clear();
                            ui->MatriculaDif->click();
                            ui->Matricula_2->clear();
                            ui->Matricula->setVisible(false);
                            ui->MatriculaDif->setVisible(false);
                            ui->Matricula_2->setVisible(false);
                            QMessageBox::information(this,"Acceso Autorizado","Reservación Activada\nIngresar al cajón "+lugare);
                        }
                    }
                    else{
                        QMessageBox::critical(this,"Error","Debes introducir una matricula.");
                    }
                }
                else{
                    QDateTime actual;
                    actual=QDateTime::currentDateTime();
                    QSqlQuery lugar(mdb);
                    lugar.prepare("select IdEstacionamiento_Socio from Reservación where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"'");
                    lugar.exec();
                    lugar.next();
                    lugare=lugar.value(0).toString();
                    lugar.clear();
                    lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
                    lugar.exec();
                    lugar.next();
                    ui->Reservaciones->setRowCount(0);
                    ui->IdSocio->clear();
                    ui->Matricula->clear();
                    ui->MatriculaDif->click();
                    ui->Matricula_2->clear();
                    ui->Matricula->setVisible(false);
                    ui->MatriculaDif->setVisible(false);
                    ui->Matricula_2->setVisible(false);
                    QMessageBox::information(this,"Acceso Autorizado","Reservación Activada\nIngresar al cajón "+lugare);
                }
            }
            else{
                matricula=ui->Matricula->text();
                if(matricula!=""){
                    QDateTime actual;
                    actual=QDateTime::currentDateTime();
                    QSqlQuery lugar(mdb);
                    lugar.prepare("select IdEstacionamiento_Socio from Reservación where IdSocio='"+id+"' and Final >= '"+actual.toString("yyyy-MM-dd hh:mm:ss")+"' and Inicio <='"+actual.toString("yyyy-MM-dd hh:mm:ss")+"'");
                    lugar.exec();
                    lugar.next();
                    lugare=lugar.value(0).toString();
                    lugar.clear();
                    lugar.prepare("Update Estacionamiento_socio SET Estatus ='Ocuapdo' where IdEstacionamiento_Socio='"+lugare+"'");
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
                    ui->Reservaciones->setRowCount(0);
                    ui->IdSocio->clear();
                    ui->Matricula->clear();
                    ui->MatriculaDif->click();
                    ui->Matricula_2->clear();
                    ui->Matricula->setVisible(false);
                    ui->MatriculaDif->setVisible(false);
                    ui->Matricula_2->setVisible(false);
                    QMessageBox::information(this,"Acceso Autorizado","Reservación Activada\nIngresar al cajón "+lugare);
                }
                else{
                    QMessageBox::critical(this,"Error","Debes introducir una matricula.");
                }
            }
        }
        else if(!idexists){
            QMessageBox::critical(this,"Error","Id de Socio incorrecto.");
            ui->Reservaciones->setRowCount(0);
            ui->IdSocio->clear();
            ui->Matricula->clear();
            ui->MatriculaDif->click();
            ui->Matricula_2->clear();
            ui->Matricula->setVisible(false);
            ui->MatriculaDif->setVisible(false);
            ui->Matricula_2->setVisible(false);
        }
        else if(!reservaexists){
            QMessageBox::warning(this,"Atención","Socio sin reservación programada.");
            ui->Reservaciones->setRowCount(0);
            ui->IdSocio->clear();
            ui->Matricula->clear();
            ui->MatriculaDif->click();
            ui->Matricula_2->clear();
            ui->Matricula->setVisible(false);
            ui->MatriculaDif->setVisible(false);
            ui->Matricula_2->setVisible(false);
        }





    }
}
