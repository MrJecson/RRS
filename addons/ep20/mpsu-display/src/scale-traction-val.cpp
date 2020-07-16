//-----------------------------------------------------------------------------
//
//      Динамические величины на шкале тяги
//      (c) РГУПС, ВЖД 15/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Динамические величины на шкале тяги
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 15/08/2019
 */


#include "scale-traction-val.h"

#include <QPainter>


//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
ScaleTractionVal::ScaleTractionVal(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    draw_(0, 0);
}

//-----------------------------------------------------------------------------
//  Установить значения динамическим элементам
//-----------------------------------------------------------------------------
void ScaleTractionVal::setVal(int setVal, int actualVal)
{
    if (setVal > 100)
        setVal = 100;
    if (setVal < -100)
        setVal = -100;

    if (actualVal > 100)
        actualVal = 100;
    if (actualVal < -100)
        actualVal = -100;

    draw_(setVal, actualVal);
}

//-----------------------------------------------------------------------------
//  Нарисовать динамические элементы
//-----------------------------------------------------------------------------
void ScaleTractionVal::draw_(int setVal, int actualVal)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    //
    int scaleHeightHalf = this->height()*0.78/2.0;
    int setVal_ = -scaleHeightHalf*setVal/100;
    int actualVal_ = -scaleHeightHalf*actualVal/100;

    int startPointH = 34;
    int midH = scaleHeightHalf + startPointH;


    // столбик
    QPolygon polygon;
    polygon << QPoint(65, midH + actualVal_)
            << QPoint(this->width() - 65, midH + actualVal_)
            << QPoint(this->width() - 65, midH)
            << QPoint(65, midH);
    paint.setPen(QColor("#8899f8"));
    paint.setBrush(QColor("#8899f8"));
    paint.drawPolygon(polygon);

    // линия
    paint.setPen(QPen(QColor(Qt::white), 8, Qt::SolidLine, Qt::RoundCap));
    paint.drawLine(40, midH + setVal_,
                   this->width() - 40, midH + setVal_);

    // численные значения
    paint.setFont(QFont("Arial", 12, 87));
    QString foo1 = QString::number(setVal);
    QString foo2 = QString::number((setVal < 0) ? (0) : (350*setVal/100));
    paint.drawText(70 - 4*foo1.size(), midH + setVal_ - 6, foo1);
    paint.drawText(105 - 4*foo2.size(), midH + setVal_ - 6, foo2);

    // численные значения
    paint.setPen(QColor("#8899f8"));
    QString foo3 = QString::number(actualVal);
    QString foo4 = QString::number((setVal < 0) ? (0) : (350*actualVal/100));
    paint.drawText(50 - 4*foo3.size(), midH + actualVal_ + 4, foo3);
    paint.drawText(126 - 4*foo4.size(), midH + actualVal_ + 4, foo4);

    paint.end();

    this->setPixmap(pix);
}
