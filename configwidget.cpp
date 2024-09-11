#include "configwidget.h"
#include "ui_configwidget.h"

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget)
{
    ui->setupUi(this);
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::on_pushButton_3_clicked()
{

}

void ConfigWidget::on_appendMessagePushButton_clicked()
{
   Q_EMIT messageSend(ui->lineEdit->text());
}

