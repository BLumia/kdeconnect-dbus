#include <QString>
#include <QtTest>

#include "kcmanager.h"
#include "kcdevice.h"
#include "kcnotification.h"

class KCDeviceListTest : public QObject {
    Q_OBJECT
public:    
    KCDeviceListTest() {}

private Q_SLOTS:
    void testCase_SampleTest() {
        QVERIFY(1 + 1 == 2);
        QStringList devList = KCManager::devices(false, true);
        qDebug() << devList;
        for (auto & devId : devList) {
            auto dev = KCManager::createDevice(devId);
            qDebug() << dev->name() << dev->isValid() << dev->hasPlugin(KCDevice::KCBattery) << dev->charge();
            qDebug() << dev->hasPlugin(KCDevice::KCNotifications) << dev->activeNotifications();
            if (dev->hasPlugin(KCDevice::KCNotifications)) {
                QStringList notifications = dev->activeNotifications();
                for (const QString & notificationId : notifications) {
                    auto n = dev->createNotification(notificationId);
                    qDebug() << n->appName() << n->title() << n->text();
                }
            }
        }
    }
};

QTEST_APPLESS_MAIN(KCDeviceListTest)

#include "tst_devicelist.moc"
