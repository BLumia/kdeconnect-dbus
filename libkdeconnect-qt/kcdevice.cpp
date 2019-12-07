#include "kcdevice.h"

#include "kcdbuscommon.h"
#include "device_interface.h"

using DeviceInterface = OrgKdeKdeconnectDeviceInterface;
using DeviceBatteryInterface = OrgKdeKdeconnectDeviceBatteryInterface;
using DeviceNotificationsInterface = OrgKdeKdeconnectDeviceNotificationsInterface;

class KCDevicePrivate
{
public:
    KCDevicePrivate(const QString & dbusPath, KCDevice *qq);

    QString dbusPath;
    DeviceInterface * dbus;
    DeviceBatteryInterface * batteryDBus;
    DeviceNotificationsInterface * notificationDBus;

private:
    KCDevice * q_ptr;

    Q_DECLARE_PUBLIC(KCDevice)
};

KCDevicePrivate::KCDevicePrivate(const QString &dbusPath, KCDevice *qq)
    : dbusPath(dbusPath)
    , dbus(new DeviceInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , batteryDBus(new DeviceBatteryInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , notificationDBus(new DeviceNotificationsInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , q_ptr(qq)
{
    qq->connect(dbus, &DeviceInterface::hasPairingRequestsChanged, qq, &KCDevice::hasPairingRequestsChanged);
    qq->connect(dbus, &DeviceInterface::nameChanged, qq, &KCDevice::nameChanged);
    qq->connect(dbus, &DeviceInterface::pairingError, qq, &KCDevice::pairingError);
    qq->connect(dbus, &DeviceInterface::pluginsChanged, qq, &KCDevice::pluginsChanged);
    qq->connect(dbus, &DeviceInterface::reachableChanged, qq, &KCDevice::reachableChanged);
    qq->connect(dbus, &DeviceInterface::trustedChanged, qq, &KCDevice::trustedChanged);
}

KCDevice::~KCDevice()
{

}

bool KCDevice::isValid() const
{
    Q_D(const KCDevice);

    return d->dbus->isValid();
}

QString KCDevice::type() const
{
    Q_D(const KCDevice);

    return d->dbus->type();
}

QString KCDevice::name() const
{
    Q_D(const KCDevice);

    return d->dbus->name();
}

QString KCDevice::statusIconName() const
{
    Q_D(const KCDevice);

    return d->dbus->statusIconName();
}

bool KCDevice::isReachable() const
{
    Q_D(const KCDevice);

    return d->dbus->isReachable();
}

bool KCDevice::isTrusted() const
{
    Q_D(const KCDevice);

    return d->dbus->isTrusted();
}

QStringList KCDevice::supportedPlugins() const
{
    Q_D(const KCDevice);

    return d->dbus->supportedPlugins();
}

bool KCDevice::hasPairingRequest() const
{
    Q_D(const KCDevice);

    return d->dbus->hasPairingRequests();
}

void KCDevice::acceptPairing() const
{
    Q_D(const KCDevice);

    QDBusPendingReply<void> reply = d->dbus->acceptPairing();
    reply.waitForFinished();
}

void KCDevice::rejectPairing() const
{
    Q_D(const KCDevice);

    QDBusPendingReply<void> reply = d->dbus->rejectPairing();
    reply.waitForFinished();
}

bool KCDevice::hasPlugin(const QString &pluginName) const
{
    Q_D(const KCDevice);

    QDBusPendingReply<bool> reply = d->dbus->hasPlugin(pluginName);
    reply.waitForFinished();

    return reply.value();
}

bool KCDevice::hasPlugin(KCDevice::KCCommonPlugins pluginType) const
{
    return hasPlugin(pluginTypeToName(pluginType));
}

int KCDevice::charge() const
{
    Q_D(const KCDevice);

    if (hasPlugin(KCBattery)) {
        QDBusPendingReply<int> reply = d->batteryDBus->charge();
        reply.waitForFinished();

        return reply.value();
    }

    return -1;
}

bool KCDevice::isCharging() const
{
    Q_D(const KCDevice);

    if (hasPlugin(KCBattery)) {
        QDBusPendingReply<bool> reply = d->batteryDBus->isCharging();
        reply.waitForFinished();

        return reply.value();
    }

    return false;
}

QStringList KCDevice::activeNotifications() const
{
    Q_D(const KCDevice);

    if (hasPlugin(KCNotifications)) {
        QDBusPendingReply<QStringList> reply = d->notificationDBus->activeNotifications();
        reply.waitForFinished();

        return reply.value();
    }

    return {};
}

QString KCDevice::pluginTypeToName(KCDevice::KCCommonPlugins pluginType)
{
    switch (pluginType) {
    case Unknown:
        return QString();
    case KCBattery:
        return QStringLiteral("kdeconnect_battery");
    case KCClipboard:
        return QStringLiteral("kdeconnect_clipboard");
    case KCFindMyPhone:
        return QStringLiteral("kdeconnect_findmyphone");
    case KCMousePad:
        return QStringLiteral("kdeconnect_mousepad");
    case KCMprisControl:
        return QStringLiteral("kdeconnect_mpriscontrol");
    case KCNotifications:
        return QStringLiteral("kdeconnect_notifications");
    case KCPing:
        return QStringLiteral("kdeconnect_ping");
    case KCRemoteKeyboard:
        return QStringLiteral("kdeconnect_remotekeyboard");
    case KCRunCommand:
        return QStringLiteral("kdeconnect_runcommand");
    case KCSftp:
        return QStringLiteral("kdeconnect_sftp");
    case KCShare:
        return QStringLiteral("kdeconnect_share");
    case KCTelephony:
        return QStringLiteral("kdeconnect_telephony");
    }
}

KCDevice::KCCommonPlugins KCDevice::pluginNameToType(QString pluginName)
{
    static QHash<QString, KCCommonPlugins> pluginNameTypeMap = {
        {"kdeconnect_battery", KCBattery},
        {"kdeconnect_clipboard", KCClipboard},
        {"kdeconnect_findmyphone", KCFindMyPhone},
        {"kdeconnect_mousepad", KCMousePad},
        {"kdeconnect_mpriscontrol", KCMprisControl},
        {"kdeconnect_notifications", KCNotifications},
        {"kdeconnect_ping", KCPing},
        {"kdeconnect_remotekeyboard", KCRemoteKeyboard},
        {"kdeconnect_runcommand", KCRunCommand},
        {"kdeconnect_sftp", KCSftp},
        {"kdeconnect_share", KCShare},
        {"kdeconnect_telephony", KCTelephony}
    };

    return pluginNameTypeMap.value(pluginName, Unknown);
}

KCDevice::KCDevice(const QString &dbusPath, QObject *parent)
    : QObject (parent)
    , d_ptr(new KCDevicePrivate(dbusPath, this))
{

}
