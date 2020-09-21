#include "reservacion.h"
#include "ui_reservacion.h"

Reservacion::Reservacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservacion)
{
    ui->setupUi(this);
}

Reservacion::~Reservacion()
{
    delete ui;
}
