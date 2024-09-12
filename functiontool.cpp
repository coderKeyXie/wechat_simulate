#include "functiontool.h"
#include "ui_functiontool.h"
#include <QFileDialog>

FunctionTool::FunctionTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionTool)
{
    ui->setupUi(this);
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
}

