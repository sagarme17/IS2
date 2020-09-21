#ifndef ELIMINARCUENTAS_H
#define ELIMINARCUENTAS_H

#include <QDialog>

namespace Ui {
class EliminarCuentas;
}

class EliminarCuentas : public QDialog
{
    Q_OBJECT

public:
    explicit EliminarCuentas(QWidget *parent = nullptr);
    ~EliminarCuentas();

private:
    Ui::EliminarCuentas *ui;
};

#endif // ELIMINARCUENTAS_H
