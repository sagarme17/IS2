#ifndef DAR_SALIDA_RESERVACION_H
#define DAR_SALIDA_RESERVACION_H

#include <QDialog>

namespace Ui {
class dar_salida_reservacion;
}

class dar_salida_reservacion : public QDialog
{
    Q_OBJECT

public:
    explicit dar_salida_reservacion(QWidget *parent = nullptr);
    ~dar_salida_reservacion();

private:
    Ui::dar_salida_reservacion *ui;
};

#endif // DAR_SALIDA_RESERVACION_H
