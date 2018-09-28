#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <form.h>
#include <ui_mainwindow.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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
