#include "cuentas.h"
#include "ui_cuentas.h"
#include <QTableWidgetItem>
cuetas_operador::cuetas_operador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cuetas_operador)
{
    ui->setupUi(this);
    this->mdb=QSqlDatabase::database("Connection");
    ui->Socio->setVisible(false);
    ui->Operador->setVisible(false);

}

cuetas_operador::~cuetas_operador()
{
    delete ui;
}

void cuetas_operador::on_Regresar_clicked()
{
    close();
}

void cuetas_operador::on_Opcion_currentTextChanged(const QString &arg1)
{
    if(mdb.open()){
        ui->Socio->setVisible(false);
        ui->Operador->setVisible(false);
        ui->Socio->setRowCount(0);
        ui->Operador->setRowCount(0);
        QSqlQuery getusuario(mdb);
        if(arg1=="Socios"){
            getusuario.prepare("select IdSocio, Nombre, A_Paterno, A_Materno, Telefono, Correo from Socio inner join Usuario on IdSocio=IdUsuario");
            getusuario.exec();
            while (getusuario.next()) {
                QTableWidgetItem *uno=new QTableWidgetItem(getusuario.value(0).toString());
                QTableWidgetItem *dos=new QTableWidgetItem(getusuario.value(1).toString());
                QTableWidgetItem *tres=new QTableWidgetItem(getusuario.value(2).toString());
                QTableWidgetItem *cuatro=new QTableWidgetItem(getusuario.value(3).toString());
                QTableWidgetItem *cinco=new QTableWidgetItem(getusuario.value(4).toString());
                QTableWidgetItem *seis=new QTableWidgetItem(getusuario.value(5).toString());
                ui->Socio->setRowCount(ui->Socio->rowCount()+1);
                ui->Socio->setItem(ui->Socio->rowCount()-1,0,uno);
                ui->Socio->setItem(ui->Socio->rowCount()-1,1,dos);
                ui->Socio->setItem(ui->Socio->rowCount()-1,2,tres);
                ui->Socio->setItem(ui->Socio->rowCount()-1,3,cuatro);
                ui->Socio->setItem(ui->Socio->rowCount()-1,4,cinco);
                ui->Socio->setItem(ui->Socio->rowCount()-1,5,seis);
            }
            ui->Socio->setVisible(true);
        }
        else if(arg1=="Operadores"){
            getusuario.prepare("select IdOperador,Nombre, A_Paterno, A_Materno, Telefono from Operador inner join Usuario on IdOperador=IdUsuario");
            getusuario.exec();
            while (getusuario.next()) {
                QTableWidgetItem *uno=new QTableWidgetItem(getusuario.value(0).toString());
                QTableWidgetItem *dos=new QTableWidgetItem(getusuario.value(1).toString());
                QTableWidgetItem *tres=new QTableWidgetItem(getusuario.value(2).toString());
                QTableWidgetItem *cuatro=new QTableWidgetItem(getusuario.value(3).toString());
                QTableWidgetItem *cinco=new QTableWidgetItem(getusuario.value(4).toString());
                ui->Operador->setRowCount(ui->Operador->rowCount()+1);
                ui->Operador->setItem(ui->Operador->rowCount()-1,0,uno);
                ui->Operador->setItem(ui->Operador->rowCount()-1,1,dos);
                ui->Operador->setItem(ui->Operador->rowCount()-1,2,tres);
                ui->Operador->setItem(ui->Operador->rowCount()-1,3,cuatro);
                ui->Operador->setItem(ui->Operador->rowCount()-1,4,cinco);
            }
            ui->Operador->setVisible(true);
        }
    }
}
