#include "devicemanager.h"
#include "devicewidget.h"

#include <kcmanager.h>

#include <QDebug>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
    , m_manager(new KCManager(this))
{
    QStringList devList = KCManager::devices(true, true);

    for (const QString & s : devList) {
        DeviceWidget * dv = new DeviceWidget(s);
        dv->show();
    }

    connect(m_manager, &KCManager::deviceVisibilityChanged, this, [](const QString &id, bool isVisible){
        qDebug() << "deviceVisibleChanged" << id << isVisible;
    });

    connect(m_manager, &KCManager::deviceAdded, this, [](const QString &id){
        qDebug() << "deviceAdded" << id;
    });

    connect(m_manager, &KCManager::deviceListChanged, this, [](){
        qDebug() << "deviceListChanged";
    });
}
