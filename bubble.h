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

Q_SIGNALS:
    void onChangeIcon(bool isSelf);

private slots:
    void on_youHeadIcon_clicked();

    void on_myHeadIcon_clicked();
    void changeSender();

private:
    Ui::Bubble *ui;
    bool m_isSelf;
    QString m_youIconFile;
    QString m_selfIconFile;
    bool m_systemInfoTips; // 系统提示
};

#endif // BUBBLE_H
