#include "odunc_teslim.h"
#include "ui_odunc_teslim.h"

odunc_teslim::odunc_teslim(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::odunc_teslim)
{
    ui->setupUi(this);

    this->setStyleSheet("QDialog {"
                        "background-image: url(:/resimler/images/arkaplan5.png);"
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "background-origin: content;"
                        "background-attachment: fixed;"
                        "background-size: cover;"
                        "}");

    sorgu=new QSqlQuery(db);
    listele();

}

odunc_teslim::~odunc_teslim()
{
    delete ui;
}

void odunc_teslim::listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Ödünç alınanlar listelenirken hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->odunc_tw->setModel(model);

    sorgu->prepare("select * from odunc_teslim_edilen");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Ödünç teslim edilenler listelenirken hata oluştu!");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->teslim_tw->setModel(model2);
}

void odunc_teslim::on_odunc_tw_clicked(const QModelIndex &index)
{
    ui->uye_no->setText(model->index(index.row(),0).data().toString());
    ui->kitap_no->setText(model->index(index.row(),1).data().toString());
}


void odunc_teslim::on_odunc_ver_clicked()
{
    sorgu->prepare("select odunc_alma_tarihi from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->uye_no->text());
    sorgu->addBindValue(ui->kitap_no->text());
    if (!sorgu->exec() || !sorgu->next()) {
        QMessageBox::critical(this, "Hata", "Ödünç alma tarihi alınamadı.");
        return;
    }
    QDate alis_tarihi = QDate::fromString(sorgu->value(0).toString(), "dd.MM.yyyy");
    int fark = alis_tarihi.daysTo(ui->dateEdit->date());
    int borc;
    if(fark<=15)
    {
        borc=0;
    }
    else
    {
        borc=fark*4-15*4;
    }
    if(ui->dateEdit->date() < alis_tarihi)
    {
        QMessageBox::critical(this,"Hata","Alış Tarihinden önceki bir tarihi giremezsiniz!");
        return;
    }
    sorgu->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
    sorgu->addBindValue(ui->uye_no->text());
    sorgu->addBindValue(ui->kitap_no->text());
    sorgu->addBindValue(alis_tarihi.toString("dd.MM.yyyy"));
    sorgu->addBindValue(ui->dateEdit->date().toString("dd.MM.yyyy"));
    sorgu->addBindValue(borc);
    if (!sorgu->exec()) {
        QMessageBox::critical(this, "Hata", "Teslim edilenler listesine eklenemedi.");
        return;
    }
    sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->uye_no->text());
    sorgu->addBindValue(ui->kitap_no->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç alınanlar listelenirken bir hata oluştu!");
        return;
    }
    listele();
}

