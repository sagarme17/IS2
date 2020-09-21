#ifndef ESTATUS_ESTACIONAMIENTO_H
#define ESTATUS_ESTACIONAMIENTO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Estatus_Estacionamiento;
}

class Estatus_Estacionamiento : public QDialog
{
    Q_OBJECT

public:
    explicit Estatus_Estacionamiento(QWidget *parent = nullptr);
    ~Estatus_Estacionamiento();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Estatus_Estacionamiento *ui;

};

#endif // ESTATUS_ESTACIONAMIENTO_H
