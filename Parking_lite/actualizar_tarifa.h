#ifndef ACTUALIZAR_TARIFA_H
#define ACTUALIZAR_TARIFA_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Actualizar_Tarifa;
}

class Actualizar_Tarifa : public QDialog
{
    Q_OBJECT

public:
    explicit Actualizar_Tarifa(QWidget *parent = nullptr);
    ~Actualizar_Tarifa();

private slots:
    void on_ComboBox_activated(const QString &arg1);

    void on_comTarifa_currentTextChanged(const QString &arg1);

    void on_Guardar_clicked();

    void on_Cancelar_clicked();

private:
    Ui::Actualizar_Tarifa *ui;
        QSqlDatabase mdb1;
};

#endif // ACTUALIZAR_TARIFA_H
