#ifndef COMSERIAL_H
#define COMSERIAL_H
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class comserial
{
public:
    comserial(QSerialPort *myDev);
    ~comserial();

    QStringList CarregarDispositivos();

    bool Conectar(QString Port, uint32_t bd);
    bool Desconectar(void);

    qint64 Write(const char *cmd);
    QString Read();
    QString Read(int TamanhoBuffer);

protected:
    QSerialPort *devSerial;
};

#endif // COMSERIAL_H
