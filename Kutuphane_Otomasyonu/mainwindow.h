#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <uye_islemleri.h>
#include <kitap.h>
#include <odunc_alma.h>
#include <odunc_teslim.h>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QScreen>
#include <QGuiApplication>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void golge_ekle(QPushButton* btn);

private slots:
    void on_uye_btn_clicked();

    void on_kitap_btn_clicked();

    void on_al_btn_clicked();

    void on_teslim_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlTableModel *model1;
};
#endif // MAINWINDOW_H
