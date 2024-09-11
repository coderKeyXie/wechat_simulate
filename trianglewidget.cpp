#include "trianglewidget.h"
#include "config.h"

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPolygon>

TriangleWidget::TriangleWidget(QWidget *parent)
    : QWidget(parent)
    , m_sideLength(6)
    , m_isMySend(true)
{

}

void TriangleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

    if (m_isMySend) {
        painter.setPen(QColor(normalWechatColor)); // 设置画笔颜色
        painter.setBrush(QColor(normalWechatColor));
        painter.rotate(30); // 旋转30度
        painter.translate(width() / 4 + 2, height() / 2);
    } else {
        painter.setPen(QColor(whiteWechatColor)); // 设置画笔颜色
        painter.setBrush(QColor(whiteWechatColor));
        painter.rotate(-30); // 旋转-30度
        painter.translate(width() / 2 - 1, height() / 2);
    }

    // 计算三角形的三个顶点
    QPointF p1(0, 0); // 顶点
    QPointF p2(m_sideLength, 0); // 右下角
    QPointF p3(m_sideLength / 2, m_sideLength * (std::sqrt(3) / 2)); // 左下角
    // 绘制三角形
    QPolygonF triangle;
    triangle << p1 << p2 << p3;
    painter.drawPolygon(triangle);

}

void TriangleWidget::setMySend(bool mySend)
{
    m_isMySend = mySend;
    update();
}
