#include "printdialog.h"
#include "ui_printdialog.h"

PrintDialog::PrintDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintDialog)
{
    ui->setupUi(this);
}

PrintDialog::~PrintDialog()
{
    delete ui;
}

void PrintDialog::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(0,"Выберете файл",".\\","*.html"));
}


void PrintDialog::on_pushButton_clicked()
{

        QFile *file = new QFile();
        file->setFileName(ui->lineEdit->text());
        file->open(QIODevice::WriteOnly);
        QTextStream in(file);
        in << "<html><head></head><body><center>"
        +QString("Пример создания отчёта");
        in << "<table border=1><tr>";
        in << "<td>"+QString("ID")+"</td>";
        in << "<td>"+QString("Наименование")+"</td>";
        in << "<td>"+QString("Категория")+"</td></tr>";
        QSqlQuery *query = new QSqlQuery();
        query->exec("SELECT * FROM Assets");
        query->next();
        while (query->next())
        {
         in << "<tr>";
         in << "<td>"+QString(query->value(0).toString())+"</td>";
         in << "<td>"+QString(query->value(1).toString())+"</td>";
         in << "<td>"+QString(query->value(2).toString())+"</td>";
         in << "</tr>";
        }
        in << "</table>";
        in << "</center></body></html>";
        file->close();
        QAxObject *word = new QAxObject("Word.Application",this);
        word->setProperty("DisplayAlerts",false);
        word->setProperty("Visible", true);
        QAxObject *doc = word->querySubObject("Documents");
        doc->dynamicCall("Open(QVariant)", ui->lineEdit->text());


    /*
    QFile *file = new QFile();
    file->setFileName(ui->lineEdit->text());
    file->open(QIODevice::WriteOnly);
    QTextStream in(file);
    in << "<html><head></head><body><center>"
    +QString("Пример создания отчёта");
    in << "<table border=1><tr>";
    in << "<td>"+QString("ID")+"</td>";
    in << "<td>"+QString("Наименование")+"</td>";
    in << "<td>"+QString("Категория")+"</td></tr>";
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM Assets");
    query->next();
    while (query->next())
    {
    in << "<tr>";
    in << "<td>"+QString(query->value(0).toString())+"</td>";
    in << "<td>"+QString(query->value(1).toString())+"</td>";
    in << "<td>"+QString(query->value(2).toString())+"</td>";
    in << "</tr>";
    }
    in << "</table>";
    in << "</center></body></html>";

    file->close();
    QAxObject *word = new QAxObject("Word.Application",this);
    word->setProperty("DisplayAlerts",false);
    word->setProperty("Visible", true);
    QAxObject *doc = word->querySubObject("Documents");
    doc->dynamicCall("Open(QVariant)", "C:\\QT_projects\\new.html");*/
}

