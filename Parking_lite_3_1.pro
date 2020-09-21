QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acceso_cliente.cpp \
    accesos_socio.cpp \
    actualizar_tarifa.cpp \
    admin.cpp \
    cobrar_estacionamiento.cpp \
    cuentas.cpp \
    eliminarcuentas.cpp \
    estatus_estacionamiento.cpp \
    inicio_de_sesion.cpp \
    main.cpp \
    modificardatos.cpp \
    operador.cpp \
    registro_cliente.cpp \
    registro_operador.cpp \
    socio.cpp \
    socio_cliente.cpp \
    tramitar_membresia.cpp \
    ventas_diarias.cpp

HEADERS += \
    acceso_cliente.h \
    accesos_socio.h \
    actualizar_tarifa.h \
    admin.h \
    cobrar_estacionamiento.h \
    cuentas.h \
    eliminarcuentas.h \
    estatus_estacionamiento.h \
    inicio_de_sesion.h \
    modificardatos.h \
    operador.h \
    registro_cliente.h \
    registro_operador.h \
    socio.h \
    socio_cliente.h \
    tramitar_membresia.h \
    ventas_diarias.h

FORMS += \
    acceso_cliente.ui \
    accesos_socio.ui \
    actualizar_tarifa.ui \
    admin.ui \
    cobrar_estacionamiento.ui \
    cuentas.ui \
    eliminarcuentas.ui \
    estatus_estacionamiento.ui \
    inicio_de_sesion.ui \
    modificardatos.ui \
    operador.ui \
    registro_cliente.ui \
    registro_operador.ui \
    socio.ui \
    socio_cliente.ui \
    tramitar_membresia.ui \
    ventas_diarias.ui

RC_ICONS = Icon.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes.qrc
