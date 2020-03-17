#include "menu_options.h"
#include "shared_memory.h"
#include <QCoreApplication>
#include "ecumodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("can");
    QCoreApplication a(argc, argv);
    EcuModel model;
    return a.exec();
}
