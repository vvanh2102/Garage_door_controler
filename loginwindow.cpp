#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "widget.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Login Window");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    if (username == "admin" && password == "123456") {
        this->hide();
        widgetdisplay = new Widget;
        widgetdisplay->show();
    } else {
        ui->textbox->setText("Your account and password are incorrect");
    }
}
