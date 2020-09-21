#ifndef CUETAS_OPERADOR_H
#define CUETAS_OPERADOR_H
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

namespace Ui {
class cuetas_operador;
}

class cuetas_operador : public QDialog
{
    Q_OBJECT

public:
    explicit cuetas_operador(QWidget *parent = nullptr);
    ~cuetas_operador();

private slots:

    void on_Regresar_clicked();

    void on_Opcion_currentTextChanged(const QString &arg1);

private:
    Ui::cuetas_operador *ui;
     QSqlDatabase mdb;
};


#endif // CUETAS_OPERADOR_H
