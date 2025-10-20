#ifndef ODUNC_TESLIM_H
#define ODUNC_TESLIM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class odunc_teslim;
}

class odunc_teslim : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_teslim();

    void listele();

private slots:
    void on_odunc_tw_clicked(const QModelIndex &index);

    void on_odunc_ver_clicked();

private:
    Ui::odunc_teslim *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
};

#endif // ODUNC_TESLIM_H
