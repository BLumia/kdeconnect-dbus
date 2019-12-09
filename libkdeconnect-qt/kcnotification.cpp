#include "kcnotification.h"

#include "kcdbuscommon.h"

#include "notification_interface.h"

using NotificationInterface = OrgKdeKdeconnectDeviceNotificationsNotificationInterface;

class KCNotificationPrivate
{
public:
    KCNotificationPrivate(const QString &deviceId, const QString &notificationId, KCNotification *qq);

    QString deviceId;
    QString notificationId;
    QString dbusPath;
    NotificationInterface * dbus;

private:
    KCNotification * q_ptr;

    Q_DECLARE_PUBLIC(KCNotification)
};

KCNotificationPrivate::KCNotificationPrivate(const QString &deviceId, const QString &notificationId, KCNotification *qq)
    : deviceId(deviceId)
    , notificationId(notificationId)
    , dbusPath(QString(KCDBUS_NOTIFICATION_BASE_PATH).arg(deviceId, notificationId))
    , dbus(new NotificationInterface(KCDBUS_SERVICE, dbusPath, QDBusConnection::sessionBus(), qq))
{

}

KCNotification::KCNotification(const QString &deviceId, const QString &notificationId, QObject *parent)
    : QObject(parent)
    , d_ptr(new KCNotificationPrivate(deviceId, notificationId, this))
{

}

KCNotification::~KCNotification()
{

}

bool KCNotification::isValid() const
{
    Q_D(const KCNotification);

    return d->dbus->isValid();
}

QString KCNotification::deviceId() const
{
    Q_D(const KCNotification);

    return d->deviceId;
}

QString KCNotification::notificationId() const
{
    Q_D(const KCNotification);

    return d->notificationId;
}

QString KCNotification::appName() const
{
    Q_D(const KCNotification);

    return d->dbus->appName();
}

bool KCNotification::dismissable() const
{
    Q_D(const KCNotification);

    return d->dbus->dismissable();
}

bool KCNotification::hasIcon() const
{
    Q_D(const KCNotification);

    return d->dbus->hasIcon();
}

QString KCNotification::iconPath() const
{
    Q_D(const KCNotification);

    return d->dbus->iconPath();
}

QString KCNotification::replyId() const
{
    Q_D(const KCNotification);

    return d->dbus->replyId();
}

bool KCNotification::silent() const
{
    Q_D(const KCNotification);

    return d->dbus->silent();
}

QString KCNotification::text() const
{
    Q_D(const KCNotification);

    return d->dbus->text();
}

QString KCNotification::title() const
{
    Q_D(const KCNotification);

    return d->dbus->title();
}

void KCNotification::dismiss() const
{
    Q_D(const KCNotification);

    QDBusPendingReply<void> reply = d->dbus->dismiss();
    reply.waitForFinished();

    return;
}

void KCNotification::reply() const
{
    Q_D(const KCNotification);

    QDBusPendingReply<void> reply = d->dbus->reply();
    reply.waitForFinished();

    return;
}

QString KCNotification::ticker() const
{
    Q_D(const KCNotification);

    return d->dbus->ticker();
}
