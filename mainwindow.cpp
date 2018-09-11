#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLocale>
#include <form.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButton_clicked()
{
    QString p=ui->p->text();         // сохраняю текст в переменную
    QString q=ui->q->text();
    QString b;
    b.setNum(p.toInt()*q.toInt());              // преобразовываю текст в числа
    ui->S->setText(b);                          // устанавливаю текст итогового поля
}
