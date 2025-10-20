#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setStyleSheet("QMainWindow {"
                        "background-image: url(:/resimler/images/arkaplan1.png);"
                        "}");

    ui->uye_btn->setIcon(QIcon(":/resimler/images/user.png"));
    ui->uye_btn->setIconSize(ui->uye_btn->size());

    ui->kitap_btn->setIcon(QIcon(":/resimler/images/kitap.png"));
    ui->kitap_btn->setIconSize(ui->kitap_btn->size());

    ui->al_btn->setIcon(QIcon(":/resimler/images/odunc2.png"));
    ui->al_btn->setIconSize(ui->al_btn->size());

    ui->teslim_btn->setIcon(QIcon(":/resimler/images/odunc1.png"));
    ui->teslim_btn->setIconSize(ui->teslim_btn->size());

    golge_ekle(ui->uye_btn);
    golge_ekle(ui->kitap_btn);
    golge_ekle(ui->al_btn);
    golge_ekle(ui->teslim_btn);


    //***
    //Ben db yi build içine koyunca çalışmadı bu sebeple direk yolu yazdım
    //***
    db.setDatabaseName("C:/Users/Ceydanur/Desktop/Kutuphane_Otomasyonu/kutuphane.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("Veri Tabanına bağlanılamadı!");
    }
    else
    {
        ui->statusbar->showMessage("Veri Tabanına bağlandı");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::golge_ekle(QPushButton* btn)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(20);
    effect->setOffset(0, 0);
    effect->setColor(QColor(0, 255, 255));
    btn->setGraphicsEffect(effect);
}

void MainWindow::on_uye_btn_clicked()
{
    uye_islemleri *uye = new uye_islemleri(db, this);
    QSize pencereBoyutu = uye->size();
    QRect ekranGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (ekranGeometry.width() - pencereBoyutu.width()) / 2;
    int y = (ekranGeometry.height() - pencereBoyutu.height()) / 2;

    QRect finalGeometry(x, y, pencereBoyutu.width(), pencereBoyutu.height());

    QRect startGeometry = finalGeometry;
    startGeometry.moveLeft(ekranGeometry.left() - pencereBoyutu.width() - 50);

    uye->setGeometry(startGeometry);
    uye->show();

    QPropertyAnimation *animation = new QPropertyAnimation(uye, "geometry");
    animation->setDuration(500);
    animation->setStartValue(startGeometry);
    animation->setEndValue(finalGeometry);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::on_kitap_btn_clicked()
{
    kitap *kitaplar = new kitap(db, this);
    QSize pencereBoyutu = kitaplar->size();
    QRect ekranGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (ekranGeometry.width() - pencereBoyutu.width()) / 2;
    int y = (ekranGeometry.height() - pencereBoyutu.height()) / 2;

    QRect finalGeometry(x, y, pencereBoyutu.width(), pencereBoyutu.height());
    QRect startGeometry = finalGeometry;
    startGeometry.moveTop(ekranGeometry.bottom() + 50);


    kitaplar->setGeometry(startGeometry);
    kitaplar->show();

    QPropertyAnimation *animation = new QPropertyAnimation(kitaplar, "geometry");
    animation->setDuration(500);
    animation->setStartValue(startGeometry);
    animation->setEndValue(finalGeometry);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::on_al_btn_clicked()
{
    odunc_alma *odunc_al = new odunc_alma(db, this);
    QSize pencereBoyutu = odunc_al->size();
    QRect ekranGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (ekranGeometry.width() - pencereBoyutu.width()) / 2;
    int y = (ekranGeometry.height() - pencereBoyutu.height()) / 2;

    QRect finalGeometry(x, y, pencereBoyutu.width(), pencereBoyutu.height());
    QRect startGeometry = finalGeometry;
    startGeometry.moveLeft(ekranGeometry.right() + 50);

    odunc_al->setGeometry(startGeometry);
    odunc_al->show();

    QPropertyAnimation *animation = new QPropertyAnimation(odunc_al, "geometry");
    animation->setDuration(500);
    animation->setStartValue(startGeometry);
    animation->setEndValue(finalGeometry);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::on_teslim_btn_clicked()
{
    odunc_teslim *teslim = new odunc_teslim(db, this);
    QSize pencereBoyutu = teslim->size();
    QRect ekranGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (ekranGeometry.width() - pencereBoyutu.width()) / 2;
    int y = (ekranGeometry.height() - pencereBoyutu.height()) / 2;

    QRect finalGeometry(x, y, pencereBoyutu.width(), pencereBoyutu.height());
    QRect startGeometry = finalGeometry;
    startGeometry.moveTop(ekranGeometry.top() - pencereBoyutu.height() - 50);

    teslim->setGeometry(startGeometry);
    teslim->show();

    QPropertyAnimation *animation = new QPropertyAnimation(teslim, "geometry");
    animation->setDuration(500);
    animation->setStartValue(startGeometry);
    animation->setEndValue(finalGeometry);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

