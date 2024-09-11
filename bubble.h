#ifndef BUBBLE_H
#define BUBBLE_H

#include <QWidget>

namespace Ui {
class Bubble;
}

class Bubble : public QWidget
{
    Q_OBJECT

public:
    explicit Bubble(QWidget *parent = nullptr);
    ~Bubble();   
    void setSelfSend(bool isSelf = true);
    void setMessage(const QString &message);
    // 设置头像，根据路径获取图片。然后设置进去
    void setIcon(const QString &iconPath);
private:
    Ui::Bubble *ui;
    bool m_isSelf;
};

#endif // BUBBLE_H
