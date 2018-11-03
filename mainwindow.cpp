#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/common_factor_rt.hpp>
#include <QTime>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace boost::integer;
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
    connect(this,SIGNAL(set_closed_keys()),this,SLOT(get_closed_keys()));
    connect(this,SIGNAL(set_closed_keys_16()),this,SLOT(get_closed_keys_16()));
    connect(this,SIGNAL(set_open_keys_16()),this,SLOT(get_open_keys_16()));
    srand(std::time(nullptr));
    ui->label_7->hide();
    ui->label_8->hide();
    QRegExp rx("\\d{32}");
    QValidator *validator= new QRegExpValidator(rx,this);
    ui->p->setValidator(validator);
    ui->q->setValidator(validator);



}

MainWindow::~MainWindow()
{
    strlist.clear();
    delete ui;
}

boost::multiprecision::uint1024_t MainWindow::bignum(QString &a, QString &b)
{
    return (QStringToBig(a)*QStringToBig(b));
}

boost::multiprecision::uint1024_t MainWindow::bignum_1(QString &a, QString &b)
{
    return ((QStringToBig(a)-1)*(QStringToBig(b)-1));
}

boost::multiprecision::uint1024_t MainWindow::QStringToBig(QString &a)
{
    return (lexical_cast <boost::multiprecision::uint1024_t>(a.toStdString()));
}

QString MainWindow::DECstr_To_HEXstr(QString &a)
{
    std::stringstream ss;
    ss<<std::hex<<QStringToBig(a);
    std::string str;
    ss>>str;
    return a=QString::fromStdString(str);

}

void MainWindow::get_open_keys()       // слот меняет текст открытого ключа
{
    QString e=ui->e->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Open_Keys->setText("Открытый ключ { "+ e + "; " + n +"}");

}
void MainWindow::get_closed_keys()       // слот меняет текст закрытого ключа
{
    QString d=ui->d->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Closed_Keys->setText("Закрытый ключ { "+ d + "; " + n +"}");

}
void MainWindow::get_open_keys_16()       // слот меняет текст открытого ключа
{
    QString e=ui->e->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Open_Keys->setText("Открытый ключ { "+ DECstr_To_HEXstr(e) + "; " + DECstr_To_HEXstr(n) +"}");

}
void MainWindow::get_closed_keys_16()       // слот меняет текст закрытого ключа
{
    QString d=ui->d->toPlainText();
    QString n=ui->n->toPlainText();
    ui->Closed_Keys->setText("Закрытый ключ { "+ DECstr_To_HEXstr(d) + "; " + DECstr_To_HEXstr(n) +"}");

}

void MainWindow::on_Calculate_Button_clicked()
{
    QString p=ui->p->text();
    QString q=ui->q->text();
    if(miller_rabin_test(QStringToBig(p),25)==false || miller_rabin_test(QStringToBig(q),25)==false)
    {
        ui->statusBar->showMessage("Вы пытаетесь сгенерировать ключи используя НЕ простые числа. Не надо так.");
    }
    else

{
    ui->statusBar->clearMessage();
    boost::multiprecision::uint1024_t n=bignum(p,q);
    QString b=QString::fromStdString(n.str());
    ui->n->setText(QString::fromStdString(n.str()));                                  // устанавливаю текст итогового поля
    n=bignum_1(p,q);
    ui->fi->setText(QString::fromStdString(n.str()));                               // записываю результат метода Эйлера
    int i=3;
    while((gcd(n,i))>2)
    {
        i+=2;
    }
    ui->e->setText(QString::number(i));
    int k=0;
    while (((k*n+1)%i)>0)
    {
        ++k;
    }
    boost::multiprecision::uint1024_t d=(k*n+1)/i;
    ui->d->setText((QString::fromStdString(d.str())));
    MainWindow::on_check_16Hex_clicked();       // метод , устанавливющий 10 или 16 системы счисления в зависмости от состояния чекбокса
}
    }

void MainWindow::on_pushButton_2_clicked()
{
    sWindow->show();  // Показываем второе окно
        this->close();    // Закрываем основное окно
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

        int x=rand()%9+1;                                  // рандом от 1 до 9
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


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0)

    ui->tabWidget->QWidget::lower();
    else
        ui->tabWidget->QWidget::raise();
}


void MainWindow::on_Shifr_button_clicked()
{

   QString Text=ui->Noshifr_textEdit->toPlainText();

   uint1024_t txt{};
   QString nT=ui->n->toPlainText();
   uint1024_t   n=QStringToBig(nT);
   QString e=ui->e->toPlainText();
   ui->Shifr_textEdit->clear();
   for (int i=0;i<Text.length();i++)
   {
       txt=Text[i].unicode();
       txt=pow(txt,e.toInt())%n;


    ui->Shifr_textEdit->appendPlainText(QString::number(lexical_cast <uint64_t>(txt)));

   }


}



void MainWindow::on_check_16Hex_clicked()
{
    if(ui->check_16Hex->isChecked())
    {
        emit get_closed_keys_16();
        emit get_open_keys_16();
    }
    else
    {
        emit get_closed_keys();
        emit get_open_keys();
    }
}

void MainWindow::on_Deshifr_button_clicked()
{
    ui->Deshifr_textEdit->clear();
    QString str=ui->Shifr_textEdit->toPlainText();
    QStringList strList=str.split('\n');                    // кладу в массив строк по одной строке зашифрованного символа
    for(int i=0;i<strList.length();i++)
    {
        str=strList.at(i);
        cpp_int pow{ui->d->toPlainText().toStdString()};
        cpp_int mod{ui->n->toPlainText().toStdString()};
        cpp_int base{str.toStdString()};
        cpp_int result = powm(base, pow, mod);
        QString a=QString::fromStdString(result.str());
      const  QChar fa= a.toInt();
      str.clear();
      str+=fa;
        ui->Deshifr_textEdit->insertPlainText(str);
    }

}

void MainWindow::on_p_textChanged()
{
        QString p=ui->p->text();
        if(p=="")
        {
            ui->label_7->hide();
        }
        if(p!="")
  {

        if(miller_rabin_test(QStringToBig(p),25)==false)
      {
        ui->label_7->show();
        ui->statusBar->showMessage("Пожалуйста , введите простое число или воспользуйтесь генератором простых чисел.");
      }

        if(miller_rabin_test(QStringToBig(p),25)==true)
      {
        ui->label_7->hide();
      }
  }

}

void MainWindow::on_q_textChanged()
{
        QString q=ui->q->text();

        if(q=="")
        {
            ui->label_8->hide();
        }

        if(q!="")
  {

        if(miller_rabin_test(QStringToBig(q),25)==false)
      {
        ui->label_8->show();
        ui->statusBar->showMessage("Пожалуйста , введите простое число или воспользуйтесь генератором простых чисел.");
      }

        if(miller_rabin_test(QStringToBig(q),25)==true)
      {
        ui->label_8->hide();
      }

  }

}
