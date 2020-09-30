#include "basededatos.h"
#include <QtTest>
#include<QDateTime>
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

/*-----Iteración 4-----*/
void baseDatos::EliminarOperador(int idOp){
     QSqlQuery borrarOp(mDatabase),usOp(mDatabase);

     QString idRe= QString::number(idOp);

         usOp.prepare("select IdOperador from operador inner join usuario where IdOperador='"+idRe+"'");
         usOp.exec();
         if(usOp.next())
         {
             QVERIFY(borrarOp.exec("delete from usuario where idUsuario="+idRe));
         }else
         {
             qDebug() << "El operador no se encontro";
         }
}
void baseDatos::EliminarSocio(int idSo){
     QSqlQuery borrarSo(mDatabase),usSo(mDatabase);

     QString idRe= QString::number(idSo);

         usSo.prepare("select IdSocio from socio inner join usuario where IdSocio='"+idRe+"'");
         usSo.exec();
         if(usSo.next())
         {

             QVERIFY(borrarSo.exec("delete from usuario where idUsuario="+idRe));
             qDebug() << "El cliente fue eliminado exitosamente!!";
         }else
         {
             qDebug() << "El cliente no se encontro";
         }
}

void baseDatos::ActualizarSocio(int id,QString contraseniaN,QString telefonoN,QString correoN,QString numtarjetaN,QString titularN,QString matriculaN){
    QSqlQuery actuSocio(mDatabase);

    QString idS=QString::number(id);

   if(contraseniaN!="")
    {
        actuSocio.clear();
        QVERIFY(actuSocio.prepare("Update usuario set Contraseña ='"+contraseniaN+"' where idUsuario='"+idS+"'"));
        actuSocio.exec();
        actuSocio.next();
        qDebug()<<"Contraseña modificada!!";
    }
   if(telefonoN!="")
   {
       actuSocio.clear();
       QVERIFY(actuSocio.prepare("Update usuario set Telefono ='"+telefonoN+"' where idUsuario='"+idS+"'"));
       actuSocio.exec();
       actuSocio.next();
       qDebug()<<"Telefono modificado!!";
   }
   if(correoN!="")
   {
      actuSocio.clear();
      QVERIFY( actuSocio.prepare("Update Socio set Correo ='"+correoN+"' where IdSocio='"+idS+"'"));
       actuSocio.exec();
       actuSocio.next();
       qDebug()<<"Correo modificado!!";
   }
   if(numtarjetaN!="")
   {
       actuSocio.clear();
       QVERIFY(actuSocio.prepare("Update Socio set NumTarjeta ='"+numtarjetaN+"' where IdSocio='"+idS+"'"));
       actuSocio.exec();
       actuSocio.next();
       qDebug()<<"Numero de tarjeta modificada!!";
   }
   if(titularN!="")
   {
       actuSocio.clear();
       QVERIFY(actuSocio.prepare("Update Socio set TitularTarjeta ='"+titularN+"' where IdSocio='"+idS+"'"));
       actuSocio.exec();
       actuSocio.next();
       qDebug()<<"Titular de la tarjeta modificada!!";
   }
   if(matriculaN!="")
   {

      actuSocio.clear();
      actuSocio.prepare("Delete from matricula_registrada where IdSocio='"+idS+"'");
      actuSocio.exec();
      actuSocio.next();
      actuSocio.clear();
      actuSocio.prepare("Select Matricula from vehiculo where Matricula='"+matriculaN+"'");
      actuSocio.exec();
      if(actuSocio.next()){
         actuSocio.clear();
         actuSocio.prepare("Insert Into Matricula_Registrada (IdSocio,Matricula) values('"+idS+"','"+matriculaN+"')");
         actuSocio.exec();
         actuSocio.next();
        }
         else{
              actuSocio.clear();
              actuSocio.prepare("Insert Into Vehiculo(Matricula) values('"+matriculaN+"')");
              actuSocio.exec();
              actuSocio.next();
              actuSocio.clear();
              QVERIFY(actuSocio.prepare("Insert Into Matricula_Registrada (IdSocio,Matricula) values('"+idS+"','"+matriculaN+"')"));
              actuSocio.exec();
              actuSocio.next();
              qDebug()<<"Matricula modificada!!";
             }
   }
}
