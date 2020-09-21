#include "estatus_estacionamiento.h"
#include "ui_estatus_estacionamiento.h"

Estatus_Estacionamiento::Estatus_Estacionamiento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Estatus_Estacionamiento)
{
    ui->setupUi(this);
}

Estatus_Estacionamiento::~Estatus_Estacionamiento()
{
    delete ui;
}

void Estatus_Estacionamiento::on_pushButton_clicked()
{
    close();
}
