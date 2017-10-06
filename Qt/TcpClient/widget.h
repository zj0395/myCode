#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QStackedWidget>

namespace Ui {
class Widget;
}

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

    void newMessage();
    void connectSuccess();

private slots:
    void on_buttonSend_clicked();

    void on_buttonConnect_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket socket;
};

#endif // WIDGET_H
