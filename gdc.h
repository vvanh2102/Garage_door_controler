#ifndef GDC_H
#define GDC_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

class Gdc : public QWidget
{
    Q_OBJECT

public:
    Gdc(QWidget *parent = nullptr);
    ~Gdc();

private:
    QLabel *operationModeLabel;
    QLabel *manualTimeLabel;
    QLabel *sensor1StatusLabel;
    QLabel *sensor2StatusLabel;
    QLabel *actionLabel; // new label to show current action
    QPushButton *openDoorButton;
    QPushButton *closeDoorButton;
    QPushButton *manualModeButton;
    QPushButton *autoModeButton;
    int manualTime;
    int manualTimeRemaining;
    QTimer *manualModeTimer;
    QString operationMode;
    QString currentAction; // new variable to store current action

private slots:
    void openDoor();
    void closeDoor();
    void manualMode();
    void autoMode();
    void updateManualTimeLabel();
};

#endif // GDC_H
