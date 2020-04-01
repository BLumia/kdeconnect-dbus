#pragma once

#include <QPushButton>

class BatteryWidget : public QPushButton
{
    Q_OBJECT
public:
    BatteryWidget(QWidget *parent = nullptr);
    ~BatteryWidget() override;

    void setChargeState(bool charged);
    void setBatteryPower(int power /* 0 to 100 */);

private:
    QString iconName();
    void updateIcon();

    bool charged = false;
    int power = 100;
};
