#include "can_define.h"
#include "shared_memory.h"

CanProcess::CanProcess(QObject *parent)
    : QObject{parent}
{

}
#define PEDAL_ACCEL     0x109
#define STEERING_WHEEL  0x103
#define CRUISE_CONTROL  0x107
#define LIGHT_SYSTEM    0x200
#define LANE_DETECT     0x106
void CanProcess::process(quint16 pid, quint32 value)
{
    switch(pid)
    {
        case PEDAL_ACCEL:
            write_int_value(pid,value);
            break;
        case STEERING_WHEEL:
            write_int_value(pid,value);
            break;
        case CRUISE_CONTROL:
            write_int_value(pid,value);
            break;
        case LIGHT_SYSTEM:
            write_uint8_value(option,boolean_value);
            break;
        case LANE_DETECT:
            write_uint8_value(option,boolean_value);
            break;
        default:
            break;
    }
}
