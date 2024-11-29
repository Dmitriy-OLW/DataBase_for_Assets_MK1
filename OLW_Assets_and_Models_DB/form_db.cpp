#include "form_db.h"
#include "ui_form_db.h"

Form_DB::Form_DB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_DB)
{
    ui->setupUi(this);
}

Form_DB::~Form_DB()
{
    delete ui;
}

void Form_DB::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_2->text()+";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    //Подключение к БД

    msg = new QMessageBox(); //Создание диалогового окна

    if(db.open()){
        msg->setText("Соединение установленно");
    }
    else{
        msg->setText("Соединение НЕ установленно");
    }
    msg->show();
}

