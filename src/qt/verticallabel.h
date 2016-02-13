#ifndef VERTICALLABEL_H
#define VERTICALLABEL_H

#include <QLabel>

class VerticalLabel : public QLabel
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit VerticalLabel(QWidget *parent=0);
    explicit VerticalLabel(const QString &text, QWidget *parent=0);
=======
    explicit VerticalLabel(QWidget *parent = 0);
    explicit VerticalLabel(const QString& text, QWidget *parent = 0);
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
    ~VerticalLabel();

protected:
    void paintEvent(QPaintEvent*);
<<<<<<< HEAD
    QSize sizeHint() const ;
=======
    QSize sizeHint() const;
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
    QSize minimumSizeHint() const;
};

#endif // VERTICALLABEL_H
