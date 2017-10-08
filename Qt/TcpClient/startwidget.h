#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "../TcpDefines.h"
#include "widget.h"

class QTcpSocket;
class QTimer;
namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();

private slots:
    void on_buttonLogin_clicked();

    void on_buttonRegister_clicked();

private:
    Ui::StartWidget *ui;
    QTcpSocket *socket;
    QTimer *timer;
    ChatWidget chatWidget;
    bool isConnected;

private:
    void connectToServer();
    void sendInfo(MessageType);
    void sendMessage(QString message);
    void recvMessage();
    void showWrong(QString title, QString word);
    void showMessage(QString msg);
    void showInfomation(QString title, QString word);
    void connectedToServer();
    void timeOut();
};

#endif // STARTWIDGET_H
