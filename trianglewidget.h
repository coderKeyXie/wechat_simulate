#ifndef TRIANGLEWIDGET_H
#define TRIANGLEWIDGET_H

#include <QWidget>


class TriangleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TriangleWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * event) override;
    void setMySend(bool mySend);

    bool isMySend(){ return m_isMySend; }
signals:

private:
    int m_sideLength;
    bool m_isMySend; // 是否是本人发送的，确定颜色和方向
};

#endif // TRIANGLEWIDGET_H
