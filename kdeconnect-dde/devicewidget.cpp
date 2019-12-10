#include "devicewidget.h"
#include "notificationitemdelegate.h"

#include <QStandardItemModel>
#include <QBoxLayout>
#include <QLabel>
#include <QListView>

#include <kcdevice.h>
#include <kcnotification.h>

DeviceWidget::DeviceWidget(const QString deviceId, QWidget *parent)
    : QWidget(parent)
    , m_kcdevice(new KCDevice(deviceId, this))
    , m_notificationModel(new QStandardItemModel(this))
    , m_batteryWidget(new QLabel("Power: -1%"))
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
    m_notificationListView->setItemDelegate(new NotificationItemDelegate);

    m_mainLayout->addLayout(m_statusBarLayout);
    m_mainLayout->addWidget(m_notificationListView);

    this->setLayout(m_mainLayout);

    connect(m_kcdevice, &KCDevice::chargeChanged, this, &DeviceWidget::updateBatteryWidget);

    updateBatteryWidget();
    fetchAllNotifications();
}

void DeviceWidget::fetchAllNotifications()
{
    QStringList notifications = m_kcdevice->activeNotifications();

    for (const QString & s : notifications) {
        QObject parent;
        KCNotification * notification = m_kcdevice->createNotification(s, &parent);
        QStandardItem * qsa = new QStandardItem(notification->text());
        qsa->setIcon(QIcon(notification->iconPath()));
        m_notificationModel->appendRow(qsa);
    }
}

void DeviceWidget::updateBatteryWidget()
{
    m_batteryWidget->setText(QString("Power: %1%").arg(m_kcdevice->charge()));
}
