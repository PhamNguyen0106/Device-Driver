#include <QObject>
#include <QQmlContext>
#include <QQuickView>
#include "qtquick2applicationviewer.h"
#include <time.h>
#include <dlt/dlt.h>
#include "hmi_dashboard.h"

DLT_IMPORT_CONTEXT(hmi_context)

#define ENABLED     1
#define DISABLED    0.0

void hmi_state_shutdown_event(QtQuick2ApplicationViewer *hmi_dashboard){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    hmi_dashboard->rootContext()->setContextProperty("speed",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("odometer",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("steering_wheel",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("rpms",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("cruise_control",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("gear",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("key_status",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("lane_detect",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("lightning",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_right",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_left",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("high_beam",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("fog_light",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("shutdown",ENABLED);
}

void hmi_state_animation_event(QtQuick2ApplicationViewer *hmi_dashboard){
    static uint8_t ctr =0;
    static uint8_t flag =0;
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    hmi_dashboard->rootContext()->setContextProperty("odometer",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("steering_wheel",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("cruise_control",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("gear",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("key_status",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("lane_detect",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("lightning",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_right",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_left",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("high_beam",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("fog_light",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("shutdown",DISABLED);
    if(ctr<190&&flag ==0){
        hmi_dashboard->rootContext()->setContextProperty("speed",ctr);
        hmi_dashboard->rootContext()->setContextProperty("rpms",ctr*52.63);
        ctr+=19;
    }else if(ctr ==190&&flag ==0){
        flag =1;
        hmi_dashboard->rootContext()->setContextProperty("speed",ctr);
        hmi_dashboard->rootContext()->setContextProperty("rpms",ctr*52.63);
        return;
    }if(ctr>0&&flag ==1){
        hmi_dashboard->rootContext()->setContextProperty("speed",ctr);
        hmi_dashboard->rootContext()->setContextProperty("rpms",ctr*52.63);
        ctr-=19;
    }else if(ctr ==0&&flag ==1){
        flag =0;hmi_dashboard->rootContext()->setContextProperty("speed",ctr);
        hmi_dashboard->rootContext()->setContextProperty("rpms",ctr*52.63);
    }
}

void hmi_state_default_event(QtQuick2ApplicationViewer *hmi_dashboard){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    hmi_dashboard->rootContext()->setContextProperty("speed",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("odometer",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("steering_wheel",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("rpms",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("cruise_control",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("gear",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("key_status",ENABLED);
    hmi_dashboard->rootContext()->setContextProperty("lane_detect",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("lightning",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_right",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("turn_left",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("high_beam",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("fog_light",DISABLED);
    hmi_dashboard->rootContext()->setContextProperty("shutdown",DISABLED);
}

void hmi_state_runtime_event(tshared_memory*data,QtQuick2ApplicationViewer *hmi_dashboard){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    hmi_dashboard->rootContext()->setContextProperty("speed",data->speed);
    hmi_dashboard->rootContext()->setContextProperty("odometer",data->odometer);
    hmi_dashboard->rootContext()->setContextProperty("steering_wheel",data->steering_wheel);
    hmi_dashboard->rootContext()->setContextProperty("rpms",data->rpms);
    hmi_dashboard->rootContext()->setContextProperty("cruise_control",data->cruise_control);
    hmi_dashboard->rootContext()->setContextProperty("gear",data->gear);
    hmi_dashboard->rootContext()->setContextProperty("key_status",data->key_status);
    hmi_dashboard->rootContext()->setContextProperty("lane_detect",data->lane_detect);
    hmi_dashboard->rootContext()->setContextProperty("lightning",data->lightning);
    hmi_dashboard->rootContext()->setContextProperty("shutdown",DISABLED);
}

