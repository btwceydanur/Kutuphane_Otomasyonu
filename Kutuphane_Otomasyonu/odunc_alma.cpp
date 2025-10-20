#include "odunc_alma.h"
#include "ui_odunc_alma.h"

odunc_alma::odunc_alma(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::odunc_alma)
{
    ui->setupUi(this);

    this->setStyleSheet("QDialog {"
                        "background-image: url(:/resimler/images/arkaplan4.png);"
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "background-origin: content;"
                        "background-attachment: fixed;"
                        "background-size: cover;"
                        "}");

    sorgu=new QSqlQuery(db);
    listele();

}

odunc_alma::~odunc_alma()
{
    delete ui;
}

void odunc_alma::listele()
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

    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Kitaplar listelenirken hata oluştu!");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->kitaplar_tw->setModel(model2);

    sorgu->prepare("select * from uye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Üyeler listelenirken hata oluştu!");
        return;
    }
    model3=new QSqlQueryModel();
    model3->setQuery(*sorgu);
    ui->uyeler_tw->setModel(model3);
}

void odunc_alma::on_uyeler_tw_clicked(const QModelIndex &index)
{
    ui->uye_no->setText(model3->index(index.row(),0).data().toString());
}


void odunc_alma::on_kitaplar_tw_clicked(const QModelIndex &index)
{
    ui->kitap_no->setText(model2->index(index.row(),0).data().toString());
}


void odunc_alma::on_odunc_al_clicked()
{
    if(ui->kitap_no->text()==""|| ui->uye_no->text()=="")
    {
        QMessageBox::critical(this,"Hata","Lütfen bir üye ve kitap seçin");
        return;
    }
    sorgu->prepare("select * from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->uye_no->text());
    sorgu->addBindValue(ui->kitap_no->text());
    if(ui->kitap_no->text()=="" || ui->uye_no->text()=="")
    {
        QMessageBox::critical(this,"Hata","Lütfen üye ve kitap seçiniz!");
        return;
    }
    sorgu->exec();
    int sayac=0;
    while(sorgu->next())
    {
        sayac++;
    }
    if(sayac>0)
    {
        QMessageBox::information(this,"Hata","Bu üye bu kitabın bir tanesini şuan ödünç almış bu yüzden tekrar ödünç verilemez!");
        return;
    }

    sorgu->prepare("select kitap_sayisi from kitap where kitap_no=?");
    sorgu->addBindValue(ui->kitap_no->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata","Kitaplar listesinden stok çekilemedi!");
        return;
    }
    if (!sorgu->next())
    {
        QMessageBox::critical(this, "Hata", "Kitap stoğu alınamadı!");
        return;
    }
    int toplam_stok = sorgu->value(0).toInt();

    sorgu->prepare("select count(*) from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->kitap_no->text());
    if (!sorgu->exec() || !sorgu->next())
    {
        QMessageBox::critical(this, "Hata", "Ödünç kitap sayısı alınamadı!");
        return;
    }
    int odunc_verilen = sorgu->value(0).toInt();

    if (odunc_verilen >= toplam_stok)
    {
        QMessageBox::warning(this, "Uyarı", "Bu kitap kütüphanede tükenmiştir, ödünç verilemez!");
        return;
    }
    sorgu->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
    sorgu->addBindValue(ui->uye_no->text());
    sorgu->addBindValue(ui->kitap_no->text());
    sorgu->addBindValue(ui->dateEdit->date().toString("dd.MM.yyyy"));
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç alınanlar listesine eklenirken hata oluştu!");
        return;
    }
    listele();
}

