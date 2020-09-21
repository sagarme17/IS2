#include "tramitar_membresia.h"
#include "ui_tramitar_membresia.h"
#include <QList>
#include <QMessageBox>
tramitar_Membresia::tramitar_Membresia(QString IdSocio,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tramitar_Membresia)
{
    ui->setupUi(this);
    this->IdSocio=IdSocio;
    this->mdb=QSqlDatabase::database("Connection");
    if(mdb.open()){
        QSqlQuery usuario(mdb);
        usuario.prepare("select IdSocio, Nombre, A_Paterno, A_Materno, Correo, NumTarjeta from Socio inner join Usuario on IdSocio=IdUsuario where IdSocio='"+IdSocio+"'");
        usuario.exec();
        if(usuario.next()){
            ui->IdSocio->setText("Id de Socio: "+usuario.value(0).toString());
            ui->Nombre->setText("Socio: "+usuario.value(1).toString()+" "+usuario.value(2).toString()+" "+usuario.value(3).toString());
            ui->Correo->setText("Correo: "+usuario.value(4).toString());
            ui->NumeroTarjeta->setText("Numero de Tarjeta: "+usuario.value(5).toString());
        }
        QDate actual;
        actual=QDate::currentDate();
        ui->fecha_Membresia->setMinimumDate(actual.addDays(1));
        ui->dateEdit->setMinimumDate(actual.addMonths(1));

    }
}

tramitar_Membresia::~tramitar_Membresia()
{
    delete ui;
}

void tramitar_Membresia::on_Cancelar_clicked()
{
    close();
}

void tramitar_Membresia::on_Tramitar_clicked()
{
    if(mdb.open()){
        if(ui->CVV_Tarjeta->text().size()==3){
            QSqlQuery membresia(mdb),lugar(mdb);
            lugar.prepare("select idEstacionamiento_socio from estacionamiento_socio where estatus='Libre' order by idestacionamiento_socio desc");
            lugar.exec();
            QString luga;
            while (lugar.next()) {
                luga=lugar.value(0).toString();
            }
            if(luga!=""){
                membresia.prepare("Insert Into membresia(IdSocio,FechaInicio,FechaFinal,IdEstacionamiento_Socio) value('"+IdSocio+"','"+ui->fecha_Membresia->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"','"+ui->fecha_Membresia->dateTime().addDays(31).toString("yyyy-MM-dd hh:mm:ss")+"','"+luga+"')");
                membresia.exec();
                membresia.next();
                lugar.clear();
                lugar.prepare("update estacionamiento_socio set estatus='Mensual' where IdEstacionamiento_socio='"+luga+"'");
                lugar.exec();
                lugar.next();
                QMessageBox::information(this,"Reservación Mensual","Reservacion mensual activada.\nSu reservación vence el "+ui->fecha_Membresia->dateTime().addDays(31).toString("dd-MM-yyyy")+".\nSu cajón es "+luga);
                close();
            }
            else{
                lugar.clear();
                lugar.prepare("select idestacionamiento_socio from reservación where inicio>='"+ui->fecha_Membresia->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"' and final<='"+ui->fecha_Membresia->dateTime().addDays(31).toString("yyyy-MM-dd hh:mm:ss")+"'");
                lugar.exec();
                QList<int>espacios;
                while (lugar.next()) {
                    espacios.append(lugar.value(0).toInt());
                }

                lugar.clear();
                lugar.prepare("select idestacionamiento_socio from membresia where fechainicio>='"+ui->fecha_Membresia->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"' and fechafinal<='"+ui->fecha_Membresia->dateTime().addDays(31).toString("yyyy-MM-dd hh:mm:ss")+"'");
                lugar.exec();
                while (lugar.next()) {
                    espacios.append(lugar.value(0).toInt());
                }
                int espa=0;
                lugar.clear();
                lugar.prepare("select idEstacionamiento_Socio from Estacionamiento_Socio");
                lugar.exec();
                while (lugar.next()) {
                    if(!espacios.contains(lugar.value(0).toInt())){
                        espa=lugar.value(0).toInt();
                    }
                }
                if(espa!=0){
                    membresia.prepare("Insert Into membresia(IdSocio,FechaInicio,FechaFinal,IdEstacionamiento_Socio) value('"+IdSocio+"','"+ui->fecha_Membresia->dateTime().toString("yyyy-MM-dd hh:mm:ss")+"','"+ui->fecha_Membresia->dateTime().addDays(31).toString("yyyy-MM-dd hh:mm:ss")+"','"+QString::number(espa)+"')");
                    membresia.exec();
                    membresia.next();
                    lugar.clear();
                    lugar.prepare("update estacionamiento_socio set estatus='Mensual' where IdEstacionamiento_socio='"+QString::number(espa)+"'");
                    lugar.exec();
                    lugar.next();
                }
                QMessageBox::information(this,"Reservación Mensual","Reservacion mensual activada.\nSu reservación vence el "+ui->fecha_Membresia->dateTime().addDays(31).toString("dd-MM-yyyy")+".\nSu cajón es "+QString::number(espa));
                close();
            }


        }
        else{
            QPalette falta;
            falta.setColor(ui->CVV_Tarjeta->foregroundRole(),Qt::red);
            ui->CVV_Tarjeta->setPalette(falta);
        }
    }
}
