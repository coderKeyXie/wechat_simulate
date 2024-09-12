#include "systemtips.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

SystemTips::SystemTips(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void SystemTips::initUI()
{
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);
    mainLayout->setMargin(0);
    this->setFixedHeight(15);
    m_label = new QLabel(this);
    m_label->setStyleSheet("QLabel {"
    "color: #686868;"
    "font-size: 12px;"
    "}");
    m_label->setFixedHeight(15);
    m_label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_label);
}

void SystemTips::setMessage(const QString &message)
{
    m_label->setText(message);
}

void SystemTips::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        Q_EMIT onDeleteSystemTips();
    }
}
