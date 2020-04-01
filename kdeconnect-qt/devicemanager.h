#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

class KCManager;
class DeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = nullptr);

signals:

public slots:

private:
    KCManager * m_manager;
};

#endif // DEVICEMANAGER_H
