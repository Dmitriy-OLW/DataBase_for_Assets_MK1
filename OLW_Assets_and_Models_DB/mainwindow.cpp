#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableView,
            SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(CustomMenuReq(QPoint)));
    fl = 0; //установка начального значения
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    //вызов Form_DB при нажатии на "Подключится"
    dlg = new Form_DB();
    dlg->show();


}


void MainWindow::on_pushButton_clicked()
{
    fl = 1;

    //Второй способ вывода  таблицы с возможность изменять её
    qmodel = new QSqlQueryModel();
    //qmodel->setQuery("SELECT * FROM Assets a inner join category b on a.catID = b.ID");
    qmodel->setQuery("SELECT * FROM Assets a inner join category b on a.catID = b.ID");
    ui->tableView->setModel(qmodel);

    //Первый способ вывода только одной таблицы с возможность изменять её
//    tmodel = new QSqlTableModel();
//    tmodel->setTable("Assets");
//    tmodel->select();
//    ui->tableView->setModel(tmodel);
}


void MainWindow::on_pushButton_2_clicked()
{
    Adlg = new AddDialog();
    Adlg->show();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_ID;
    ui->comboBox->clear();
    temp_ID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt(); //в одну строку
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, catID, ImagePath, Date FROM Assets WHERE ID = :ID");
    query->bindValue(":ID",temp_ID);
    ui->lineEdit->setText(QString::number(temp_ID));
    if (query->exec())
    {
        query->next();
        ui->lineEdit_2->setText(query->value(0).toString());
        //ui->lineEdit_3->setText(query->value(1).toString());
        QSqlQuery *queryCombo = new QSqlQuery();
            queryCombo->exec("SELECT name FROM category");
            while (queryCombo->next())
            {
                ui->comboBox->addItem(queryCombo->value(0).toString());
            }
        ui->comboBox->setCurrentIndex((query->value(1).toInt())-1);
        Img = query->value(2).toString();
        ui->label_4->setPixmap(Img);
        ui->label_4->setScaledContents(true); //выравнивание размера фото по доступной области для размещения
        //ui->label_4->setPixmap(QPixmap(query->value(1).toString()));
        ui->dateEdit->setDate(QDate(query->value(3).toDate()));

    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM Assets WHERE ID = :ID");
    query->bindValue(":ID",ui->lineEdit->text());
    query->exec();
    //очищаем поля ввода
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    //ui->lineEdit_3->setText("");
    //вызов обраотчика кнопки «Обновить»
    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_pushButton_3_clicked()
{
    /*
    QSqlQuery *query = new QSqlQuery();
        query->prepare("UPDATE Assets SET name = :name, Categoty_id = :Categoty_id, ImagePath = :image WHERE ID = :ID");
    mdf = new ModifyDialog();
    mdf->show();
    MainWindow::on_pushButton_clicked();*/
    /*
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE Assets SET name = :name, "
    "Categoty_id = :Categoty_id, ImagePath = :image WHERE ID = :ID");
    query->bindValue(":ID",ui->lineEdit->text());
    query->bindValue(":name",ui->lineEdit_2->text());
    query->bindValue(":Categoty_id",ui->lineEdit_3->text());
    query->bindValue(":image",Img);
    query->bindValue(":Date", ui->dateEdit->text());

    query->exec();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->label_4->setText("");
    MainWindow::on_pushButton_clicked();*/
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE Assets SET name = :name, "
    "catID = :catID, ImagePath = :ImagePath, Date = :Date WHERE ID = :ID");
    query->bindValue(":ID",ui->lineEdit->text());
    query->bindValue(":name",ui->lineEdit_2->text());

    query->bindValue(":catID",(ui->comboBox->currentIndex())+1);
    query->bindValue(":ImagePath",Img);
    query->bindValue(":Date", ui->dateEdit->text());

    query->exec();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    //ui->lineEdit_3->setText("");

    ui->comboBox->clear();
    ui->label_4->setText("");
    MainWindow::on_pushButton_clicked();

}


void MainWindow::CustomMenuReq(QPoint pos)
{
 if (fl == 1)
 {
    QModelIndex index = ui->tableView->indexAt(pos);
    GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    QMenu *menu = new QMenu(this);
    QAction *ModRec = new QAction("Изменить...", this);
    QAction *DelRec = new QAction("Удалить", this);

    connect(ModRec, SIGNAL(triggered()), this, SLOT(ModRecAction()));
    connect(DelRec, SIGNAL(triggered()), this, SLOT(DelRecAction()));

    menu->addAction(ModRec);
    menu->addAction(DelRec);
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
 }
}

void MainWindow::DelRecAction()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM Assets WHERE ID = :ID");
    query->bindValue(":ID",GlobID);
    query->exec();
    MainWindow::on_pushButton_clicked();
}

void MainWindow::ModRecAction()
{
    mdf = new ModifyDialog();
    connect(this,SIGNAL(sendID(int)),mdf, SLOT(sendingID(int)));
    connect(mdf, SIGNAL(refresh_table()), this, SLOT(obr_ref_tab()));
    emit sendID(GlobID);
    mdf->show();
    disconnect(this,SIGNAL(sendID(int)),mdf,
    SLOT(sendingID(int)));
}



void MainWindow::on_pushButton_5_clicked()
{
    pdlg = new PrintDialog();
    pdlg->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    QString str;
    str.append("<html><head></head><body><center>"
    +QString("Пример создания отчёта"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("ID")+"</td>");
    str.append("<td>"+QString("Наименование")+"</td>");
    str.append("<td>"+QString("Категория")+"</td></tr>");
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM Assets");
    query->next();
    while(query->next())
    {
    str.append("<tr>");
    str.append("<td>"
    +QString(query->value(0).toString())+"</td>");
    str.append("<td>"
    +QString(query->value(1).toString())+"</td>");
    str.append("<td>"
    +QString(query->value(2).toString())
    +"</td></tr>");
    }
    str.append("</table>");
    str.append("</center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path =
    QFileDialog::getSaveFileName(NULL,"Сохранить",
    "Отчёт","PDF(*.pdf)");
    if (path.isEmpty()) return;
    printer.setOutputFileName(path);
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}


void MainWindow::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img,"*.png");
    ui->label_4->setPixmap(Img);
}


void MainWindow::on_action_2_triggered()
{
    pg = new printGraf();
    pg->show();
}





void MainWindow::on_toolButton_triggered(QAction *arg1)
{

}

