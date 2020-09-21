#ifndef RESERVACION_H
#define RESERVACION_H

#include <QDialog>

namespace Ui {
class Reservacion;
}

class Reservacion : public QDialog
{
    Q_OBJECT

public:
    explicit Reservacion(QWidget *parent = nullptr);
    ~Reservacion();

private:
    Ui::Reservacion *ui;
};

#endif // RESERVACION_H
