#ifndef REGISTRO_CLIENTE_H
#define REGISTRO_CLIENTE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Registro_cliente;
}

class Registro_cliente : public QDialog
{
    Q_OBJECT

public:
    explicit Registro_cliente(QWidget *parent = nullptr);
    ~Registro_cliente();

private slots:
    void on_CerrarSesion_clicked();

    void on_Guardar_clicked();

private:
    Ui::Registro_cliente *ui;
    QSqlDatabase mdb;
};

#endif // REGISTRO_CLIENTE_H
