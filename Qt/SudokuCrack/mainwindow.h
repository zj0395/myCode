#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sudokucrack.h"
#include "sudukucrackfromfile.h"

class QPushButton;
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent * );
    void resizeEvent(QResizeEvent* size);
    ~MainWindow();

private:

    void setResult(const vvint &d);
    void setButtonInit();
    void clearall();

    QPushButton ***b;
    QPushButton **others;
    QPushButton **key;
    QWidget* widget;
    QFrame* widget2;
    Ui::MainWindow *ui;
    vvint vvnum;

private slots:
    void tablebuttonClicked();
    void keyboardclicked();
    void beginclicked();
    void about_clicked();
    void new_tabclicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
};



#endif // MAINWINDOW_H
