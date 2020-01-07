#pragma once

#include <QObject>
#include <QDBusError>

class KCNotification;
class KCDevicePrivate;
class KCDevice : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KCDevice)

    Q_PROPERTY(QString type READ type CONSTANT FINAL)
    Q_PROPERTY(QString name READ name CONSTANT FINAL)

public:
    enum KCCommonPlugins {
        Unknown = 0,
        KCBattery, // kdeconnect_battery
        KCClipboard, // kdeconnect_clipboard
        KCFindMyPhone, // kdeconnect_findmyphone
        KCMousePad, // kdeconnect_mousepad
        KCMprisControl, // kdeconnect_mpriscontrol
        KCNotifications, // kdeconnect_notifications
        KCPing, // kdeconnect_ping
        KCRemoteKeyboard, // kdeconnect_remotekeyboard
        KCRunCommand, // kdeconnect_runcommand
        KCSftp, // kdeconnect_sftp
        KCShare, // kdeconnect_share
        KCTelephony // kdeconnect_telephony
    };
    Q_ENUM(KCCommonPlugins)

    explicit KCDevice(const QString & deviceId, QObject * parent = nullptr);
    ~KCDevice();

    bool isValid() const;

    // properties
    QString type() const;
    QString name() const;
    QString statusIconName() const;
    bool isReachable() const;
    bool isTrusted() const;
    QStringList supportedPlugins() const;
    bool hasPairingRequest() const;

    // methods
    void acceptPairing() const;
    void rejectPairing() const;
    bool hasPlugin(const QString & pluginName) const;
    bool hasPlugin(KCCommonPlugins pluginType) const;
    bool requestPair() const;
    bool unpair() const;

    // battery (plugin name: kdeconnect_battery)
    int charge() const;
    bool isCharging() const;

    // notifications (plugin name: kdeconnect_notifications)
    QStringList activeNotifications() const;
    void sendReply(const QString &replyId, const QString &message);
    KCNotification * createNotification(const QString &notificationId, QObject * parent = nullptr);

    // helper
    static QString pluginTypeToName(KCCommonPlugins pluginType);
    static KCCommonPlugins pluginNameToType(QString pluginName);

signals:
    void hasPairingRequestsChanged(bool hasPairingRequests);
    void nameChanged(const QString &name);
    void pairingError(const QString &error);
    void pluginsChanged();
    void reachableChanged(bool reachable);
    void trustedChanged(bool trusted);

    // battery
    void chargeChanged(int charge);
    void chargeStateChanged(bool charging);

    // notifications
    void allNotificationsRemoved();
    void notificationPosted(const QString &publicId);
    void notificationRemoved(const QString &publicId);
    void notificationUpdated(const QString &publicId);

protected:

private:
    QScopedPointer<KCDevicePrivate> d_ptr;

    friend class KCManager;
};
