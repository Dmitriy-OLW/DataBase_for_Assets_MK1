#ifndef PRINTGRAF_H
#define PRINTGRAF_H

#include <QWidget>
#include <QSqlQuery>
#include <QAxObject>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

namespace Ui {
class printGraf;
}

class printGraf : public QWidget
{
    Q_OBJECT

public:
    explicit printGraf(QWidget *parent = nullptr);
    ~printGraf();

private slots:
    void on_pushButton_clicked();

private:
    Ui::printGraf *ui;
};

#endif // PRINTGRAF_H
