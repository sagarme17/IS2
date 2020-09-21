#include "admin.h"
#include "ui_admin.h"
#include "ventas_diarias.h"
#include "actualizar_tarifa.h"
#include "registro_operador.h"
#include "cuentas.h"

admin::admin(QString IdAdministrador,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->IdAdministrador=IdAdministrador;
}

admin::~admin()
{
    delete ui;
}

void admin::on_CerrarSesion_clicked()
{
    close();
}

void admin::on_RegistrodeVentas_clicked()
{
    Ventas_Diarias ven_dia(this);
    ven_dia.setWindowTitle("Registro de ventas");
    ven_dia.exec();
}

void admin::on_Actualizar_tarifa_clicked()
{
    Actualizar_Tarifa act_taf(this);
    act_taf.setWindowTitle("Actualizar Tarifas");
    act_taf.exec();
}

void admin::on_Registrar_operador_clicked()
{
    Registro_operador res_op(this);
    res_op.setWindowTitle("Registrar operador");
    res_op.exec();

}

void admin::on_Ver_cuentas_clicked()
{
    cuetas_operador cuen(this);
    cuen.setWindowTitle("Registro de usuarios");
    cuen.exec();
}
