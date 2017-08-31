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

    bool isreset(){    return newstr=="0";  }
    void reset(){newstr="0";_needupdate=1;pushkeynum=0;}
    inline void cutthelast(int n){   newstr.remove(newstr.length()-n,n);  }
    inline void setoldstr(){    oldstr3=oldstr2;oldstr2=oldstr1;}

signals:
    void newstrchanged(const QString&str);
    void resultchanged(const QString&str);
    void oldstrchanged();
    void oldstr1change(const QString&str);
    void oldstr2change(const QString&str);
    void oldstr3change(const QString&str);
    void presskeydoit();

public slots:
    void inputkey();
    void changeresultstyle();
    void changeinputstyle();
    void tochangeoldstrscreen();
    void changeinputstr(const QString&str);

private slots:
    void on_keyadd_clicked();

    void on_keyminus_clicked();

    void on_keymultipy_clicked();

    void on_keydivide_clicked();

    void on_deleteone_clicked();

    void on_deleteall_clicked();

    void on_keydoit_clicked();

    void on_number3_clicked();

    void on_number6_clicked();

    void on_number9_clicked();

    void on_number8_clicked();

    void on_number5_clicked();

    void on_number2_clicked();

    void on_keypoint_clicked();

    void on_number0_clicked();

    void on_number1_clicked();

    void on_number4_clicked();

    void on_number7_clicked();

    void on_leftbracket_clicked();

    void on_rightbracket_clicked();

    void on_num10_clicked();

    void on_CONSTPI_clicked();

    void on_sqrt_clicked();

    void on_power_clicked();

    void on_calfact_clicked();

    void on_calsin_clicked();

    void on_calcos_clicked();

    void on_caltan_clicked();

    void on_calln_clicked();

    void on_callg_clicked();

private:
    Ui::MainWindow *ui;
    QString newstr;
    QString oldstr1;
    QString oldstr2;
    QString oldstr3;
    QString resultstr;
    bool _needupdate;
    bool pushkeynum;
    bool isnotchar(QChar a);
};

#endif // MAINWINDOW_H
