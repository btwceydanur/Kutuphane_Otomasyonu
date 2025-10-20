#include "uye_islemleri.h"
#include "ui_uye_islemleri.h"

uye_islemleri::uye_islemleri(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uye_islemleri)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QDialog {"
        "background-image: url(:/resimler/images/arkaplan2.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-origin: content;"
        "background-attachment: fixed;"
        "background-size: cover;"
        "}"
        );

    sorgu=new QSqlQuery(db);
    listele();

}

uye_islemleri::~uye_islemleri()
{
    delete ui;
}

void uye_islemleri::listele()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye tablosu açılırken bir hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->uye_tw->setModel(model);
}

void uye_islemleri::on_uye_tw_clicked(const QModelIndex &index)
{
    ui->no_ln->setText(model->index(index.row(),0).data().toString());
    ui->ad_ln->setText(model->index(index.row(),1).data().toString());
    ui->soyad_ln->setText(model->index(index.row(),2).data().toString());
}


void uye_islemleri::on_kayit_btn_clicked()
{
    sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
    if(ui->ad_ln->text()=="" || ui->soyad_ln->text()=="")
    {
        QMessageBox::critical(this,"Hata!","Lütfen boş alan bırakmayınız!");
        return;
    }
    sorgu->addBindValue(ui->ad_ln->text());
    sorgu->addBindValue(ui->soyad_ln->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye tablosuna ekleme yapılırken bir hata oluştu!");
        return;
    }
    listele();
}


void uye_islemleri::on_guncelle_btn_clicked()
{
    sorgu->prepare("update uye set uye_ad=?,uye_soyad=? where uye_no=?");
    sorgu->addBindValue(ui->ad_ln->text());
    sorgu->addBindValue(ui->soyad_ln->text());
    sorgu->addBindValue(ui->no_ln->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye tablosunda güncelleme yapılırken bir hata oluştu!");
        return;
    }
    listele();
}


void uye_islemleri::on_sil_btn_clicked()
{
    sorgu->prepare("select * from odunc_alinan where uye_no=?");
    sorgu->addBindValue(ui->no_ln->text().toInt());
    sorgu->exec();
    int sayac=0;
    while(sorgu->next())
    {
        sayac++;
    }
    if(sayac>0)
    {
        QMessageBox::critical(this,"Hata","Bu üyenin teslim etmediği kitap olduğu için üye silinemez");
        return;
    }
    else
    {
        sorgu->prepare("delete from uye where uye_no=?");
        sorgu->addBindValue(ui->no_ln->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Üye tablosundan silme yapılırken bir hata oluştu!");
            return;
        }
        listele();
    }

}

