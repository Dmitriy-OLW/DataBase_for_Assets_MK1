#include "modifydialog.h"
#include "ui_modifydialog.h"
#include "mainwindow.cpp"


ModifyDialog::ModifyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
        queryCombo->exec("SELECT name FROM category");
        while (queryCombo->next())
        {
            ui->comboBox->addItem(queryCombo->value(0).toString());
        }
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{


        QSqlQuery *query = new QSqlQuery();
        query->prepare("UPDATE Assets SET name = :name, catID = :catID, ImagePath =:ImagePath, Date = :Date WHERE ID = :ID");
        query->bindValue(":ID", tempID);
        query->bindValue(":name",ui->lineEdit->text());
        query->bindValue(":catID",(ui->comboBox->currentIndex())+1);
        query->bindValue(":ImagePath",Img);
        query->bindValue(":Date", ui->dateEdit->text());
        //query->bindValue(":Categoty_id",ui->lineEdit_2->text());

        if(query->exec())
        {
        close();
        }



}

void ModifyDialog::sendingID(int aa)
{
    tempID = aa;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, catID, ImagePath, Date  FROM Assets WHERE ID = ?");
    query->bindValue(0,aa);
    if (query->exec())
    {
       query->next();
        ui->lineEdit->setText(query->value(0).toString());
        //ui->lineEdit_2->setText(query->value(1).toString());
        ui->comboBox->setCurrentIndex((query->value(1).toInt())-1);
        Img = query->value(2).toString();
        ui->label_3->setPixmap(Img);
        ui->label_3->setScaledContents(true);
        ui->dateEdit->setDate(QDate(query->value(3).toDate()));
    }

}




void ModifyDialog::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img,"*.png");
    ui->label_3->setPixmap(Img);

}

