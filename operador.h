#ifndef OPERADOR_H
#define OPERADOR_H

#include <QDialog>

namespace Ui {
class operador;
}

class operador : public QDialog
{
    Q_OBJECT

public:
    explicit operador(QString IdOperador,QWidget *parent = nullptr);
    ~operador();

private slots:
    void on_CerrarSesion_clicked();

    void on_RegistrodeVentas_clicked();

    void on_Cobrar_clicked();

private:
    Ui::operador *ui;
    QString IdOperador;
};

#endif // OPERADOR_H
