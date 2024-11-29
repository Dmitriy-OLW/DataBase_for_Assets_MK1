#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSqlQuery> //создание запросов
#include <QFileDialog> //диалоговое окно работы с файлами
#include <QFile> //работа с файлами
#include <QTextStream> //организация текстовых потоков
#include <QAxObject>


namespace Ui {
class PrintDialog;
}

class PrintDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PrintDialog(QWidget *parent = nullptr);
    ~PrintDialog();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::PrintDialog *ui;
};

#endif // PRINTDIALOG_H
