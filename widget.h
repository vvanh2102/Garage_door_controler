#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "comserial.h"

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
    void on_pbCloseSerial_clicked();
    void on_pbOpenSerial_clicked();
   // void on_pbSendCmd_clicked();

    void WriteData(const QByteArray data);
    void ReadData();


    void on_closedoor_clicked();

    void on_opendoor_clicked();

    void on_Manualmode_clicked();



    void on_Automode_clicked();





private:
    int currentBaudRate;
    Ui::Widget *ui;
    QSerialPort *devserial;
    comserial *procSerial;

    void CarregarInfoDispSerial(void);
    QList<int> baudRateList;
};

#endif // WIDGET_H
