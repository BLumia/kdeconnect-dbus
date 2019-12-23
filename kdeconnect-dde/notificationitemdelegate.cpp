#include "notificationitemdelegate.h"

#include <QPainter>

NotificationItemDelegate::NotificationItemDelegate(QObject *parent)
    : QStyledItemDelegate (parent)
{

}

void NotificationItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // save
    painter->save();
    painter->setClipRect(option.rect);

    // 1st line (icon and title)
    QFontMetrics fm(option.font);
    int singleLineHeight = fm.boundingRect("^_^").height();
    int firstLineY = option.rect.top() + 5;
    int secondLineY = firstLineY + singleLineHeight;
    QString contentText = index.data(Qt::DisplayRole).toString();
//    QRect dummyContentRect = fm.boundingRect(option.rect, Qt::AlignLeft/* | Qt::TextWordWrap*/, contentText);
//    bool singleLineContent = (dummyContentRect.height() < singleLineHeight + 5);
    
    // context locations
    QRect iconRect = QRect(option.rect.adjusted(5, 5, 0, 0).topLeft(), QSize(16, 16));
    QRect titleTextRect = QRect(5 + iconRect.width(), firstLineY,
                                  option.rect.width() - iconRect.width() - 5 - 5, singleLineHeight);
    QRect contentTextRect = QRect(5, secondLineY,
                                  option.rect.width() - iconRect.width() - 5 - 5, singleLineHeight/* * (singleLineContent ? 1 : 2)*/);
    
    // draw background here
    QStyledItemDelegate::paint(painter, option, QModelIndex());
    
    // draw icon
    QIcon::Mode mode = QIcon::Normal;
    if (!(option.state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if (option.state & QStyle::State_Selected) {
        mode = QIcon::Selected;
    }
    QIcon::State state = option.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
    opt.icon.paint(painter, iconRect, option.decorationAlignment, mode, state);
//    index.data(Qt::DecorationRole)
//    painter->drawPixmap(iconRect, opt.icon.pixmap(QSize(16, 16)));
//    painter->fillRect(iconRect, Qt::green);
    painter->drawText(titleTextRect, QString("%1 - %2").arg(index.data(NotificationTitleRole).toString(), index.data(ApplicationNameRole).toString()));

    // draw content text
    painter->drawText(contentTextRect, index.data().toString());
    
    // restore
    painter->restore();
    
//    return QStyledItemDelegate::paint(painter, option, index);
}

QSize NotificationItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // [icon] AppName
    // Content content content content,
    // content content content...
    QString contentText = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(option.font);
    int singleLineHeight = fm.boundingRect("^_^").height();
//    QRect dummyContentRect = fm.boundingRect(option.rect, Qt::AlignLeft/* | Qt::TextWordWrap*/, contentText);
//    bool singleLineContent = (dummyContentRect.height() < singleLineHeight + 5);
//    if (option.rect.size().expandedTo(dummyContentRect.size()) != option.rect.size()) {
//        return QSize(option.rect.width(), singleLineHeight * 3 + 5 + 5);
//    }
    return QSize(option.rect.width(), singleLineHeight * 2 + 5 + 5);
//    return QStyledItemDelegate::sizeHint(option, index);
}
