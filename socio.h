#ifndef SOCIO_H
#define SOCIO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class socio;
}

class socio : public QDialog
{
    Q_OBJECT

public:
    explicit socio(QString IdSocio,QWidget *parent = nullptr);
    ~socio();

private slots:
    void on_CerrarSesion_clicked();

    void on_ReservaMnesual_clicked();

private:
    Ui::socio *ui;
    QString IdSocio;
    QSqlDatabase mdb;
};

#endif // SOCIO_H
