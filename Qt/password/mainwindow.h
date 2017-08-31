#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Login_clicked();

    void on_Logout_clicked();

private:
    Ui::MainWindow *ui;
    QString D_username;
    QByteArray D_password;
};

#endif // MAINWINDOW_H
