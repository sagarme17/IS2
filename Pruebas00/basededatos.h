#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

class baseDatos
{
public:
    baseDatos();

    QSqlDatabase mDatabase;

    QString BuscarAdmin (int);
    QString BuscarOperador(int);
    QString BuscarSocio(int);
    bool Actualizar_TarifaM(double);
    bool Actualizar_TarifaH(double);
    QString BuscarVenta(QString);
    bool InsertarSocio(QString,QString,QString,QString,QString,QString,QString,QString);
    bool InsertarOperador(QString,QString,QString,QString,QString);
    bool AccesoSocioSR_p1(QString,QString);
    bool AccsesoSocioCR_p1(int);
    bool VerSocio(int id);
    bool VerOperador(int id);
    bool VerMembresia(int id);
    bool Venta(QString matricula);
    bool Reservacion(QString,QString,int,int);
    bool EntradaCliente(QString);//,int);
    bool VerVentasSemanales();


};

#endif // BASEDEDATOS_H
