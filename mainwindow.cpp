#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QtDebug>
#include <QFileDialog>
#include <QTimer>
#include <QMediaPlayer>
#include <QPainter>
#include <QThread>
#include <QLayout>
#include <QSpacerItem>

#include "systemtips.h"
#include "bubble.h"
#include "functiontool.h"
#include "showthread.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Wechat");

    ui->functonToolWidget->setVisible(false);// 屏蔽工具栏
    m_scrolltoMax = new QTimer(this);
    m_scrolltoMax->setSingleShot(true);
    m_scrolltoMax->setInterval(100);

    m_showThread = new ShowThread(m_messages);

    ui->messageWidget->layout()->setAlignment(Qt::AlignTop);

    connect(m_showThread, &ShowThread::appendWidget, this , [ = ] (QWidget *widget) {
        widget->show();
        if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();

    });
    connect(m_showThread, &ShowThread::finished, this, [ = ]() {
        ui->configUi->onPlaying(false);
    });

    connect(m_scrolltoMax, &QTimer::timeout, this, [ = ]() {
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->maximumHeight());
    });
    connect(ui->functonToolWidget, &FunctionTool::onAppendImage, this, &MainWindow::onAppendImage);
    connect(ui->functonToolWidget, &FunctionTool::onSettingBG, this, &MainWindow::onSettingBackground);
    connect(ui->functonToolWidget, &FunctionTool::onAppendSystemInfo, this, &MainWindow::onAppendSystemInfo);

    connect(ui->configUi, &ConfigWidget::playMessage, this, &MainWindow::onPlayMessage);
    connect(ui->configUi, &ConfigWidget::stopMessage, this, [ = ] () {
        m_showThread->stop();
        for (QWidget * widget: m_messages) {
            widget->show();
        }
        if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();
    });


    bool isSelfSend = true;
    for (int i = 0; i < 10 ; i++) {

        isSelfSend = !isSelfSend;
        if (isSelfSend)
            onAppendMessage("一二三四五六七八九十十一十二十三十四十五十六This[破涕为笑]你好 is a long text that should automatically wrap to the next line when it reaches the edge of the QLabel. It demonstrates how QLabel can handle word wrapping.", true);
        else onAppendMessage("n你好哈阿斯顿啊实打实的爱上多少啊多少啊的", false);
    }
    ui->messageWidget->resize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_bubbles);
    m_bubbles.clear();
    qDeleteAll(m_systemMessages);
    m_systemMessages.clear();
    if (m_showThread->isRunning()) m_showThread->exit();
    delete m_showThread;
    m_showThread = nullptr;
}

QPixmap MainWindow::createRoundedIcon(const QPixmap &pixmap, int radius)
{
        QPixmap roundedPixmap(pixmap.size());
        roundedPixmap.fill(Qt::transparent);  // 填充透明背景

        QPainter painter(&roundedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        // 创建圆角矩形区域
        QRect rect(0, 0, pixmap.width(), pixmap.height());
        painter.setClipRect(rect);  // 设置绘制区域为图标矩形

        // 绘制圆角矩形
        painter.drawRoundedRect(rect, radius, radius);  // 绘制圆角矩形

        // 绘制原始图标
        painter.drawPixmap(0, 0, pixmap.scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        painter.end();

        return roundedPixmap;

}

void MainWindow::onAppendMessage(const QString &message, bool isSelf)
{
    Bubble * messageBubble = new Bubble();
    messageBubble->setSelfSend(isSelf);
    messageBubble->setMessage(message);
    ui->messageWidget->layout()->addWidget(messageBubble);
    messageBubble->setIcon(m_selfIconFile);
    messageBubble->setIcon(m_youIconFile, false);
    m_bubbles.append(messageBubble);
    m_messages.append(messageBubble);
    connect(messageBubble, &Bubble::onChangeIcon, this, &MainWindow::onSettingHeadIcon);
    connect(messageBubble, &Bubble::onDeleteBubble, this, &MainWindow::onDeleteBubble);
    if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();
}

void MainWindow::onAppendSystemInfo(const QString &systemMessage)
{
    SystemTips *systemLabel = new SystemTips();
    systemLabel->setMessage(systemMessage);
    ui->messageWidget->layout()->addWidget(systemLabel);
    m_messages.append(systemLabel);
    connect(systemLabel, &SystemTips::onDeleteSystemTips, this, &MainWindow::onDeleteSystemInfo);
    m_systemMessages.append(systemLabel);
    if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();

}

void MainWindow::onDeleteSystemInfo()
{
    SystemTips * senderLabel = dynamic_cast<SystemTips *>(sender());
    ui->messageWidget->layout()->removeWidget(senderLabel);
    m_systemMessages.removeAll(senderLabel);
    m_messages.removeOne(senderLabel);

    delete  senderLabel;
    senderLabel = nullptr;
}


void MainWindow::onAppendImage(const QString &imagePath)
{
    Bubble * messageBubble = new Bubble();
    messageBubble->setSelfSend(true);
    ui->messageWidget->layout()->addWidget(messageBubble);

    messageBubble->setImage(imagePath);
    messageBubble->setIcon(m_selfIconFile);
    messageBubble->setIcon(m_youIconFile, false);
    m_bubbles.append(messageBubble);
    m_messages.append(messageBubble);

    connect(messageBubble, &Bubble::onChangeIcon, this, &MainWindow::onSettingHeadIcon);
    connect(messageBubble, &Bubble::onDeleteBubble, this, &MainWindow::onDeleteBubble);
    if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();
}

void MainWindow::onSettingBackground(const QString &imagePath)
{
    ui->scrollArea->setStyleSheet(QString("QScrollArea {border-image: url(%1) 0 0 0 0 stretch stretch;}").arg(imagePath));
}

void MainWindow::onSettingHeadIcon(bool isSelf)
{
    QString fileName = QFileDialog::getOpenFileName( this,
        tr("Open Image File"),
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif);All Files (*)"
    );
    if (fileName.isEmpty()) {
        return;
    }
    if (isSelf) m_selfIconFile = fileName;
    else m_youIconFile =fileName;

    for (auto message: m_bubbles) {
        message->setIcon(fileName, isSelf);
    }
}

void MainWindow::onPlayMessage(int rate)
{
    // 隐藏消息列表中的内容
    for (QWidget *widget: m_messages) {
        widget->hide();
        Bubble * bubbleWidget = dynamic_cast<Bubble *>(widget);
        if (bubbleWidget) {
            bubbleWidget->setRate(rate); // 设置时间间隔
        }

    }
    m_showThread->start();
    ui->configUi->onPlaying(true);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    return false;
}

void MainWindow::on_morePushButton_clicked()
{

}


void MainWindow::on_messageEdit_returnPressed()
{
    if (ui->messageEdit->text().isEmpty()) return;

    onAppendMessage(ui->messageEdit->text());
    ui->messageEdit->clear();
}


void MainWindow::on_addPushButton_clicked()
{
    ui->functonToolWidget->setVisible(!ui->functonToolWidget->isVisible());
    update();
}

void MainWindow::onDeleteBubble()
{
    Bubble *bubble = dynamic_cast<Bubble *>(sender());
    ui->messageWidget->layout()->removeWidget(bubble);
    m_bubbles.removeOne(bubble);
    m_messages.removeOne(bubble);
    delete bubble;
    bubble = nullptr;
}

