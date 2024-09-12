#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Bubble;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap createRoundedIcon(const QPixmap &pixmap, int radius);
public Q_SLOTS:
    // 添加文字数据，mac上支持颜文字
    void appendMessage(const QString &message ,bool isSelf = true);
    // 添加图片数据
    void appendImage(const QString &imagePath);
    // 设置聊天背景。聊天背景会从0， 0点开始显示，到聊天窗口大小结束
    void settingBackground(const QString &imagePath);

    void changeIcon(bool isSelf);

private slots:
    void on_morePushButton_clicked();

    void on_messageEdit_returnPressed();

    void on_addPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString m_youIconFile;
    QString m_selfIconFile;
    QList<Bubble *> m_messages;
    QTimer *m_scrolltoMax; // 滚动到最低下
};
#endif // MAINWINDOW_H
