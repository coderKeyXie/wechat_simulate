#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QtDebug>

#include "bubble.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Wechat");

    bool isSelfSend = true;
    for (int i = 0; i < 20 ; i++) {
        Bubble *bubbleWidget =  new Bubble();
        bubbleWidget->setSelfSend(isSelfSend);

        isSelfSend = !isSelfSend;
        bubbleWidget->setIcon("/Users/xiehui/Pictures/1");

        if(isSelfSend) {
            bubbleWidget->setMessage("...");
            bubbleWidget->setIcon("/Users/xiehui/Pictures/1");
        }

        else {
            bubbleWidget->setMessage("一二三四五六七八九十十一十二十三十四十五十六This你好 is a long text that should automatically wrap to the next line when it reaches the edge of the QLabel. It demonstrates how QLabel can handle word wrapping.");
            bubbleWidget->setIcon("/Users/xiehui/Pictures/2");
        }ui->messageWidget->layout()->addWidget(bubbleWidget);
    }
    ui->messageWidget->resize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

