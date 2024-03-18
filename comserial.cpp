#include "comserial.h"


/**
 * @brief With Serial::With Serial * *
 * Chức năng của phương thức khởi tạo, khởi tạo các biến và đối tượng riêng để lớp sử dụng
 * * @param
 * @return
 */
comserial::comserial(QSerialPort *myDev)
{
    devSerial = myDev;
}


/**
 * @brief CommSerial::LoadDevices
  *
  * Chức năng kiểm tra tất cả các cổng khả dụng /dev/tty*
  * và sau đó đặt cổng bằng serial.setport và kiểm tra xem đó có phải là cổng không
  * cổng nối tiếp
  *
  * @param vô hiệu
  * @return QStringList với các thiết bị từ /dev là cổng nối tiếp
 */
QStringList comserial::CarregarDispositivos()
{
    QStringList devs;

    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts()) {

        devSerial->setPort(info);


        if (devSerial->open(QIODevice::ReadWrite)) {
            devSerial->close();
            devs << info.portName();
        }

    }
    return devs;
}



/**
* @brief Với Serial::Conectar
 * * Hàm nhận các thông số Cổng, Tốc độ truyền và Kiểm soát luồng và thực hiện kết nối
 * * @param Cổng QString(Cổng nối tiếp), uint32_t bd(Tốc độ truyền) * @return
 */
bool comserial::Conectar(QString Port, uint32_t bd)
{
    /* Device Serial Port */
    devSerial->setPortName(Port);
    qDebug() << "Serial Port Device: " << Port;


     /* Conectar SerialPort */

        /* BaudRate */
        switch (bd) {
        case 2400:
            qDebug() << "Baudrate: 2400";
            devSerial->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            qDebug() << "Baudrate: 4800";
            devSerial->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            qDebug() << "Baudrate: 9600";
            devSerial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            qDebug() << "Baudrate: 19200";
            devSerial->setBaudRate(QSerialPort::Baud19200);
            break;
        case 115200:
            qDebug() << "Baudrate: 115200";
            devSerial->setBaudRate(QSerialPort::Baud115200);
            break;
        }

        /*Kiểm soát lưu lượng */
        devSerial->setFlowControl(QSerialPort::NoFlowControl);


        /* cài đặt thêm */
        devSerial->setDataBits(QSerialPort::Data8);
        devSerial->setParity(QSerialPort::NoParity);
        devSerial->setStopBits(QSerialPort::OneStop);


        if(devSerial->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port connect successfully!";
            return true;
        }
        else {
            qDebug() << "No serial port connect !";
            qDebug() << "Error: " << devSerial->error();
            return false;
        }


}


/**
* @brief CommSerial::Ngắt kết nối
  *
  * Chức năng ngắt kết nối, thực hiện vệ sinh linh kiện và đóng
  *
  * @param
  * @trở lại
 */
bool comserial::Desconectar()
{
    devSerial->clear();
    devSerial->close();


    if(devSerial->error() == 0 || !devSerial->isOpen()) {
        qDebug() << "Serial port connect successful!";
        return true;
    }
    else {
        qDebug() << "No serial port connect ! ERRO: " << devSerial->error();
        return false;
    }

}


/**
* @brief CommSerial::Viết
  *
  * Hàm ghi nối tiếp, nhận con trỏ ký tự đã có sẵn ở dạng const char* của ghi
  *
  * @param const char *cmd
  * @return vô hiệu
 */
qint64 comserial::Write(const char *cmd)
{
    qint64 tamanhoEscrito;//kích thước bằng văn bản
    tamanhoEscrito = devSerial->write(cmd,qstrlen(cmd));

    return tamanhoEscrito;
}


/**
* @brief CommSerial::Đọc
  *
  * Chức năng Đọc những gì đến qua sê-ri sau khi ghi vào nó và trả về một QString
  *
  * @param
  * @return QString
 */
QString comserial::Read()
{
     QString bufRxSerial;

     /* Awaits read all the data before continuing */
     while (devSerial->waitForReadyRead(20)) {
         bufRxSerial += devSerial->readAll();
     }
     return bufRxSerial;
}


/**
* @brief CommSerial::Đọc
  *
  * Chức năng Đọc những gì đến qua sê-ri sau khi ghi vào nó và trả về một QString
  * trong trường hợp này, một số nguyên được gửi cùng với số ký tự trong bộ đệm nhận
  *
  * @param int
  * @return QString
 */
QString comserial::Read(int TamanhoBuffer)
{
    char buf[TamanhoBuffer];

    if (devSerial->canReadLine()) {
        devSerial->read(buf, sizeof(buf));
    }

    return buf;

}
