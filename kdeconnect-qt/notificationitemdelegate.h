#pragma once

#include <QStyledItemDelegate>

enum NotificationItemDataRole {
    NotificationIdRole = Qt::UserRole + 1,
    NotificationTitleRole = Qt::UserRole + 2,
    ApplicationNameRole = Qt::UserRole + 3
};

class NotificationItemDelegate : public QStyledItemDelegate
{
public:
    NotificationItemDelegate(QObject *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
