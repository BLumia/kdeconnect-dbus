#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QStandardItemModel;
class QHBoxLayout;
class QVBoxLayout;
class QListView;
class QStandardItem;
QT_END_NAMESPACE

class KCDevice;
class BatteryWidget;
class NotificationModel;
class DeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceWidget(const QString deviceId, QWidget *parent = nullptr);

signals:

public slots:
    void fetchAllNotifications();
    void updateBatteryWidget();
    void allNotificationsRemoved();
    void notificationPosted(const QString &publicId);
    void notificationRemoved(const QString &publicId);
    void notificationUpdated(const QString &publicId);

private:
    QStandardItem * createNotificationItem(const QString & notificationId);

    KCDevice * m_kcdevice;

    QStandardItemModel * m_notificationModel;

    BatteryWidget * m_batteryWidget;
    QListView * m_notificationListView;
    QHBoxLayout * m_statusBarLayout;
    QVBoxLayout * m_mainLayout;
};

#endif // DEVICEWIDGET_H
