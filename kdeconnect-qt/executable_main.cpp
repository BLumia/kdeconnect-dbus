#include <QApplication>

#include <kcmanager.h>

#include "devicemanager.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    DeviceManager devMan;

    return app.exec();
}
