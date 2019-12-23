#include "devicewidget.h"
#include "notificationitemdelegate.h"
#include "batterywidget.h"

#include <QStandardItemModel>
#include <QBoxLayout>
#include <QLabel>
#include <QListView>
#include <QDebug>

#include <kcdevice.h>
#include <kcnotification.h>

DeviceWidget::DeviceWidget(const QString deviceId, QWidget *parent)
    : QWidget(parent)
    , m_kcdevice(new KCDevice(deviceId, this))
    , m_notificationModel(new QStandardItemModel(this))
    , m_batteryWidget(new BatteryWidget)
    , m_notificationListView(new QListView)
    , m_statusBarLayout(new QHBoxLayout)
    , m_mainLayout(new QVBoxLayout)
{
    // nothing here for now....
    setFixedSize(350, 450);

    m_statusBarLayout->addWidget(new QLabel(m_kcdevice->name()));
    m_statusBarLayout->addStretch();
    m_statusBarLayout->addWidget(m_batteryWidget);

    m_notificationListView->setModel(m_notificationModel);
    m_notificationListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_notificationListView->setItemDelegate(new NotificationItemDelegate);

    m_mainLayout->addLayout(m_statusBarLayout);
    m_mainLayout->addWidget(m_notificationListView);

    this->setLayout(m_mainLayout);

    connect(m_kcdevice, &KCDevice::chargeChanged, this, &DeviceWidget::updateBatteryWidget);
    connect(m_kcdevice, &KCDevice::chargeStateChanged, this, &DeviceWidget::updateBatteryWidget);

    connect(m_kcdevice, &KCDevice::allNotificationsRemoved, this, &DeviceWidget::allNotificationsRemoved);
    connect(m_kcdevice, &KCDevice::notificationPosted, this, &DeviceWidget::notificationPosted);
    connect(m_kcdevice, &KCDevice::notificationRemoved, this, &DeviceWidget::notificationRemoved);
    connect(m_kcdevice, &KCDevice::notificationUpdated, this, &DeviceWidget::notificationUpdated);

    updateBatteryWidget();
    fetchAllNotifications();
}

void DeviceWidget::fetchAllNotifications()
{
    QStringList notifications = m_kcdevice->activeNotifications();

    for (const QString & s : notifications) {
        m_notificationModel->appendRow(createNotificationItem(s));
    }
}

void DeviceWidget::updateBatteryWidget()
{
    m_batteryWidget->setBatteryPower(m_kcdevice->charge());
    m_batteryWidget->setChargeState(m_kcdevice->isCharging());
}

void DeviceWidget::allNotificationsRemoved()
{
    qDebug() << "allNotificationsRemoved";
    m_notificationModel->clear();
}

void DeviceWidget::notificationPosted(const QString &publicId)
{
    qDebug() << "notificationPosted" << publicId;
    m_notificationModel->appendRow(createNotificationItem(publicId));
}

void DeviceWidget::notificationRemoved(const QString &publicId)
{
    qDebug() << "notificationRemoved" << publicId;
    for (int i = 0; i < m_notificationModel->rowCount(); i++) {
        QStandardItem * item = m_notificationModel->item(i);
        if (item && item->data(NotificationIdRole).toString() == publicId) {
            m_notificationModel->removeRow(i);
            return;
        }
    }
    qWarning() << "cannot found the notification with id:" << publicId;
}

void DeviceWidget::notificationUpdated(const QString &publicId)
{
    qDebug() << "notificationUpdated" << publicId;
}

QStandardItem *DeviceWidget::createNotificationItem(const QString &notificationId)
{
    QObject parent;
    KCNotification * notification = m_kcdevice->createNotification(notificationId, &parent);
    QStandardItem * qsa = new QStandardItem(notification->text());
    qsa->setIcon(QIcon(notification->iconPath()));
    qsa->setData(notification->notificationId(), NotificationIdRole);
    qsa->setData(notification->title(), NotificationTitleRole);
    qsa->setData(notification->appName(), ApplicationNameRole);
    return qsa;
}
