#include <QApplication>

#include <kcmanager.h>

#include "devicewidget.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    QStringList devList = KCManager::devices(true, true);

    for (const QString & s : devList) {
        DeviceWidget * dv = new DeviceWidget(s);
        dv->show();
    }

    return app.exec();
}
