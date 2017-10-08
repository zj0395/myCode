#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QStackedWidget>

namespace Ui {
class Widget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();

    void newMessage(QString temp);

    void sendSuccess();
private slots:
    void on_buttonSend_clicked();

    void on_buttonUpdate_clicked();

signals:
    void sendMsg(QString msg);

private:
    Ui::Widget *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // WIDGET_H
