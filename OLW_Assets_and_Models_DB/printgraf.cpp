#include "printgraf.h"
#include "ui_printgraf.h"

printGraf::printGraf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printGraf)
{
    ui->setupUi(this);
    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0,0, new QCPTextElement(ui->widget,"График"));
    QVector <double> dx, dy;//для хранения координат точки
    double minX, minY, maxX, maxY; //для определения границ
    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;
    QSqlQuery *query = new QSqlQuery();
    if (query->exec("SELECT * FROM chart"))
    {
        while (query->next())
        {
            //Поиск максимального и минимального значения координат
            if (minX>=query->value(0).toDouble())
              minX = query->value(0).toDouble();
            if (minY>=query->value(1).toDouble())
              minY = query->value(1).toDouble();
            if (maxX<=query->value(0).toDouble())
              maxX = query->value(0).toDouble();
            if (maxY<=query->value(1).toDouble())
              maxY = query->value(1).toDouble();
            //Добавление координат в вектора
            dx << query->value(0).toDouble();
            dy << query->value(1).toDouble();
        }
        //Создание объекта с привязкой к осям виджета
        QCPBars *bar = new QCPBars(ui->widget->xAxis,
                                   ui->widget->yAxis);
        bar->setName("Значение");

    //Цвет заливки графика (R,G,B,Transparency)
    bar->setBrush(QColor(255,0,0,255));
    bar->setData(dx,dy); //координаты точек
    bar->setWidth(0.25); //толщина линий
    //Добавление подписей осей
    ui->widget->xAxis->setLabel("Месяц");
    ui->widget->yAxis->setLabel("Количество дней разработки");
    //Установка границ отображения графика
    ui->widget->xAxis->setRange(minX,maxX+0.20);
    ui->widget->yAxis->setRange(minY,maxY+1);
    //Запрет автоматического определения шага шкалы
    //ui->widget->xAxis->setTicks(false);
    //ui->widget->yAxis->setTicks(false);
    //Ручная установка шага
    ui->widget->xAxis->ticker()->setTickCount(12);
    ui->widget->yAxis->ticker()->setTickCount(31);

    }
}

printGraf::~printGraf()
{
    delete ui;
}

void printGraf::on_pushButton_clicked()
{
    /*QString fn = QFileDialog::getSaveFileName(0,"Соханить в PDF","./","*.pdf");
            if(!fn.isEmpty())
            {
                QPrinter print;
                print.setFullPage(true);
                print.setOrientation(QPrinter::Portrait);
                print.setOutputFormat(QPrinter::PdfFormat);
                print.setPaperSize(QPrinter::A4);
                print.setOutputFileName(fn);
            }*/


}

