#include "verticallabel.h"

#include <QPainter>

<<<<<<< HEAD
VerticalLabel::VerticalLabel(QWidget *parent)
    : QLabel(parent)
{

}

VerticalLabel::VerticalLabel(const QString &text, QWidget *parent)
: QLabel(text, parent)
=======
VerticalLabel::VerticalLabel(QWidget* parent)
    : QLabel(parent)
{
}

VerticalLabel::VerticalLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent)
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
{
}

VerticalLabel::~VerticalLabel()
{
}

void VerticalLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::Dense1Pattern);
<<<<<<< HEAD
    painter.translate(width()/2,height());
    painter.rotate(270);

    painter.drawText(0,0, text());
=======
    painter.translate(width() / 2, height());
    painter.rotate(270);

    painter.drawText(0, 0, text());
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
}

QSize VerticalLabel::minimumSizeHint() const
{
    QSize s = QLabel::minimumSizeHint();
    return QSize(s.height(), s.width());
}

QSize VerticalLabel::sizeHint() const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());
}
