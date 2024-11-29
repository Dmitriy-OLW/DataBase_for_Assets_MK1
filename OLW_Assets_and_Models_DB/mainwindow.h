#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form_db.h" //Подключение файлов
#include "ui_form_db.h" //Подключение файлов
#include "adddialog.h" //Подключение файлов
#include "ui_adddialog.h" //Подключение файлов
//#include "QSqlTableModel" //Подключение библиотеки
#include <QSqlQueryModel> //Подключение библиотеки
#include "modifydialog.h" //Подключение файлов
#include "ui_modifydialog.h" //Подключение файлов

#include "printdialog.h"
#include "ui_printdialog.h"
#include <QAxObject>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>


#include "printgraf.h"
#include "ui_printgraf.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int GlobID;
    int fl;
    QString Img;


private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void CustomMenuReq(QPoint);//Кастомные методы

    void DelRecAction();//Кастомные методы

    void ModRecAction();//Кастомные методы

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_clicked();


    void on_action_2_triggered();

    void on_toolButton_triggered(QAction *arg1);

signals:
    void sendID(int);

private:
    Ui::MainWindow *ui;
    Form_DB *dlg; //создание переменной Form_DB
    AddDialog *Adlg; //создание переменной Form_DB
 //   QSqlTableModel *tmodel; //создание переменной QSqlTableModel
    QSqlQueryModel *qmodel; //создание переменной QSqlQueryModel
    ModifyDialog *mdf;
    PrintDialog *pdlg;
    printGraf *pg;


};
#endif // MAINWINDOW_H
