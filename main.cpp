#include "inicio_de_sesion.h"
#include <QtSql/QSqlDatabase>
#include <QApplication>


int main(int argc, char *argv[])
{
    QSqlDatabase mdb;

    mdb= QSqlDatabase::addDatabase("QODBC","Connection");
    mdb.setDatabaseName("parking_lite");
    QApplication a(argc, argv);
    Inicio_De_Sesion w;
    w.setWindowTitle("Parking Lite");
    w.show();
    return a.exec();
}
