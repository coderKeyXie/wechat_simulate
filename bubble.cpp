#include "bubble.h"
#include "ui_bubble.h"
#include "config.h"

#include <QFontMetrics>
#include <QDebug>
#include <QPixmap>

Bubble::Bubble(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bubble)
    , m_systemInfoTips(false)
{
    ui->setupUi(this);
    setSelfSend(true);
    connect(ui->messageWidget, &MessageWidget::onChangeSender, this, &Bubble::changeSender);
}


Bubble::~Bubble()
{
    delete ui;
}

void Bubble::setSelfSend(bool isSelf)
{
    m_isSelf = isSelf;
    ui->mySendIcon->setVisible(m_isSelf);
    ui->myTriangleWidget->setMySend(m_isSelf);
    if (!ui->messageWidget->isImage()) {
        ui->myTriangleWidget->setVisible(m_isSelf);
        ui->youTriangleWidget->setVisible(!m_isSelf);
    }
    ui->youHeadIcon->setVisible(!m_isSelf);
    ui->youTriangleWidget->setMySend(m_isSelf);
    ui->messageWidget->setSelfSend(m_isSelf);
    ui->widget->layout()->setAlignment(ui->messageWidget, isSelf ? Qt::AlignRight : Qt::AlignLeft);
}

void Bubble::setMessage(const QString &message)
{
    ui->messageWidget->setMessage(message);
}

void Bubble::setImage(const QString &imagePath)
{
    ui->messageWidget->setImage(imagePath);
    ui->myTriangleWidget->setVisible(false);
    ui->youTriangleWidget->setVisible(false);
}

void Bubble::setIcon(const QString &iconPath, bool isSelf)
{
    if (iconPath.isEmpty()) return;

    if (isSelf) {
        m_selfIconFile =  iconPath;

        ui->myHeadIcon->setStyleSheet(QString("QPushButton {"
                         "border-image: url(%1) 35 35 35 35 stretch stretch;;"
                         "border-radius: 5px;}").arg(m_selfIconFile));
   } else {
        m_youIconFile = iconPath;
        ui->youHeadIcon->setStyleSheet(QString("QPushButton {"
                         "border-image: url(%1) 35 35 35 35 stretch stretch;;"
                         "border-radius: 5px;}").arg(m_youIconFile));
    }
}

void Bubble::on_youHeadIcon_clicked()
{
    onChangeIcon(false);
}


void Bubble::on_myHeadIcon_clicked()
{
    onChangeIcon(true);
}

void Bubble::changeSender()
{
    setSelfSend(!m_isSelf);
}

