#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QtDebug>
#include <QFileDialog>
#include <QTimer>
#include <QPainter>

#include "bubble.h"
#include "functiontool.h"

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
    connect(m_scrolltoMax, &QTimer::timeout, this, [ = ]() {
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->maximumHeight());
    });
    connect(ui->functonToolWidget, &FunctionTool::onAppendImage, this, &MainWindow::appendImage);
    connect(ui->functonToolWidget, &FunctionTool::onSettingBG, this, &MainWindow::settingBackground);

    connect(ui->configUi, &ConfigWidget::messageSend, this, &MainWindow::appendMessage);
    bool isSelfSend = true;
    for (int i = 0; i < 50 ; i++) {

        isSelfSend = !isSelfSend;

        appendMessage("一二三四五六七八九十十一十二十三十四十五十六This[破涕为笑]你好 is a long text that should automatically wrap to the next line when it reaches the edge of the QLabel. It demonstrates how QLabel can handle word wrapping.", isSelfSend);
    }
    ui->messageWidget->resize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::appendMessage(const QString &message, bool isSelf)
{
    Bubble * messageBubble = new Bubble();
    messageBubble->setSelfSend(isSelf);
    messageBubble->setMessage(message);
    ui->messageWidget->layout()->addWidget(messageBubble);
    messageBubble->setIcon(m_selfIconFile);
    messageBubble->setIcon(m_youIconFile, false);
    m_messages.append(messageBubble);
    connect(messageBubble, &Bubble::onChangeIcon, this, &MainWindow::changeIcon);
    if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();
}

void MainWindow::appendImage(const QString &imagePath)
{
    Bubble * messageBubble = new Bubble();
    messageBubble->setSelfSend(true);
    ui->messageWidget->layout()->addWidget(messageBubble);

    messageBubble->setImage(imagePath);
    messageBubble->setIcon(m_selfIconFile);
    messageBubble->setIcon(m_youIconFile, false);
    m_messages.append(messageBubble);
    connect(messageBubble, &Bubble::onChangeIcon, this, &MainWindow::changeIcon);
    if (!m_scrolltoMax->isActive()) m_scrolltoMax->start();
}

void MainWindow::settingBackground(const QString &imagePath)
{
    ui->scrollArea->setStyleSheet(QString("QScrollArea {border-image: url(%1) 0 0 0 0 stretch stretch;}").arg(imagePath));
}

void MainWindow::changeIcon(bool isSelf)
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

    for (auto message: m_messages) {
//        if (message->isSelf() != isSelf) continue;

        message->setIcon(fileName, isSelf);
    }
}


void MainWindow::on_morePushButton_clicked()
{

}


void MainWindow::on_messageEdit_returnPressed()
{
    if (ui->messageEdit->text().isEmpty()) return;

    appendMessage(ui->messageEdit->text());
    ui->messageEdit->clear();
}


void MainWindow::on_addPushButton_clicked()
{
    ui->functonToolWidget->setVisible(!ui->functonToolWidget->isVisible());
    update();
}

