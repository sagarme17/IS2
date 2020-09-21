#include "modificardatos.h"
#include "ui_modificardatos.h"

ModificarDatos::ModificarDatos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarDatos)
{
    ui->setupUi(this);
}

ModificarDatos::~ModificarDatos()
{
    delete ui;
}
