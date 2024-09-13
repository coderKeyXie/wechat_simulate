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
    void setImage(const QString &imagePath);
    // 设置头像，根据路径获取图片。然后设置进去
    void setIcon(const QString &iconPath, bool isSelf = true);
    bool isSelf() { return m_isSelf;}
    int messageShowTimer();
    // 设置每秒看几个字
    inline void setRate(int rate) {m_rate = rate;}

Q_SIGNALS:
    void onChangeIcon(bool isSelf);
    void onDeleteBubble();
private slots:
    void on_youHeadIcon_clicked();

    void on_myHeadIcon_clicked();
    void changeSender();

private:
    Ui::Bubble *ui;
    bool m_isSelf;
    QString m_youIconFile;
    QString m_selfIconFile;
    int m_rate;
};

#endif // BUBBLE_H
