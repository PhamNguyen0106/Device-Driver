#ifndef HMI_STATES_VALUES_H
#define HMI_STATES_VALUES_H
#include "qtquick2applicationviewer.h"
#include "hmi_shared_memory.h"

void hmi_state_shutdown_event(QtQuick2ApplicationViewer *hmi_dashboard);
void hmi_state_animation_event(QtQuick2ApplicationViewer *hmi_dashboard);
void hmi_state_runtime_event(tshared_memory*data,QtQuick2ApplicationViewer *hmi_dashboard);
void hmi_state_default_event(QtQuick2ApplicationViewer *hmi_dashboard);
#endif // HMI_STATES_VALUES_H
