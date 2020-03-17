#include <QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QTimer>
#include <dlt/dlt.h>
#include "hmi_dashboard.h"
#include "hmi_shared_memory.h"
#include "hmi_states_values.h"

DLT_DECLARE_CONTEXT(hmi_context);

int main(int argc,char*argv[]){
    DLT_REGISTER_APP("CPI","Cluster PI");

    DLT_REGISTER_CONTEXT(hmi_context,"HMI","HMI Context");
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING("HMI Dashboard Initialization"));
    QGuiApplication app(argc,argv);
    Window Dashboard;
    QTimer Timer;
    Timer.start(100);
    app.connect(&Timer,SIGNAL(timeout()),&Dashboard,SLOT(Update_Can_Data()));
    return app.exec();
    DLT_UNREGISTER_CONTEXT(hmi_context);
    DLT_UNREGISTER_APP();
}
