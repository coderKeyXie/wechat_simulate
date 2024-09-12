#ifndef SYSTEMTIPS_H
#define SYSTEMTIPS_H

#include <QWidget>

class QLabel;
class SystemTips : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTips(QWidget *parent = nullptr);
    void initUI();
    void setMessage(const QString &message);
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void onDeleteSystemTips();
private:
    QLabel *m_label;
};

#endif // SYSTEMTIPS_H
