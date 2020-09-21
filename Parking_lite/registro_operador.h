#ifndef REGISTRO_OPERADOR_H
#define REGISTRO_OPERADOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Registro_operador;
}

class Registro_operador : public QDialog
{
    Q_OBJECT

public:
    explicit Registro_operador(QWidget *parent = nullptr);
    ~Registro_operador();

private slots:
    void on_CerrarSesion_clicked();

    void on_Guardar_clicked();

private:
    Ui::Registro_operador *ui;
    QSqlDatabase mdb;
};

#endif // REGISTRO_OPERADOR_H
