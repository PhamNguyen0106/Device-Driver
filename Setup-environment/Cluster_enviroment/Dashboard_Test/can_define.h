#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "ecu.h"

#define PEDAL_ACCEL     0x109
#define STEERING_WHEEL  0x103
#define CRUISE_CONTROL  0x107
#define LIGHT_SYSTEM    0x200
#define LANE_DETECT     0x106

class CanProcess : public QObject
{
    Q_OBJECT

public:
    explicit CanProcess(QObject *parent = nullptr);
    virtual ~CanProcess();
    void process(quint16 pid, quint32 value);
};
