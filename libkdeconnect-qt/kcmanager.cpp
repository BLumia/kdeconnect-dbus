#include "kcmanager.h"

#include "kcdevice.h"
#include "kcdbuscommon.h"
#include "daemon_interface.h"

const QString DaemonPath = "/modules/kdeconnect";
const QString DeviceBasePath = "/modules/kdeconnect/devices/";
using DaemonInterface = OrgKdeKdeconnectDaemonInterface;

class KCManagerPrivate
{
public:
    KCManagerPrivate(KCManager *qq);

private:
    KCManager * q_ptr;

    Q_DECLARE_PUBLIC(KCManager)
};

KCManagerPrivate::KCManagerPrivate(KCManager *qq)
    : q_ptr(qq)
{

}

KCManager::KCManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new KCManagerPrivate(this))
{
    // TODO: check if this dbus exist and do the following stuff once kdeconnect dbus is valid to use.
    // https://stackoverflow.com/questions/1423739/waiting-for-a-dbus-service-to-be-available-in-qt
    DaemonInterface daemonIface(KCDBUS_SERVICE, DaemonPath, QDBusConnection::sessionBus());

    connect(&daemonIface, &DaemonInterface::announcedNameChanged, this, &KCManager::announcedNameChanged);
    connect(&daemonIface, &DaemonInterface::deviceAdded, this, &KCManager::deviceAdded);
    connect(&daemonIface, &DaemonInterface::deviceRemoved, this, &KCManager::deviceRemoved);
    connect(&daemonIface, &DaemonInterface::deviceVisibilityChanged, this, &KCManager::deviceVisibilityChanged);
    connect(&daemonIface, &DaemonInterface::deviceListChanged, this, &KCManager::deviceListChanged);
}

KCManager::~KCManager()
{

}

QStringList KCManager::devices(bool onlyReachable, bool onlyPaired)
{
    DaemonInterface daemonIface(KCDBUS_SERVICE, DaemonPath, QDBusConnection::sessionBus());

    QDBusPendingReply<QStringList> reply = daemonIface.devices(onlyReachable, onlyPaired);
    reply.waitForFinished();

    return reply.value();
}

KCDevice * KCManager::createDevice(const QString &deviceId, QObject * parent)
{
    return new KCDevice(DeviceBasePath + deviceId, parent);
}
