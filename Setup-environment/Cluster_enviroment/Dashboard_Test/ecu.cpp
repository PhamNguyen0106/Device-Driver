// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <tuple>
#include <QCanBusFrame>
#include <QRandomGenerator>
#include <QString>
#include "ecu.h"
#include "shared_memory.h"

Ecu::Ecu(int ecuId, QSharedPointer<QCanBusDevice> canBus, QObject *parent)
    : EcuBase{ecuId, canBus, parent}
{
    hmi_init_shared_memory();
}

Ecu::~Ecu()
{
    hmi_deinit_shared_memory();
}

bool Ecu::isReadParameter(const QCanBusFrame &frame) const
{
    Q_UNUSED(frame);
}
void Ecu::sendReadParameter(quint16 pid, quint32 value)
{
    Q_UNUSED(pid);
    Q_UNUSED(value);
}
void Ecu::receiveReadParameter(const QCanBusFrame &frame)
{
    quint16 pid = 0U;
    quint32 value = 0U;
    std::tie(pid, value) = decodeReadParameter(frame);

    write_int_value(frame.frameId(), value);
    emitReadParameterMessage(QStringLiteral("Ecu/Recv"), pid, value);
}
