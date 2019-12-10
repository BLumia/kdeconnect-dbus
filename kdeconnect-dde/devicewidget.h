#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QStandardItemModel;
class QHBoxLayout;
class QVBoxLayout;
class QListView;
QT_END_NAMESPACE

class KCDevice;
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

private:
    KCDevice * m_kcdevice;

    QStandardItemModel * m_notificationModel;

    QLabel * m_batteryWidget;
    QListView * m_notificationListView;
    QHBoxLayout * m_statusBarLayout;
    QVBoxLayout * m_mainLayout;
};

#endif // DEVICEWIDGET_H
