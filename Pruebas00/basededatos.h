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
    /*PrimeraIteración*/
    QString BuscarAdmin (int);
    QString BuscarOperador(int);
    QString BuscarSocio(int);
    bool Actualizar_TarifaM(double);
    bool Actualizar_TarifaH(double);
    /*SegundaIteración*/
    QString BuscarVenta(QString);
    bool InsertarSocio(QString,QString,QString,QString,QString,QString,QString,QString);
    bool InsertarOperador(QString,QString,QString,QString,QString);
    bool AccesoSocioSR_p1(QString,QString);
    bool AccsesoSocioCR_p1(int);
    /*TerceraIteración*/
    bool VerSocio(int id);
    bool VerOperador(int id);
    bool VerMembresia(int id);
    bool Venta(QString matricula);
    /*CuartaIteración*/
    void EliminarOperador(int idOp);
    void EliminarSocio(int idSo);
    void ActualizarSocio(int,QString,QString,QString,QString,QString,QString);

};

#endif // BASEDEDATOS_H
