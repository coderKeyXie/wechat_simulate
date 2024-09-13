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


public Q_SLOTS:
    void onPlaying(bool isPlaying);


Q_SIGNALS:
    void playMessage(int rate);
    void stopMessage();

private slots:
    void on_playButton_clicked();


private:
    Ui::ConfigWidget *ui;
    QString m_selfIcon;
    QString m_youIcon;
    QString m_backgroundImage;

};

#endif // CONFIGWIDGET_H
