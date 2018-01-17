#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_pushButtonOPen_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonDo_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
