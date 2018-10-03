#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <form.h>
#include <ui_mainwindow.h>
#include <boost/multiprecision/cpp_int.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  boost::multiprecision::uint1024_t  bignum(QString a, QString b);
  boost::multiprecision::uint1024_t bignum_1(QString a, QString b);
  boost::multiprecision::uint1024_t QStringToBig(QString a);
signals:
    void set_open_keys();
    void is_a_prime();
private slots:

    void get_open_keys();


    void on_pushButton_2_clicked();

    void on_Calculate_Button_clicked();


    void on_Bit_SLider_valueChanged(int value);


    void on_Generate_button_clicked();

private:

    Ui::MainWindow *ui;
    Form *sWindow;
};

#endif // MAINWINDOW_H
