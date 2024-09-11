#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class ConfigWidget;
}

class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(QWidget *parent = nullptr);
    ~ConfigWidget();

private slots:
    void on_pushButton_3_clicked();

    void on_appendMessagePushButton_clicked();

Q_SIGNALS:
    void messageSend(const QString &message, bool isSelf = true);
private:
    Ui::ConfigWidget *ui;
    QString m_selfIcon;
    QString m_youIcon;
    QString m_backgroundImage;

};

#endif // CONFIGWIDGET_H
