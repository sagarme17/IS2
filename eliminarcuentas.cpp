#include "eliminarcuentas.h"
#include "ui_eliminarcuentas.h"

EliminarCuentas::EliminarCuentas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EliminarCuentas)
{
    ui->setupUi(this);
}

EliminarCuentas::~EliminarCuentas()
{
    delete ui;
}
