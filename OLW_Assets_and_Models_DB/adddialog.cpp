#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery> //Подключение библиотеки
#include <QMessageBox> //Подключение библиотеки

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
        queryCombo->exec("SELECT name FROM category");
        while (queryCombo->next())
        {
            ui->comboBox->addItem(queryCombo->value(0).toString());
        }
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO Assets (name, catID, ImagePath, Date) VALUES(:name,:catID, :ImagePath, :Date )");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":catID",(ui->comboBox->currentIndex())+1);
    query->bindValue(":ImagePath",Img);
    query->bindValue(":Date", ui->dateEdit->text());
    //query->bindValue(":catID", ui->
    //query->bindValue(":catID",(ui->comboBox->currentText()));
    //query->bindValue(":Categoty_id", (ui->comboBox->currentIndex())+1);

    QMessageBox *mess= new QMessageBox();
    if(!query->exec())
    {
    mess->setText("Запрос составлен неверно!");
    mess->show(); }
    else{
         close(); //закрытие диалогового окна
    }

    //query->exec();

}


void AddDialog::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img,"*.png");
    ui->label_3->setPixmap(Img);

}

