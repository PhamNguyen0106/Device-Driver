#include <dlt/dlt.h>
#include "hmi_dashboard.h"
#include "hmi_shared_memory.h"
#include "hmi_states_values.h"

HMI_STATES hmi_state;
tshared_memory hmi_valid_data;
DLT_IMPORT_CONTEXT(hmi_context)
#define HMI_VALIDATION_CTR  19
#define ENABLED     1
#define DISABLED    0
#define HMI_ANIMATION_CTR_LIMIT     21

Window::Window(QWindow *parent):QQuickView(parent){
    Dashboard =new QtQuick2ApplicationViewer();
    hmi_state_shutdown_event(Dashboard);
    hmi_state =HMI_STATE_SHUTDOWN;
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("INITIAL HMI DASHBOARD STATE: HMI_STATE_SHUTDOWN"));
    memset(&hmi_valid_data,0,sizeof(hmi_valid_data));
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("Init hmi_valid_data structure values to 0"));
    Dashboard->setMainQmlFile(QStringLiteral("qrc:/main.qml"));
    Dashboard->showExpanded();
}

void Window::Update_Can_Data(){
    uint8_t hmi_shmem_res;
    uint8_t hmi_cmp_data_res;
    static uint8_t hmi_validation_ctr =0;
    static uint8_t hmi_animation_ctr =0;
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    hmi_shmem_res =hmi_init_shared_memory();
    if(hmi_shmem_res ==0){
        hmi_cmp_data_res =hmi_compare_data(&hmi_valid_data);
        if(hmi_cmp_data_res ==0){
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("No value was changed -Iqual structures (Shared memory and Valid data)"));
            hmi_validation_ctr++;
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("Increment HMI_VALIDATION_CTR:"),DLT_INT(hmi_validation_ctr));
            if(hmi_validation_ctr >HMI_VALIDATION_CTR &&hmi_state !=HMI_STATE_ANIMATION){
                hmi_state =HMI_STATE_COMUNNICATION_ERROR;
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_COMUNNICATION_ERROR"));
                hmi_validation_ctr =0;
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("COMUNNICATION_ERROR occurs, HMI_VALIDATION_CTR:"),DLT_INT(hmi_validation_ctr));
            }else if(hmi_validation_ctr <HMI_VALIDATION_CTR &&hmi_state ==HMI_STATE_ANIMATION){
                hmi_validation_ctr--;
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI_STATE_ANIMATION running, decrement HMI_VALIDATION_CTR:"),DLT_INT(hmi_validation_ctr));
            }
        }else{
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("Diferent structures (Shared memory and Valid data)"));
            hmi_copy_data(&hmi_valid_data);
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("Copy values from Shared Memory to Valid data)"));
            hmi_validation_ctr =0;
        }
    }else{
        DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("Unable to read SHARED MEMORY -Stay on the same HMI_STATE"));
        return;
    }
    hmi_deinit_shared_memory();
    switch(hmi_state){
        case HMI_STATE_SHUTDOWN:
        {
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("ENTER TO HMI DASHBOARD STATE: HMI_STATE_SHUTDOWN"));
            if(hmi_valid_data.key_status ==DISABLED){
                hmi_state =HMI_STATE_SHUTDOWN;
                hmi_state_shutdown_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_SHUTDOWN"));
            }else{
                hmi_state =HMI_STATE_ANIMATION;
                hmi_state_animation_event(Dashboard);
                hmi_animation_ctr++;
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_ANIMATION"));
            }
            break;
        }
        case HMI_STATE_ANIMATION:
        {
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("ENTER TO HMI DASHBOARD STATE: HMI_STATE_ANIMATION"));
            if(hmi_valid_data.key_status ==DISABLED){
                hmi_state =HMI_STATE_SHUTDOWN;
                hmi_state_shutdown_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_SHUTDOWN"));
            }else if(hmi_animation_ctr <=HMI_ANIMATION_CTR_LIMIT){
                hmi_state =HMI_STATE_ANIMATION;
                hmi_state_animation_event(Dashboard);
                hmi_animation_ctr++;
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_ANIMATION"));
            }else{
                hmi_state =HMI_STATE_DEFAULT;
                hmi_animation_ctr =0;
                hmi_state_default_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_DEFAULT"));
            }
            break;
        }
        case HMI_STATE_DEFAULT:
        {
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("ENTER TO HMI DASHBOARD STATE: HMI_STATE_DEFAULT"));
            if(hmi_valid_data.key_status ==DISABLED){
                hmi_state =HMI_STATE_SHUTDOWN;
                hmi_state_shutdown_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_SHUTDOWN"));
            }else{
                hmi_state =HMI_STATE_RUNTIME;
                hmi_state_runtime_event(&hmi_valid_data,Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_RUNTIME"));
            }
            break;
        }
        case HMI_STATE_RUNTIME:
        {
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("ENTER TO HMI DASHBOARD STATE: HMI_STATE_RUNTIME"));
            if(hmi_valid_data.key_status ==DISABLED){
                hmi_state =HMI_STATE_SHUTDOWN;
                hmi_state_shutdown_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_SHUTDOWN"));
            }else{
                hmi_state =HMI_STATE_RUNTIME;
                hmi_state_runtime_event(&hmi_valid_data,Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_RUNTIME"));
            }
            break;
        }
        case HMI_STATE_COMUNNICATION_ERROR:
        {
            DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("ENTER TOHMI DASHBOARD STATE: HMI_STATE_COMUNNICATION_ERROR"));
            if(hmi_valid_data.key_status ==ENABLED){
                hmi_state =HMI_STATE_RUNTIME;
                hmi_state_runtime_event(&hmi_valid_data,Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_RUNTIME"));
            }else{
                hmi_state =HMI_STATE_SHUTDOWN;
                hmi_state_shutdown_event(Dashboard);
                DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI DASHBOARD CHANGE STATE TO: HMI_STATE_SHUTDOWN"));
            }
            break;
        }
    }
}
