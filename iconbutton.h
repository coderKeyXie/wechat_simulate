#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * event) override;
    void setIcon(QPixmap *pixmap) {m_pixmap = pixmap;}
signals:

private:
    QPixmap *m_pixmap;
};

#endif // ICONBUTTON_H
