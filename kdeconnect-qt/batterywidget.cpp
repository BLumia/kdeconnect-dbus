#include "batterywidget.h"

#include <QPainter>
#include <QApplication>

BatteryWidget::BatteryWidget(QWidget *parent)
    : QPushButton (parent)
{
    setFlat(true);
    setFocusPolicy(Qt::NoFocus);
    setCheckable(false);

    updateIcon();
}

BatteryWidget::~BatteryWidget()
{
    //
}

void BatteryWidget::setChargeState(bool charged)
{
    this->charged = charged;
    updateIcon();
}

void BatteryWidget::setBatteryPower(int power)
{
    this->power = power;
    updateIcon();
}

QString BatteryWidget::iconName()
{
    QString percentageStr;

    if (power < 20 && power >= 0) {
        percentageStr = "000";
    } else if (power < 40) {
        percentageStr = "020";
    } else if (power < 50) {
        percentageStr = "040";
    } else if (power < 70) {
        percentageStr = "060";
    } else if (power < 90) {
        percentageStr = "080";
    } else if (power <= 100){
        percentageStr = "100";
    } else {
        percentageStr = "000";
    }

    return QString("battery-%1-%2").arg(percentageStr, charged ? "plugged-symbolic" : "symbolic");
}

void BatteryWidget::updateIcon()
{
    setIcon(QIcon::fromTheme(iconName()));
    setText(QString("%1%").arg(power));
}
