#include "configwidget.h"
#include "ui_configwidget.h"

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget)
{
    ui->setupUi(this);
//    ui->acknowledgementsLabel->setVisible(false);
    connect(ui->stopButton, &QPushButton::clicked, this, &ConfigWidget::stopMessage);
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::onPlaying(bool isPlaying)
{
    ui->playButton->setEnabled(!isPlaying);
    ui->stopButton->setEnabled(isPlaying);
}


void ConfigWidget::on_playButton_clicked()
{
    int rate = ui->rateSpinBox->value();
    Q_EMIT playMessage(rate);
}

