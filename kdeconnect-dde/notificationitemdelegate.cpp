#include "notificationitemdelegate.h"

NotificationItemDelegate::NotificationItemDelegate(QObject *parent)
    : QStyledItemDelegate (parent)
{

}

void NotificationItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::paint(painter, option, index);
}

QSize NotificationItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // [icon] AppName
    // Content content content content,
    // content content content...
    QString contentText = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(option.font);
    int singleLineHeight = fm.boundingRect("^_^").height();
    QRect dummyContentRect = fm.boundingRect(option.rect, Qt::AlignLeft/* | Qt::TextWordWrap*/, contentText);
    if (option.rect.size().expandedTo(dummyContentRect.size()) != option.rect.size()) {
        return QSize(option.rect.width(), singleLineHeight * 3);
    }

    return QStyledItemDelegate::sizeHint(option, index);
}
