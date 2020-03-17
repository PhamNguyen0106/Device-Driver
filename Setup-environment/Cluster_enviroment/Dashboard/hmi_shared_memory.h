#ifndef HMI_SHARED_MEMORY_H
#define HMI_SHARED_MEMORY_H
#include <stdint.h>

typedef struct{
    float speed;
    uint32_t odometer;
    uint16_t steering_wheel;
    uint16_t rpms;
    uint8_t cruise_control;
    uint8_t gear;
    uint8_t lightning;
    uint8_t key_status;
    uint8_t lane_detect;
}tshared_memory;

uint8_t hmi_init_shared_memory(void);
void hmi_deinit_shared_memory(void);
uint8_t hmi_compare_data(tshared_memory*valid_data);
void hmi_copy_data(tshared_memory*valid_data);
#endif // HMI_SHARED_MEMORY_H
