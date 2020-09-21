#ifndef TRAMITAR_MEMBRESIA_H
#define TRAMITAR_MEMBRESIA_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class tramitar_Membresia;
}

class tramitar_Membresia : public QDialog
{
    Q_OBJECT

public:
    explicit tramitar_Membresia(QString,QWidget *parent = nullptr);
    ~tramitar_Membresia();

private slots:
    void on_Cancelar_clicked();

    void on_Tramitar_clicked();

private:
    Ui::tramitar_Membresia *ui;
    QString IdSocio;
    QSqlDatabase mdb;
};

#endif // TRAMITAR_MEMBRESIA_H
