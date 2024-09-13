#include "functiontool.h"
#include "ui_functiontool.h"
#include <QFileDialog>

FunctionTool::FunctionTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionTool)
{
    ui->setupUi(this);
    ui->dataEdit->setVisible(false);
}

FunctionTool::~FunctionTool()
{
    delete ui;
}

void FunctionTool::on_photoPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this,
        tr("Open Image File"),
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif);All Files (*)"
    );
    if (fileName.isEmpty()) {
        return;
    }

    Q_EMIT onAppendImage(fileName);
    this->setVisible(false);
}


void FunctionTool::on_backgroundSettingButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName( this,
        tr("Open Image File"),
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif);All Files (*)"
    );
    if (fileName.isEmpty()) {
        return;
    }

    Q_EMIT onSettingBG(fileName);
    this->setVisible(false);
}


void FunctionTool::on_systemInfoButton_clicked()
{
    ui->dataEdit->setVisible(true);
    ui->dataEdit->setFocus();
}

void FunctionTool::on_dataEdit_returnPressed()
{
    Q_EMIT onAppendSystemInfo(ui->dataEdit->text());
    ui->dataEdit->clear();
    ui->dataEdit->setVisible(false);
    this->setVisible(false);
}

