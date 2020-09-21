#include "dar_salida_reservacion.h"
#include "ui_dar_salida_reservacion.h"

dar_salida_reservacion::dar_salida_reservacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dar_salida_reservacion)
{
    ui->setupUi(this);
}

dar_salida_reservacion::~dar_salida_reservacion()
{
    delete ui;
}
