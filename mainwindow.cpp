#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <QTime>
using namespace boost::multiprecision;
using boost::lexical_cast;

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

boost::multiprecision::uint1024_t MainWindow::bignum(QString a, QString b)
{
    return (QStringToBig(a)*QStringToBig(b));
}
boost::multiprecision::uint1024_t MainWindow::bignum_1(QString a, QString b)
{
    return ((QStringToBig(a)-1)*(QStringToBig(b)-1));
}
boost::multiprecision::uint1024_t MainWindow::QStringToBig(QString a)
{
    return (lexical_cast <boost::multiprecision::uint1024_t>(a.toStdString()));
}
void MainWindow::get_open_keys()       // слот меняет текст открытого ключа
{
    QString e=ui->e->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Open_Keys->setText("Открытый ключ { " + e + "; " + n +"}");

}



void MainWindow::on_Calculate_Button_clicked()
{
    QString p=ui->p->toPlainText();
    QString q=ui->q->toPlainText();

    boost::multiprecision::uint1024_t n=bignum(p,q);
    QString b=QString::fromStdString(n.str());
    ui->n->setText(QString::fromStdString(n.str()));                                  // устанавливаю текст итогового поля
    n=bignum_1(p,q);
    ui->fi->setText(QString::fromStdString(n.str()));                               // записываю результат метода Эйлера
  //  boost::multiprecision::uint1024_t MAX=ui->fi->toPlainText().toInt();
 //   boost::multiprecision::uint1024_t A = Random::get(0,ui->fi->toPlainText().toInt());   //случайно выбираю число от 0 до φ(n)
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


// генерирует цифры , объединяя их в большое число и перед записью проверяет на простоту

void MainWindow::on_Generate_button_clicked()
{
   QTime time;
   time.start();
    bool exit=true;
    while(exit)
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
        --limit;
    }
    if(miller_rabin_test(QStringToBig(Value),25))
     {
        ui->Generate_Prime->setText(Value);
        exit=false;
     }
}
    ui->Time_of_generate->setText("Время генерации (мс): "+QString::number(time.elapsed()));
}
