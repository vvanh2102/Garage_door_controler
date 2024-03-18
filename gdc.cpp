#include "gdc.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QTimer>
#include<widget.h>
Gdc::Gdc(QWidget *parent)
    : QWidget(parent)
{
    operationMode = "Manual mode";
    operationModeLabel = new QLabel("Operation mode: " + operationMode);
    manualTimeLabel = new QLabel("");
    sensor1StatusLabel = new QLabel("Sensor 1: OK");
    sensor2StatusLabel = new QLabel("Sensor 2: OK");
    openDoorButton = new QPushButton("Open door");
    closeDoorButton = new QPushButton("Close door");
    manualModeButton = new QPushButton("Manual mode");
    autoModeButton = new QPushButton("Auto mode");
    actionLabel = new QLabel("");

    QVBoxLayout *labelLayout = new QVBoxLayout;
    labelLayout->addWidget(operationModeLabel);
    labelLayout->addWidget(manualTimeLabel);
    labelLayout->addWidget(sensor1StatusLabel);
    labelLayout->addWidget(sensor2StatusLabel);
    labelLayout->addWidget(actionLabel); // add new label to the layout

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(openDoorButton);
    buttonLayout->addWidget(closeDoorButton);
    buttonLayout->addWidget(manualModeButton);
    buttonLayout->addWidget(autoModeButton);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(buttonLayout);
    layout->addLayout(labelLayout);

    setLayout(layout);

    connect(openDoorButton, &QPushButton::clicked, this, &Gdc::openDoor);
    connect(closeDoorButton, &QPushButton::clicked, this, &Gdc::closeDoor);
    connect(manualModeButton, &QPushButton::clicked, this, &Gdc::manualMode);
    connect(autoModeButton, &QPushButton::clicked, this, &Gdc::autoMode);

    manualModeTimer = new QTimer(this);
    connect(manualModeTimer, &QTimer::timeout, this, &Gdc::updateManualTimeLabel);
}

Gdc::~Gdc()
{
    delete operationModeLabel;
    delete manualTimeLabel;
    delete sensor1StatusLabel;
    delete sensor2StatusLabel;
    delete openDoorButton;
    delete closeDoorButton;
    delete manualModeButton;
    delete autoModeButton;
    delete manualModeTimer;
    delete actionLabel;
}

void Gdc::openDoor()
{
    if (operationMode == "Auto mode") {
        currentAction = "Door command: Open door";
        actionLabel->setText(currentAction);
    } else {
        currentAction = "Door opened";
        actionLabel->setText(currentAction);
    }
    operationMode = "Open door";
    operationModeLabel->setText("Operation mode: " + operationMode);
}

void Gdc::closeDoor()
{
    if (operationMode == "Auto mode") {
        currentAction = "Door command: Close door";
        actionLabel->setText(currentAction);
    } else {
        currentAction = "Door closed";
        actionLabel->setText(currentAction);
    }
    operationMode = "Close door";
    operationModeLabel->setText("Operation mode: " + operationMode);
}

void Gdc::manualMode()
{
    bool ok;
    int minutes = QInputDialog::getInt(this, tr("Manual mode"),
        tr("How long (minutes) do you want the controller to be in manual mode?"),
        0, 0, 60,1, &ok);
    if (ok) {
        manualTime = minutes * 60;
        manualTimeRemaining = manualTime;
        manualTimeLabel->setText("Manual mode time remaining: " + QString::number(manualTimeRemaining) + " seconds");
        operationMode = "Manual mode";
        operationModeLabel->setText("Operation mode: " + operationMode);
        currentAction = "Manual mode";
        actionLabel->setText(currentAction);
        manualModeTimer->start(1000);
    }
}

void Gdc::autoMode()
{
    manualModeTimer->stop();
    manualTimeLabel->setText("");
    operationMode = "Auto mode";
    operationModeLabel->setText("Operation mode: " + operationMode);
    currentAction = "Auto mode";
    actionLabel->setText(currentAction);
}

void Gdc::updateManualTimeLabel()
{
    manualTimeRemaining--;
    manualTimeLabel->setText("Manual mode time remaining: " + QString::number(manualTimeRemaining) + " seconds");
    if (manualTimeRemaining == 0) {
        manualModeTimer->stop();
        manualTimeLabel->setText("");
        operationMode = "Auto mode";
        operationModeLabel->setText("Operation mode: " + operationMode);
        currentAction = "Auto mode";
        actionLabel->setText(currentAction);
    }
}
