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

    void on_p_valueChanged(int arg1);


    void on_fi_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Form *sWindow;
};

#endif // MAINWINDOW_H
