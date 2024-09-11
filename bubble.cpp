#include "bubble.h"
#include "ui_bubble.h"
#include "config.h"

#include <QFontMetrics>
#include <QDebug>
#include <QPixmap>

Bubble::Bubble(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bubble)
{
    ui->setupUi(this);
    setSelfSend(true);
}


Bubble::~Bubble()
{
    delete ui;
}

void Bubble::setSelfSend(bool isSelf)
{
    m_isSelf = isSelf;
    ui->myTriangleWidget->setVisible(m_isSelf);
    ui->mySendIcon->setVisible(m_isSelf);
    ui->myTriangleWidget->setMySend(m_isSelf);

    ui->youTriangleWidget->setVisible(!m_isSelf);
    ui->youHeadIcon->setVisible(!m_isSelf);
    ui->youTriangleWidget->setMySend(m_isSelf);
    ui->messageWidget->setSelfSend(m_isSelf);
}

void Bubble::setMessage(const QString &message)
{
    ui->messageWidget->setMessage(message);
}

void Bubble::setIcon(const QString &iconPath)
{
//    QPixmap icon = QPixmap(iconPath);
//    ui->myHeadIcon->setPixmap(icon);
    if (m_isSelf)
        ui->myHeadIcon->setStyleSheet(QString("QLabel {"
                         "border-image: url(%1) 35 35 35 35 stretch stretch;;"
                         "border-radius: 5px;" // 设置圆角半径
                         "}").arg(iconPath));
    else
        ui->youHeadIcon->setStyleSheet(QString("QLabel {"
                         "border-image: url(%1) 35 35 35 35 stretch stretch;;"
                         "border-radius: 5px;" // 设置圆角半径
                         "}").arg(iconPath));
}
