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

    static const QStringList GEOS;

private slots:
    void on_fileOption_currentIndexChanged(int index);

    void on_buttonTransform_clicked();

    void on_buttonFileBegin_clicked();

    void on_buttonFileEnd_clicked();

private:
    Ui::Widget *ui;

private:
    int getFromPro();
    int getDestPro();
    void onePointTransform(int fromPro, int destPro);
    void fileTransfrom(int fromPro, int destPro);
    void buildCombox();
    void saveToFile(const QPolygonF &poly, QString saveName);
};

#endif // WIDGET_H
