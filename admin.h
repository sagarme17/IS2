#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QString IdAdministrador,QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_CerrarSesion_clicked();

    void on_RegistrodeVentas_clicked();

    void on_Actualizar_tarifa_clicked();

    void on_Registrar_operador_clicked();

    void on_Ver_cuentas_clicked();

private:
    Ui::admin *ui;
    QString IdAdministrador;
};

#endif // ADMIN_H
