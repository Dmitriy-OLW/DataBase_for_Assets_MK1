#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>

#include <QFileDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

    QString Img;

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
