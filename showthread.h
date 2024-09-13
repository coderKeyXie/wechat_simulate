#ifndef SHOWTHREAD_H
#define SHOWTHREAD_H

#include <QWidget>
#include <QList>
#include <QThread>
class ShowThread : public QThread
{
        Q_OBJECT
public:
    ShowThread(const QList<QWidget *> &widges, QObject *parent = nullptr);
    void run() override;
    void stop();
signals:
    void appendWidget(QWidget *widget);// 显示窗口
    void finished();           // 完成信号

private:
   const QList<QWidget *> &m_widgets;
   bool m_isRun;
   QTimer *m_appendTimer;

};

#endif // SHOWTHREAD_H
