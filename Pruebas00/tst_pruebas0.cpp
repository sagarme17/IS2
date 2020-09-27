#include <QtTest>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include "basededatos.h"


// add necessary includes here

class Pruebas0 : public QObject
{
    Q_OBJECT

public:
    Pruebas0();
    ~Pruebas0();
    baseDatos *conexion;

private slots:
    void conexionBase();
    void BuscarAdmin();
    void BuscarOperador();
    void BuscarCliente();
    void ActualizarTarifaM();
    void ActualizarTarifaH();
    void BuscarVenta(); //?
    void RegistroSocio();
    void RegistroOperador();
    void AccesoSocioSR_1();
    void AccesoSocioCR_1();
    void VerSocio();
    void VerOperador();
    void Membresia();
    void Venta();
    void Reservacion();
    void EntradaCliente();
    void VentasVistas();

};

Pruebas0::Pruebas0()
{
    conexion = new baseDatos();
}
Pruebas0::~Pruebas0(){}

void Pruebas0::conexionBase()
{

    QVERIFY(conexion->mDatabase.open());
}

void Pruebas0::BuscarAdmin()
{
     QCOMPARE(conexion->BuscarAdmin(100001),"Pedro");
}
void Pruebas0::BuscarVenta()
{

     QCOMPARE(conexion->BuscarVenta("2020-09-05"),"2020-9-5");

}
void Pruebas0::BuscarCliente()
{
    QCOMPARE(conexion->BuscarSocio(100003),"Luis");
}
void Pruebas0::ActualizarTarifaM()
{
    QVERIFY(conexion->Actualizar_TarifaM(1280.50));
}
void Pruebas0::ActualizarTarifaH()
{
    QVERIFY(conexion->Actualizar_TarifaH(28.50));
}
void Pruebas0::BuscarOperador()
{
    QCOMPARE(conexion->BuscarOperador(100002),"Juan");
}

void Pruebas0::RegistroSocio()
{
    QCOMPARE(conexion->InsertarSocio("Pepe","Lagunes","Perez","666666","2711950192","tunomabre@gmail.com","1234567890123456","Pepe Lagunes Perez"),true);
}
void Pruebas0::RegistroOperador()
{
    QCOMPARE(conexion->InsertarOperador("Luis","Roman","Salazar","777777","2711750392"),true);
}

void Pruebas0::AccesoSocioSR_1()
{
    QCOMPARE(conexion->AccesoSocioSR_p1("DFGA2385","100003"),true);  //verificamos que si tenga una matricula registrada que este asociada con un idSocio (r=100006)
}
void Pruebas0::AccesoSocioCR_1()
{
    QCOMPARE(conexion->AccsesoSocioCR_p1(100006),true);
}

void Pruebas0::VerSocio()
{
    QCOMPARE(conexion->VerSocio(100003),true);
}

void Pruebas0::VerOperador()
{
    QCOMPARE(conexion->VerOperador(100002),true);
}

void Pruebas0::Membresia()
{
    QCOMPARE(conexion->VerMembresia(100003),true);
}
void Pruebas0::Venta()
{
    QCOMPARE(conexion->Venta("SDFW3453"),true);
}
void Pruebas0::Reservacion()
{
    QCOMPARE(conexion->Reservacion("2020-09-26","2020-09-26",3,100004),true);
}
void Pruebas0::EntradaCliente()
{
    QCOMPARE(conexion->EntradaCliente("Ocupado"),true );
}
void Pruebas0::VentasVistas()
{
    QCOMPARE(conexion->VerVentasSemanales(),true);
}
QTEST_APPLESS_MAIN(Pruebas0)

#include "tst_pruebas0.moc"
