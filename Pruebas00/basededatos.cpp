#include "basededatos.h"
#include <QtTest>
#include<QDateTime>
#include <QDate>
baseDatos::baseDatos()
{
    mDatabase = QSqlDatabase::addDatabase("QODBC","Connection");
    //mDatabase.setPort(3306);
    //mDatabase.setHostName("localhost");
    //mDatabase.setUserName("root");
    //mDatabase.setPassword("");
    mDatabase.setDatabaseName("parking_lite");
}

QString baseDatos::BuscarAdmin(int id)
{
    QString nombreA;
    QString id_p= QString::number(id);
    QSqlQuery query1(mDatabase);
    query1.prepare("select IdAdministrador,Nombre,Contraseña  from Usuario inner join Administrador on IdAdministrador=IdUsuario where IdUsuario='"+id_p+"'");
    query1.exec();
    while(query1.next())
     {
        nombreA=query1.value(1).toString();
     }
    return nombreA;
}

QString baseDatos::BuscarOperador(int id)
{
    QString nombreA;
    QSqlQuery query1(mDatabase);
    query1.prepare("select IdOperador,Nombre,Contraseña  from Usuario inner join Operador on IdOperador=IdUsuario where IdUsuario='"+QString::number(id)+"'");
    query1.exec();
    while(query1.next())
     {
        nombreA=query1.value(1).toString();
     }
    return nombreA;
}

QString baseDatos::BuscarSocio(int id)
{
    QString nombreA;
    QSqlQuery query1(mDatabase);
    query1.prepare("select IdSocio,Nombre,Contraseña  from Usuario inner join Socio on IdSocio=IdUsuario where IdUsuario='"+QString::number(id)+"'");
    query1.exec();
    while(query1.next())
     {
        nombreA=query1.value(1).toString();
     }
    return nombreA;
}

bool baseDatos::Actualizar_TarifaM(double precio)
{

    QSqlQuery nuevatarifa(mDatabase);
    if(nuevatarifa.exec("UPDATE tarifas SET TarifaMensual='"+QString::number(precio)+"'"))
    {
        return true;
    }else
    {
        return false;
    }
}
bool baseDatos::Actualizar_TarifaH(double precio)
{
    QSqlQuery nuevatarifa(mDatabase);
    if(nuevatarifa.exec("UPDATE tarifas SET TarifaHora='"+QString::number(precio)+"'"))
    {
        return true;
    }else
    {
        return false;
    }
}

QString baseDatos::BuscarVenta(QString fecha)
{
    QSqlQuery queryv(mDatabase);
    QDate fecha_r;
    queryv.prepare("SELECT FechaInicio,FechaFinal FROM VENTA where FechaInicio between '"+fecha+" 00:00:00' and '"+fecha+" 23:59:59'");
    queryv.exec();
    queryv.next();
    while(queryv.next())
    {

        fecha_r=queryv.value(0).toDate();
    }

    QString fecha_rr=QString::number(fecha_r.year())+"-"+QString::number(fecha_r.month())+"-"+ QString::number(fecha_r.day());
    return fecha_rr;
}

bool baseDatos::InsertarSocio(QString, QString, QString, QString, QString, QString, QString, QString)
{
    QSqlQuery registro(mDatabase);
    QString nombre, a_paterno, a_materno,contrasenia,telefono,correo,numtarjeta,titulartarjeta;
    if(registro.exec("call RegistroSocio('"+nombre+"','"+a_paterno+"','"+a_materno+"','"+contrasenia+"','"+telefono+"','"+correo+"','"+numtarjeta+"','"+titulartarjeta+"')"))
    {
        return true;
    }else
    {
        return false;
    }
}

bool baseDatos::InsertarOperador(QString, QString, QString, QString, QString)
{
    QSqlQuery registro(mDatabase);
    QString nombre, a_paterno, a_materno,contrasenia,telefono;
    if(registro.exec("call RegistroOper('"+nombre+"','"+a_paterno+"','"+a_materno+"','"
                     +contrasenia+"','"+telefono+"')"))
    {
        return true;
    }else
    {
        return false;
    }
}

bool baseDatos::AccesoSocioSR_p1(QString, QString)
{
     QSqlQuery acceso(mDatabase);
     QString matricula, id;
     if(acceso.exec("Select Matricula from Ingreso_Temporal where Matricula='"+matricula+"' and ingreso_temportal.IdSocio='"+id+"'"))
     {
         return true;

     }else {
         {
             return false;
         }
     }
}
bool baseDatos::AccsesoSocioCR_p1(int id)
{
    QSqlQuery acceso(mDatabase);

    if(acceso.exec("Select socio.IdSocio from socio inner join reservación on socio.IdSocio=reservación.IdSocio where reservación.IdSocio='"+QString::number(id)+"'"))
    {
        return true;
    }else
    {
        return false;
    }
}

bool baseDatos::VerSocio(int id)
{
     QSqlQuery verSocio(mDatabase);
     verSocio.prepare("select IdSocio, Nombre, A_Paterno, A_Materno, Telefono, Correo from socio inner join usuario on usuario.idUsuario=socio.IdSocio where socio.IdSocio='"+QString::number(id)+"'");
     verSocio.exec();
     if(verSocio.next())
     {
         return true;
     }else
     {
         return false;
     }
}

bool baseDatos::VerOperador(int id)
{
    QSqlQuery verOp(mDatabase);
    verOp.prepare("select IdOperador, Nombre, A_Paterno, A_Materno, Telefono from operador inner join usuario on usuario.idUsuario=operador.IdOperador where operador.IdOperador='"+QString::number(id)+"'");
    verOp.exec();
    if(verOp.next())
    {
        return true;
    }else
    {
        return false;
    }
}

bool baseDatos::VerMembresia(int id)
{
    QSqlQuery Membresia(mDatabase);
    Membresia.prepare("select idmembresia from membresia where membresia.idSocio='"+QString::number(id)+"'");
    Membresia.exec();
    if(Membresia.next())
    {
        return true;
    }else
    {
        return false;
    }
}


bool baseDatos::Venta(QString matricula)
{
    QSqlQuery Venta(mDatabase);

    QDateTime actual;
    Venta.prepare(("select FechaInicio from venta where venta.Matricula='"+matricula+"' and venta.FechaInicio =Curdate()"));
    Venta.exec();
    if(Venta.next())
    {
        return true;
    }else
    {
        return false;
    }
}

bool baseDatos::Reservacion(QString fechaInicioString, QString fechaFinString, int idEstacionamiento , int idSocio)
{
    QDate fechaInicio, fechaFin;
    fechaInicio.setDate(2020,9,26);

    //QString fechaInicioString;
    /*QString*/ fechaInicioString= fechaInicio.toString("yyyy/MM/dd");
    //QString fechaFinString;
     fechaFin.setDate(2020,9,26);
    /*QString*/ fechaFinString=fechaFin.toString("yyyy/MM/dd");
    //int idEstacionamiento=5, idSocio=100003;


    QSqlQuery Reservacion(mDatabase);
    Reservacion.prepare("Insert into reservación (Inicio,Final,IdEstacionamiento_Socio,IdSocio) values ('"+fechaInicioString+"','"+fechaFinString+"','"+QString::number(idEstacionamiento)+"','"+QString::number(idSocio)+"')");
    Reservacion.exec();
    qDebug()<<"AQUI VA LA FECHA"+fechaInicioString;
    qDebug()<<"AQUI VA LA FECHA"+fechaFinString;
    //if(Reservacion.exec("Insert into reservación (Inicio,Final,IdEstacionamiento_Socio,IdSocio) values ('"+fechaInicioString+"','"+fechaFinString+"','"+idEstacionamiento+"','"+idSocio+"')"))
    if(Reservacion.next())
    {
        return false;
            qDebug()<<"Reservacion exitosa";
    }else
    {
        return true;
    }

}

bool baseDatos::EntradaCliente(QString Estatus)//,int id)
{
   QSqlQuery Entrada(mDatabase);
   Entrada.prepare("Update estacionamiento_cliente Set Estatus='"+Estatus+"' where estacionamiento_cliente.idEstacionamiento_Cliente=1");
   if(Entrada.exec())
   {
       return true;
   }else
   {
       return false;
   }
}
bool baseDatos::VerVentasSemanales()
{
    QSqlQuery Ventas(mDatabase);
    //Ventas.prepare("SELECT * FROM venta WHERE venta.FechaInicio > DATE_SUB(NOW(), INTERVAL 1 WEEK)");
    if(Ventas.exec("SELECT * FROM venta WHERE venta.FechaInicio > DATE_SUB(NOW(), INTERVAL 1 WEEK)"))
    {
        return true;
        //qDebug()<<"SELECT * FROM venta WHERE venta.FechaInicio > DATE_SUB(NOW(), INTERVAL 1 WEEK)";
    }else
    {
        return false;
    }
}
