#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Form_MainWidget;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    Form_MainWidget * mainWidget;
};

#endif // WIDGET_H
