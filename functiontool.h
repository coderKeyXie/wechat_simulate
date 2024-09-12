#ifndef FUNCTIONTOOL_H
#define FUNCTIONTOOL_H

#include <QWidget>

namespace Ui {
class FunctionTool;
}

class FunctionTool : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionTool(QWidget *parent = nullptr);
    ~FunctionTool();

Q_SIGNALS:
    void onAppendImage(const QString &imagePath);
    void onSettingBG(const QString &imagePath);
private slots:

    void on_photoPushButton_clicked();

    void on_backgroundSettingButton_clicked();

private:
    Ui::FunctionTool *ui;
};

#endif // FUNCTIONTOOL_H