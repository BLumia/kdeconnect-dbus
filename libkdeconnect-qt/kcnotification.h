#pragma once

#include <QObject>
#include <QDBusError>

class KCNotificationPrivate;
class KCNotification : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KCNotification)

public:
    explicit KCNotification(const QString & deviceId, const QString & notificationId, QObject * parent = nullptr);
    ~KCNotification();

    bool isValid() const;
    QString deviceId() const;
    QString notificationId() const;

    QString appName() const;
    bool dismissable() const;
    bool hasIcon() const;
    QString iconPath() const;
    QString replyId() const;
    bool silent() const;
    QString text() const;
    QString ticker() const;
    QString title() const;

    void dismiss() const;
    void reply() const;

signals:

private:
    QScopedPointer<KCNotificationPrivate> d_ptr;
};
