#ifndef COBRAR_ESTACIONAMIENTO_H
#define COBRAR_ESTACIONAMIENTO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class cobrar_Estacionamiento;
}

class cobrar_Estacionamiento : public QDialog
{
    Q_OBJECT

public:
    explicit cobrar_Estacionamiento(QString IdOperador,QWidget *parent = nullptr);
    ~cobrar_Estacionamiento();

private slots:
    void on_BtnRegresar_clicked();

    void on_BtnCobrar_clicked();

private:
    Ui::cobrar_Estacionamiento *ui;
    QString IdOperador;
    QSqlDatabase mdb;
};

#endif // COBRAR_ESTACIONAMIENTO_H
