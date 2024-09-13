#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QPixmap>

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void setMessage(const QString &message);
    void setImage(const QString &m_image);
    QStringList cutLongStrings(const QString &word, QFontMetrics *metrices);
    void setSelfSend(bool isSelf);
    bool isMessage() { return !m_message.isEmpty();}
    bool isImage() { return !m_pixmap.isNull(); }
    const QString & message() { return m_message; }

protected:
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void onChangeSender();
    void onDeleteMessage();
    void onHeightChange(int height);

private:
    QString m_message;
    QPixmap m_pixmap;
    int m_height;
    bool m_selfSend;
    bool m_isDelete;

};

#endif // MESSAGEWIDGET_H
