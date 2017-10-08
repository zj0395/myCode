#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QStackedWidget>
#include <QTimer>

class QStandardItemModel;
namespace Ui {
class Widget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    void setUserName( QString name );
    void updateUserList( QString list );
    ~ChatWidget();

    void newMessage(QString temp);

    void sendSuccess();
private slots:
    void on_buttonSend_clicked();

    void on_buttonUpdate_clicked();

    void on_buttonNothing_clicked();

signals:
    void sendMsg(QString, QString  );
    void sendUpdateUserMsg();
    void sendCloseMsg(QString user);

private:
    Ui::Widget *ui;
    QString userName;
    QStandardItemModel * userModel;
    QTimer * timer;

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *);
};

#endif // WIDGET_H
