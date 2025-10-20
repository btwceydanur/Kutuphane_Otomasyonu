#ifndef ODUNC_ALMA_H
#define ODUNC_ALMA_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class odunc_alma;
}

class odunc_alma : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_alma(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_alma();
    void listele();

private slots:
    void on_uyeler_tw_clicked(const QModelIndex &index);

    void on_kitaplar_tw_clicked(const QModelIndex &index);

    void on_odunc_al_clicked();

private:
    Ui::odunc_alma *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;
};

#endif // ODUNC_ALMA_H
