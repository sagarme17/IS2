#ifndef ACCESOS_SOCIO_H
#define ACCESOS_SOCIO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class accesos_socio;
}

class accesos_socio : public QDialog
{
    Q_OBJECT

public:
    explicit accesos_socio(QString,QWidget *parent = nullptr);
    ~accesos_socio();

private slots:


    void on_Buscar_clicked();

    void on_MatriculaDif_clicked();
    
    void on_BtnRegresar_clicked();
    
    void on_Permitir_acceso_clicked();

private:
    Ui::accesos_socio *ui;
    QSqlDatabase mdb;
    QString IdOperador;
};

#endif // ACCESOS_SOCIO_H
