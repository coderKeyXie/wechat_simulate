#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Bubble;
class SystemTips;
class ShowThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap createRoundedIcon(const QPixmap &pixmap, int radius);

   void initUI();
public Q_SLOTS:
    // 添加文字数据，mac上支持颜文字
    void onAppendMessage(const QString &message ,bool isSelf = true);
    // 删除气泡，包括message和图片消息
    void onDeleteBubble();
    // 添加系统提示
    void onAppendSystemInfo(const QString &systemMessage);
    // 删除系统提示
    void onDeleteSystemInfo();
    // 添加图片数据
    void onAppendImage(const QString &imagePath);
    // 设置聊天背景
    void onSettingBackground(const QString &imagePath);
    // 设置头像
    void onSettingHeadIcon(bool isSelf);
    // 播放聊天过程
    void onPlayMessage(int rate);
private:
    void titleNameShow(bool isVisible);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_morePushButton_clicked();

    void on_messageEdit_returnPressed();

    void on_addPushButton_clicked();

    void on_titleEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QString m_youIconFile;
    QString m_selfIconFile;
    QList<Bubble *> m_bubbles;
    QList<SystemTips *> m_systemMessages;
    QList<QWidget *> m_messages; // 全部显示的消息列表
    QTimer *m_scrolltoMax; // 滚动到最低下
    ShowThread *m_showThread; // 定时显示滚动条
};
#endif // MAINWINDOW_H
