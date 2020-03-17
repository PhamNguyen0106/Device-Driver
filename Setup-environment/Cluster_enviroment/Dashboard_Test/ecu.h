// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#pragma once

#include "ecucan/ecubase.h"
class QCanBusFrame;

class Ecu : public EcuBase
{
    Q_OBJECT
public:
    explicit Ecu(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent = nullptr);
    virtual ~Ecu();
    virtual bool isReadParameter(const QCanBusFrame &frame) const override;
    virtual void sendReadParameter(quint16 pid, quint32 value = 0U) override;
    virtual void receiveReadParameter(const QCanBusFrame &frame) override;

signals:
    void parameterRead(quint16 pid, quint32 value);
};
