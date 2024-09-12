#include "messagewidget.h"
#include "config.h"

#include <QPainter>
#include <QStyle>
#include <QPaintEvent>
#include <QStyleOption>
#include <QDebug>

MessageWidget::MessageWidget(QWidget *parent)
    : QWidget(parent)
    , m_height(0)
    , m_selfSend(true)
    , m_message("")
{
    this->setMaximumWidth(messageMaxWidth);
}

void MessageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

    // 处理图片类数据
    if (isImage()) {
        int scaled = 1;
        if (m_pixmap.width() > messageMaxWidth || m_pixmap.height() > messageMaxHeight) {
            scaled = qMax(m_pixmap.width() / messageMaxWidth, m_pixmap.height() / messageMaxHeight) * 2;
        }
        QSize newSize = m_pixmap.size() / scaled;
        painter.drawPixmap(0, 0, m_pixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setFixedSize(m_pixmap.size() / scaled);
        return;
    } else if (!isMessage()) {
        return;
    }

    /********* 处理文本数据 *************/

    // 应用qss
    QStyleOption option;
    option.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);


    painter.setPen("#180d0d"); //设置字体颜色为黑色

    // 设置字体和字体大小
    QFont font = QFont("Segoe UI Emoji", 14, QFont::Thin); // 获取当前字体

    painter.setFont(font); // 应用新的字体设置
    QFontMetrics metrics(painter.font());

    int x = messageLeftMargin; // X坐标
    int y = messageTopMargin; // Y坐标
    int maxWidth = messageMaxWidth - 2 * messageLeftMargin; // 最大宽度，留出边距

    // 分割文本并绘制
    QStringList words = m_message.split(" ");
    QString line;
    for (const QString &word : words) {
        QStringList datas = cutLongStrings(word, &metrics);
        for (const QString & subWord: datas) {
            QString textLine = line.isEmpty() ? subWord : line + (datas.size() == 1 ? " " : "") + subWord;
            if (metrics.horizontalAdvance(textLine) > maxWidth) {
                painter.drawText(x, y, line); // 绘制当前行
                line = subWord; // 开始新的一行
                y += metrics.height(); // 增加Y坐标
            } else {
                line = textLine; // 继续添加到当前行
            }
        }
    }
    // 绘制最后一行
    if (!line.isEmpty()) {
        painter.drawText(x, y, line);
    }

    // 设置气泡大小
    if (m_height != y + 10) {
        m_height = y + 10;
        int width = qMin(metrics.horizontalAdvance(m_message) + 2 * messageLeftMargin, messageMaxWidth);
        setFixedSize(qMax(width, messageMinWidth), qMax(m_height, messageMinHeight));
    }
}

void MessageWidget::setMessage(const QString &message)
{
    m_message = message;
    update();
}

void MessageWidget::setImage(const QString &image)
{
    m_pixmap.load(image);
    m_message.clear();
    update();
}

QStringList  MessageWidget::cutLongStrings(const QString &word, QFontMetrics *metrices)
{
    QStringList charList;
    int maxWidth = messageMaxWidth - 2 * messageLeftMargin; // 最大宽度，留出边距
    if (metrices->horizontalAdvance(word) < maxWidth) {
        charList << word;
        return charList;
    }

    // 按每个字符拆分
    for (int i = 0; i < word.length(); ++i) {
        charList << word.mid(i, 1); // 使用 mid() 方法获取每个字符
    }
    return charList;
}

void MessageWidget::setSelfSend(bool isSelf)
{
    m_selfSend = isSelf;
    this->setStyleSheet(isSelf ? "background-color: " + normalWechatColor +  ";border-radius: 6px;" : "background-color:" + whiteWechatColor + ";border-radius: 6px;");
    update();
}

void MessageWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    Q_EMIT onChangeSender();
}

void MessageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
       Q_EMIT onDeleteMessage();
    }
}


