#include "kitap.h"
#include "ui_kitap.h"

kitap::kitap(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::kitap)
{
    ui->setupUi(this);


    this->setStyleSheet(
        "QDialog {"
        "background-image: url(:/resimler/images/arkaplan3.png);"
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

kitap::~kitap()
{
    delete ui;
}

void kitap::listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitaplar listelenirken hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->kitap_tw->setModel(model);
}

void kitap::on_kitap_tw_clicked(const QModelIndex &index)
{
    ui->kitap_no->setText(model->index(index.row(),0).data().toString());
    ui->kitap_ad->setText(model->index(index.row(),1).data().toString());
    ui->stok->setText(model->index(index.row(),2).data().toString());

    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Odunc alınan listesinden bilgi alınırken hata oluştu!");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->suan_tw->setModel(model2);

    sorgu->prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu->addBindValue(ui->kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Odunc teslim edilen listesinden bilgi alınırken hata oluştu!");
        return;
    }
    model3=new QSqlQueryModel();
    model3->setQuery(*sorgu);
    ui->once_tw->setModel(model3);
}


void kitap::on_kayit_btn_clicked()
{
    QString stokText = ui->stok->text();
    if(ui->kitap_ad->text().isEmpty() || stokText.isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Lütfen boş alan bırakmayınız!");
        return;
    }
    bool ok;
    int stok = stokText.toInt(&ok);
    if(!ok || stok <= 0)
    {
        QMessageBox::critical(this, "Hata!", "Stok sayısı negatif ve karakter olamaz!");
        return;
    }
    sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
    sorgu->addBindValue(ui->kitap_ad->text());
    sorgu->addBindValue(stok);
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitaplar listesine eklenirken hata oluştu!");
        return;
    }
    listele();
}


void kitap::on_guncelle_btn_clicked()
{
    sorgu->prepare("update kitap set kitap_ad=?,kitap_sayisi=? where kitap_no=?");
    sorgu->addBindValue(ui->kitap_ad->text());
    sorgu->addBindValue(ui->stok->text());
    sorgu->addBindValue(ui->kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitap güncellenirken bir hata oluştu!");
        return;
    }
    listele();
}


void kitap::on_sil_btn_clicked()
{
    sorgu->prepare("select *from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->kitap_no->text().toInt());
    sorgu->exec();
    int sayac=0;
    while(sorgu->next())
    {
        sayac++;
    }
    if(sayac>0)
    {
        QMessageBox::critical(this,"Hata","Bu kitabı ödünç alan olduğu için silinemez!");
        return;
    }
    else
    {
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(ui->kitap_no->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Kitap güncellenirken bir hata oluştu!");
            return;
        }
        listele();
    }
}

