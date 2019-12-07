#include <QString>
#include <QtTest>

#include "kcmanager.h"
#include "kcdevice.h"

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
        }
    }
};

QTEST_APPLESS_MAIN(KCDeviceListTest)

#include "tst_devicelist.moc"
