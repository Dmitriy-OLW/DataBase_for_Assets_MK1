#ifndef FORM_DB_H
#define FORM_DB_H

#include <QWidget>
#include <QtSql> //Подключение библиотеки
#include <QMessageBox> //Подключение библиотеки

namespace Ui {
class Form_DB;
}

class Form_DB : public QWidget
{
    Q_OBJECT

public:
    explicit Form_DB(QWidget *parent = nullptr);
    ~Form_DB();
    QMessageBox *msg; //создание переменной QMessageBox

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form_DB *ui;
    QSqlDatabase db; //создание переменной QSqlDatabase
};

#endif // FORM_DB_H
