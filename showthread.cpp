#include "showthread.h"
#include "bubble.h"

#include <QDebug>
#include <QTimer>
ShowThread::ShowThread(const QList<QWidget *> &widges, QObject *parent)
    : m_widgets(widges)
    , QThread(parent)
    , m_isRun(true)
{
    m_appendTimer = new QTimer(this);
}

void ShowThread::run() {
    m_isRun = true;
    // 模拟耗时操作
    for (QWidget *widget : m_widgets) {
        if (!m_isRun) break;
        Bubble * bubbleWidget = dynamic_cast<Bubble *>(widget);
        if (bubbleWidget) {
            int timerout = bubbleWidget->messageShowTimer();
            if (m_isRun) {
                Q_EMIT appendWidget(widget);
                msleep(timerout);
            }
        } else {
            Q_EMIT appendWidget(widget);
        }
    }
    Q_EMIT finished();
}

void ShowThread::stop()
{
    m_isRun = false;
}
