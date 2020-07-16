//-----------------------------------------------------------------------------
//
//      Шкала тяги
//      (c) РГУПС, ВЖД 14/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Шкала тяги
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 14/08/2019
 */

#include "scale-traction.h"

#include <QPainter>


//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
ScaleTraction::ScaleTraction(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);

    this->setStyleSheet("border: 1px solid black");

//    this->setAutoFillBackground(true);
//    this->setPalette(QPalette(QColor(Qt::black)));

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать шкалу
//-----------------------------------------------------------------------------
void ScaleTraction::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    //
    paint.setFont(QFont("Arial", 12, QFont::Medium));
    paint.setPen(QPen(QColor(Qt::white), 3, Qt::SolidLine));
    // вертикальная линия
    paint.drawLine(this->width()/2.0, 10,
                   this->width()/2.0, this->height() - 16);

    int foo1 = 34;
    double horizontalLinesH = this->height()*0.78;
    double fooStep = horizontalLinesH / 8;
    int fooDigitLeft = 100;
    int fooDigitRight = 350;

    // горизонтальные линии
    for (int i = 0; i < 9; ++i)
    {
        paint.drawLine(40, foo1 + fooStep*i,
                       this->width() - 40, foo1 + fooStep*i);
        paint.setPen(QPen(QColor(Qt::white), 3, Qt::SolidLine));
        if (i % 2 == 0)
        {
            QString fooTextLeft = QString::number(fooDigitLeft);
            QString fooTextRight = QString::number(fooDigitRight);
            paint.drawText(20 - 4*fooTextLeft.size(), foo1 + fooStep * i + 5, fooTextLeft);
            paint.drawText(this->width() - 22 - 4*fooTextRight.size(),
                           foo1 + fooStep * i + 5, fooTextRight);
            fooDigitLeft -= 50;
            fooDigitRight -= 175;
            if (fooDigitRight <= 0)
                fooDigitRight = 0;

            paint.setPen(QPen(QColor(Qt::white), 2, Qt::SolidLine));
        }
    }

    //
    paint.setFont(QFont("Arial", 14, QFont::DemiBold));
    paint.drawText(QPoint(14, 21), "%");
    paint.drawText(QPoint(this->width() - 35, 21), "кН");

    paint.end();

    this->setPixmap(pix);
}
