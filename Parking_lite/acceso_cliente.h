#ifndef ACCESO_CLIENTE_SOCIO_H
#define ACCESO_CLIENTE_SOCIO_H
#define ACTUALIZAR_TARIFA_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Acceso_cliente_socio;
}

class Acceso_cliente_socio : public QDialog
{
    Q_OBJECT

public:
    explicit Acceso_cliente_socio(QString,QWidget *parent = nullptr);
    ~Acceso_cliente_socio();

private slots:
    void on_BtnRegresar_clicked();

    void on_BuscarSocio_clicked();


    void on_MatriculaDif_clicked();

    void on_Guardar_2_clicked();

private:
    Ui::Acceso_cliente_socio *ui;
    QSqlDatabase mdb;
    QString IdOperador;
};

#endif // ACCESO_CLIENTE_SOCIO_H
