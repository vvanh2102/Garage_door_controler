#include "widget.h"
#include "ui_widget.h"
#include "comserial.h"
#include "QTimer"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Garage door controller");

    devserial = new QSerialPort(this);

    /* Tạo Object the Class comserial để thao tác đọc/ghi theo cách của tôi */
    procSerial = new comserial(devserial);

    /* Tải cổng nối tiếp thiết bị có sẵn */
    QStringList DispSeriais = procSerial->CarregarDispositivos();

    /* Chèn vào ComboxBox các thiết bị */
    ui->cbDevice->addItems(DispSeriais);

    /* Kích hoạt PushButton "Conectar" nếu tìm thấy bất kỳ cổng nào.
     *  Nếu xảy ra lỗi, nó sẽ được báo cáo trong Nhật ký
     */
    if (DispSeriais.length() > 0) {
            ui->pbOpenSerial->setEnabled(true);
            ui->teLog->insertHtml("<span style='color: green;'>Serial port ready to use.</span><br>");
    } else {
            ui->teLog->insertHtml("<span style='color: red;'>No serial port detected!</span><br>");
    }


    // Khởi tạo giá trị cho currentBaudRate, ví dụ: 9600
    currentBaudRate = 9600;

    // Khai báo một danh sách tốc độ truyền
    baudRateList = {2400, 4800, 9600, 19200, 115200};

    // Hiển thị danh sách tốc độ truyền ban đầu trên combobox
    for (int baudRate : baudRateList) {
        ui->cbBaudRate->addItem(QString::number(baudRate));
    }

    // Nếu tốc độ truyền hiện tại không nằm trong danh sách, thêm nó vào danh sách và combobox
    if (!baudRateList.contains(currentBaudRate)) {
        baudRateList.append(currentBaudRate);
        ui->cbBaudRate->addItem(QString::number(currentBaudRate));
    }

    // Hiển thị tốc độ truyền hiện tại trên combobox
    ui->cbBaudRate->setCurrentText(QString::number(currentBaudRate));

    /* Kết nối các đối tượng -> Tín hiệu và Khe cắm
     * DevSerial với Đọc dữ liệu nối tiếp
     * TextEdit "teLog" với getData() sau khi gửi dữ liệu WriteData()
     * [Không áp dụng ở đây trong phiên bản 5.X]
     */
    connect(devserial, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(ui->teLog, SIGNAL(getData(QByteArray)), this, SLOT(WriteData(QByteArray)));

}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_pbCloseSerial_clicked()
{
    bool statusCloseSerial;


    statusCloseSerial = procSerial->Desconectar();

    /*LỖI: Có một lỗi khi đóng QtSerialPort, đã được cộng đồng biết ở đó
      * khi được sử dụng với waitForReadyRead, sẽ báo lỗi 12 Thời gian chờ trên SerialPort và không đóng kết nối
      *tuy nhiên báo lỗi nhưng đóng máy.
      * Để khắc phục sự cố Ngắt kết nối, tôi đã kiểm tra với isOpen ngay sau khi đóng kết nối
      * nối tiếp.
     */

    if (statusCloseSerial) {
        ui->pbCloseSerial->setEnabled(false);
        ui->pbOpenSerial->setEnabled(true);
        ui->teLog->insertHtml("<span style='color: green;'>Serial port closed successfully!</span><br>");
    }
    else {
        ui->teLog->insertHtml("<span style='color: red;'>Unable to close serial connection.</span><br>");
    }
}

void Widget::on_pbOpenSerial_clicked()
{
    bool statusOpenSerial;

    // Lấy tốc độ truyền được chọn từ combobox và chuyển thành số nguyên
    int selectedBaudRate = ui->cbBaudRate->currentText().toInt();

    statusOpenSerial = procSerial->Conectar(ui->cbDevice->currentText(), selectedBaudRate);
    if (statusOpenSerial) {
        ui->pbCloseSerial->setEnabled(true);
        ui->pbOpenSerial->setEnabled(false);
         ui->teLog->insertHtml("<span style='color: green;'>Serial port opened successfully!</span><br>");

        // Lưu tốc độ truyền hiện tại vào biến currentBaudRate
        currentBaudRate = selectedBaudRate;

        // Thêm tốc độ truyền vào combobox nếu nó chưa tồn tại
        if (ui->cbBaudRate->findText(QString::number(currentBaudRate)) == -1) {
            ui->cbBaudRate->addItem(QString::number(currentBaudRate));
        }

        // Hiển thị tốc độ truyền hiện tại trên combobox
        ui->cbBaudRate->setCurrentText(QString::number(currentBaudRate));
    }
    else {
         ui->teLog->insertHtml("<span style='color: red;'>Unable to open serial connection !</span><br>");
    }
}
void Widget::WriteData(const QByteArray data)
{
    procSerial->Write(data);
}
void Widget::ReadData()
{
    QString data = procSerial->Read();
    qDebug() << "Output: " << data << Qt::endl;

    ui->teLog->append(data);
}
// close the door
void Widget::on_closedoor_clicked()
{
    QString Cmd = "close door";
    qDebug() << "Input: " << Cmd << Qt::endl;
    ui->hienthithongtin->setText(Cmd);
    WriteData(Cmd.toUtf8());
}
// open the door
void Widget::on_opendoor_clicked()
{
    QString Cmd = "open door ";
    qDebug() << "Input: " << Cmd << Qt::endl;
    ui->hienthithongtin->setText(Cmd);
    WriteData(Cmd.toUtf8());
}
void Widget::on_Manualmode_clicked()
{

}
void Widget::on_Automode_clicked()
{

}



