#ifndef SYSTEMTIPS_H
#define SYSTEMTIPS_H

#include <QWidget>


class SystemTips : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTips(QWidget *parent = nullptr);
    void initUI();
    void setMessage();
signals:
private:
    QString m_message;
};

#endif // SYSTEMTIPS_H
