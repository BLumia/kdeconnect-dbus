#pragma once

#include <QObject>
#include <QDBusError>

class KCDevice;
class KCManagerPrivate;
class KCManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KCManager)

public:
    explicit KCManager(QObject * parent = nullptr);
    ~KCManager();

    static QStringList devices(bool onlyReachable = false, bool onlyPaired = false);
    static KCDevice *createDevice(const QString & deviceId, QObject *parent = nullptr);

signals:
    void announcedNameChanged(const QString &announcedName);
    void deviceAdded(const QString &id);
    void deviceRemoved(const QString &id);
    void deviceVisibilityChanged(const QString &id, bool isVisible);
    void deviceListChanged();
    void pairingRequestsChanged();

private:
    QScopedPointer<KCManagerPrivate> d_ptr;
};
