#pragma once

#include <QStyledItemDelegate>

class NotificationItemDelegate : public QStyledItemDelegate
{
public:
    NotificationItemDelegate(QObject *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
