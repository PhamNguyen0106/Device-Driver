#ifndef HMI_SHARED_MEMORY_H
#define HMI_SHARED_MEMORY_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <QByteArray>

#define ON 1
#define OFF 0

#define KEY_STATUS      0x101
#define STEERING_WHEEL  0x103
#define LANE_DETECT     0x106
#define CRUISE_CONTROL  0x107
#define PEDAL_ACCEL     0x109
#define LIGHT_SYSTEM    0x200

typedef struct{
    uint32_t speed;
    uint32_t odometer;
    uint16_t steering_wheel;
    uint16_t rpms;
    uint8_t cruise_control;
    uint8_t gear;
    uint8_t lightning;
    uint8_t key_status;
    uint8_t lane_detect;
}tshared_memory;

void hmi_init_shared_memory(void);
void hmi_deinit_shared_memory(void);
void write_int_value(quint16 frame_id, quint32 value);

#endif // HMI_SHARED_MEMORY_H
