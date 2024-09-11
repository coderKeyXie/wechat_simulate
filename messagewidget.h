#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void setMessage(const QString &message);
    QStringList cutLongStrings(const QString &word, QFontMetrics *metrices);
    void setSelfSend(bool isSelf);
signals:

private:
    QString m_message;
    int m_height;
    bool m_selfSend;
};

#endif // MESSAGEWIDGET_H
