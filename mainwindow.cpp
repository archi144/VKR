#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random.hpp>
#include <isprime.h>
#include <QRandomGenerator>
#include <QToolTip>
#include <QPoint>
#include <boost/multiprecision/cpp_int.hpp>
#include <QValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sWindow= new Form();
    connect(sWindow,&Form::firstWindow,this,&MainWindow::show);
    connect(this,SIGNAL(set_open_keys()),this,SLOT(get_open_keys()));
  //  QToolTip::showText(ui->label->pos(),"Hello WOrld",ui->label);                // доделать

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_open_keys()       // слот меняет текст открытого ключа
{
    QString e=ui->e->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Open_Keys->setText("Открытый ключ { " + e + "; " + n +"}");

}



void MainWindow::on_Calculate_Button_clicked()
{
    boost::multiprecision::uint1024_t p=ui->p->toPlainText().toInt();
    boost::multiprecision::uint1024_t q=ui->p->toPlainText().toInt();
    QString b;
    b.setNum(p*q);                      // преобразовываю текст в число
    ui->n->setText(b);                          // устанавливаю текст итогового поля
    b.setNum((p-1)*(q-1));
    ui->fi->setText(b);                 // записываю результат метода Эйлера

    boost::multiprecision::uint1024_t MAX=ui->fi->toPlainText().toInt();
    boost::multiprecision::uint1024_t A = Random::get(0,ui->fi->toPlainText().toInt());   //случайно выбираю число от 0 до φ(n)
//    if(isPrime(A) && MAX%A!=0)
//    {

//        ui->e->setText(QString::number(A));
//    }
    emit set_open_keys();                     // вызываем сигнал устанавливающий открытые ключи в тексте
}

void MainWindow::on_pushButton_2_clicked()
{
    sWindow->show();  // Показываем второе окно
        this->close();    // Закрываем основное окно
}



void MainWindow::on_Bit_SLider_valueChanged(int value)
{
    ui->Bit_SLider->setSingleStep(ui->Bit_SLider->value());       // устанавливаю шаг равный значению слайдера
    ui->Bit_label->setText(QString::number(value) + " Бит(а)");


}


// генерирует цифры , объединяя их в большое число

void MainWindow::on_Generate_button_clicked()
{

    int limit = ui->generate_size->value();
    QString Value="";
    while (limit)
    {
        QString tempValue;
        int x=qrand()%9+1;                                  // рандом от 1 до 9
            if(limit==1 && x%2==0)
            {
                while (x%2==0)
                    x=qrand()%9+1;
            }
        tempValue=(QString::number(x));
        Value+=tempValue;
        ui->Generate_Prime->setText(Value);
        --limit;
    }
}
