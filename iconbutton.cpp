#include "iconbutton.h"
#include <QPainter>

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent)
    , m_pixmap(nullptr)
{

}

void IconButton::paintEvent(QPaintEvent *event)
{
    if (!m_pixmap) return QPushButton::paintEvent(event);
    int radius = 5;
    Q_UNUSED(event);

           QPainter painter(this);
           painter.setRenderHint(QPainter::Antialiasing);

           // 创建圆角矩形区域
           QRect rect(0, 0, width(), height());
           painter.setClipRect(rect);  // 设置绘制区域为按钮矩形

           // 绘制圆角矩形背景
           painter.setBrush(Qt::white);  // 设置背景颜色
           painter.drawRoundedRect(rect, radius, radius);  // 绘制圆角矩形

           // 绘制圆角图标
           QRect iconRect(0, 0, width(), height());
           painter.drawPixmap(iconRect, m_pixmap->scaled(iconRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
