#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "../TcpDefines.h"

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

private:
    void connectToServer();
    void sendMessage(MessageType);
};

#endif // STARTWIDGET_H
