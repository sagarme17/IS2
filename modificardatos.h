#ifndef MODIFICARDATOS_H
#define MODIFICARDATOS_H

#include <QDialog>

namespace Ui {
class ModificarDatos;
}

class ModificarDatos : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarDatos(QWidget *parent = nullptr);
    ~ModificarDatos();

private:
    Ui::ModificarDatos *ui;
};

#endif // MODIFICARDATOS_H
