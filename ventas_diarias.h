#ifndef VENTAS_DIARIAS_H
#define VENTAS_DIARIAS_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDialog>

namespace Ui {
class Ventas_Diarias;
}

class Ventas_Diarias : public QDialog
{
    Q_OBJECT

public:
    explicit Ventas_Diarias(QWidget *parent = nullptr);
    ~Ventas_Diarias();

private slots:
    void on_Calendario_clicked(const QDate &date);

    void on_pushButton_clicked();

private:
    Ui::Ventas_Diarias *ui;
    QSqlDatabase mdb1;
};

#endif // VENTAS_DIARIAS_H
