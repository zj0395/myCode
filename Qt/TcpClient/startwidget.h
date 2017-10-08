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
    enum WaittingTask{
        Task_Nothing = 0,
        Task_Login,
        Task_Reg,
    };

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
    WaittingTask task;


private:
    void connectToServer();

    void sendUserInfo(MessageType);
    void sendMessage(MessageType type, QString message);
    void recvMessage();

    void showWrong(QString title, QString word);
    void showWrongChatWindow(QString title, QString word);
    void showInfomation(QString title, QString word);
    void connectedToServerSuccess();
    void timeOut();
};

#endif // STARTWIDGET_H
