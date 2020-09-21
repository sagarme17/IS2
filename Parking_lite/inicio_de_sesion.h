#ifndef INICIO_DE_SESION_H
#define INICIO_DE_SESION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Inicio_De_Sesion;
}

class Inicio_De_Sesion : public QDialog
{
    Q_OBJECT

public:
    explicit Inicio_De_Sesion(QWidget *parent = nullptr);
    ~Inicio_De_Sesion();

private slots:
    void on_Inicio_sesion_clicked();

    void on_Registrarse_clicked();

private:
    Ui::Inicio_De_Sesion *ui;
    QSqlDatabase mdb;
};

#endif // INICIO_DE_SESION_H
