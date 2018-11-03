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
  boost::multiprecision::uint1024_t  bignum(QString &a, QString &b);
  boost::multiprecision::uint1024_t bignum_1(QString &a, QString &b);
  boost::multiprecision::uint1024_t QStringToBig(QString &a);     //представляет строку в виде переменной uint1024_t
  QString DECstr_To_HEXstr(QString &a);       //из 10-ной системы счисления в 16-ную
  QStringList strlist;
signals:
    void set_open_keys();
    void set_closed_keys();
    void set_open_keys_16();
    void set_closed_keys_16();

private slots:

    void get_open_keys();
    void get_closed_keys();
    void get_open_keys_16();
    void get_closed_keys_16();
    void on_pushButton_2_clicked();
    void on_Calculate_Button_clicked();
    void on_Generate_button_clicked();
    void on_tabWidget_currentChanged(int index);

    void on_Shifr_button_clicked();

    void on_check_16Hex_clicked();

    void on_Deshifr_button_clicked();

    void on_p_textChanged();

    void on_q_textChanged();

private:

    Ui::MainWindow *ui;
    Form *sWindow;
};

#endif // MAINWINDOW_H
