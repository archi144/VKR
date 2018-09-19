#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLocale>
<<<<<<< HEAD
#include <random.hpp>
#include <isprime.h>
=======

>>>>>>> f7653c0e3cac990aad01c8ba1f682d6377d1fe58
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sWindow= new Form();
    connect(sWindow,&Form::firstWindow,this,&MainWindow::show);
    connect(this,SIGNAL(set_open_keys()),this,SLOT(get_open_keys()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_open_keys()       // слот меняет текст открытого ключа
{
    QString e=ui->e->text();
    QString n=ui->n->text();
    ui->Open_Keys->setText("Открытый ключ { " + e + "; " + n +"}");

}



void MainWindow::on_Calculate_Button_clicked()
{
    int p=ui->p->text().toInt();
    int q=ui->p->text().toInt();
    QString b;
    b.setNum(p*q);                      // преобразовываю текст в число
    ui->n->setText(b);                          // устанавливаю текст итогового поля
    b.setNum((p-1)*(q-1));
    ui->fi->setText(b);
}

void MainWindow::on_pushButton_2_clicked()
{
    sWindow->show();  // Показываем второе окно
        this->close();    // Закрываем основное окно
}


void MainWindow::on_p_valueChanged(int arg1)
{
    if(isPrime(arg1))
        emit is_a_prime();
}



void MainWindow::on_fi_textChanged(const QString &arg1)
{
    long int MAX=ui->fi->text().toInt();
    int long A = Random::get(0,ui->fi->text().toInt());   //случайно выбираю число от 0 до φ(n)
    while(isPrime(A) && MAX%A!=0)
    {

        ui->e->setText(QString::number(A));
    }
    emit set_open_keys();                     // вызываем сигнал устанавливающий открытые ключи в тексте

}
