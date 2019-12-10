#include "kcdevice.h"
#include "kcnotification.h"

#include "kcdbuscommon.h"
#include "device_interface.h"
#include "notification_interface.h"

#define PROXY_SIGNAL_QQ(sender, senderClassName, receiverClassName, signalMethodName) \
    qq->connect(sender, &senderClassName::signalMethodName, qq, &receiverClassName::signalMethodName)

using DeviceInterface = OrgKdeKdeconnectDeviceInterface;
using DeviceBatteryInterface = OrgKdeKdeconnectDeviceBatteryInterface;
using DeviceNotificationsInterface = OrgKdeKdeconnectDeviceNotificationsInterface;
using SingleNotificationInterface = OrgKdeKdeconnectDeviceNotificationsNotificationInterface;

class KCDevicePrivate
{
public:
    KCDevicePrivate(const QString & deviceId, KCDevice *qq);

    QString deviceId;
    QString dbusPath;
    DeviceInterface * dbus;
    DeviceBatteryInterface * batteryDBus;
    DeviceNotificationsInterface * notificationDBus;

private:
    KCDevice * q_ptr;

    Q_DECLARE_PUBLIC(KCDevice)
};

KCDevicePrivate::KCDevicePrivate(const QString &deviceId, KCDevice *qq)
    : deviceId(deviceId)
    , dbusPath(QString(KCDBUS_DEVICE_BASE_PATH).arg(deviceId))
    , dbus(new DeviceInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , batteryDBus(new DeviceBatteryInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , notificationDBus(new DeviceNotificationsInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
    , q_ptr(qq)
{
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, hasPairingRequestsChanged);
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, nameChanged);
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, pairingError);
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, pluginsChanged);
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, reachableChanged);
    PROXY_SIGNAL_QQ(dbus, DeviceInterface, KCDevice, trustedChanged);

    PROXY_SIGNAL_QQ(batteryDBus, DeviceBatteryInterface, KCDevice, chargeChanged);

    // notifications
    PROXY_SIGNAL_QQ(notificationDBus, DeviceNotificationsInterface, KCDevice, allNotificationsRemoved);
    PROXY_SIGNAL_QQ(notificationDBus, DeviceNotificationsInterface, KCDevice, notificationPosted);
    PROXY_SIGNAL_QQ(notificationDBus, DeviceNotificationsInterface, KCDevice, notificationRemoved);
    PROXY_SIGNAL_QQ(notificationDBus, DeviceNotificationsInterface, KCDevice, notificationUpdated);
}

KCDevice::KCDevice(const QString &deviceId, QObject *parent)
    : QObject (parent)
    , d_ptr(new KCDevicePrivate(deviceId, this))
{

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

void KCDevice::sendReply(const QString &replyId, const QString &message)
{
    Q_D(const KCDevice);

    if (hasPlugin(KCNotifications)) {
        QDBusPendingReply<QStringList> reply = d->notificationDBus->sendReply(replyId, message);
        reply.waitForFinished();

        return;
    }
}

KCNotification *KCDevice::createNotification(const QString &notificationId, QObject *parent)
{
    Q_D(KCDevice);

    return new KCNotification(d->deviceId, notificationId, parent);
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

    return QString();
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
