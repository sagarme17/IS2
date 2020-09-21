#ifndef SOCIO_CLIENTE_H
#define SOCIO_CLIENTE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Socio_Cliente;
}

class Socio_Cliente : public QDialog
{
    Q_OBJECT

public:
    explicit Socio_Cliente(QString,QWidget *parent = nullptr);
    ~Socio_Cliente();

private slots:

    void on_BtnRegresar_clicked();

    void on_Socio_sin_reservacion_clicked();

    void on_Socio_con_reservacion_clicked();

private:
    Ui::Socio_Cliente *ui;
    QString IdOperador;
    QSqlDatabase mdb;
};

#endif // SOCIO_CLIENTE_H
