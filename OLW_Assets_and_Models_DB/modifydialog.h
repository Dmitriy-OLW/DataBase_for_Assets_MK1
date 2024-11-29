#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QWidget>
#include <QSqlQuery>

#include <QFileDialog>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = nullptr);
    ~ModifyDialog();

    int tempID;
    QString Img;

private slots:
    void on_pushButton_clicked();
    void sendingID(int);

    void on_toolButton_clicked();

private:
    Ui::ModifyDialog *ui;
};

#endif // MODIFYDIALOG_H


