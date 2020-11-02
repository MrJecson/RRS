//-----------------------------------------------------------------------------
//
//      Имитация вентилятра
//      (c) РГУПС, ВЖД 2/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Имитация вентилятра
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 2/09/2019
 */

#include "fan-imitation.h"

#include <QPainter>
#include <QtCore/qmath.h>

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
FanImitation::FanImitation(QSize _size, QWidget* parent)
    : QLabel(parent)
    , angle_(0)
{
    this->resize(_size);
    this->setStyleSheet("border: 1px solid black");

    cpX_ = this->width()/2.0;
    cpY_ = this->height()/2.0;
    r_ = this->height()/2.0 - 2.0;
    base_ = qDegreesToRadians(20.0);

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    draw_();
}



//-----------------------------------------------------------------------------
//  Деструктор
//-----------------------------------------------------------------------------
FanImitation::~FanImitation()
{

}



//-----------------------------------------------------------------------------
//  Установить угол вентилятора
//-----------------------------------------------------------------------------
void FanImitation::setAngle(int angle)
{
    angle_ = angle;

    draw_();
}



//-----------------------------------------------------------------------------
// Нарисовать вентилятор
//-----------------------------------------------------------------------------
void FanImitation::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    paint.setPen(QPen(QColor(Qt::white), 1));
    paint.setBrush(QColor(Qt::green));

    QPolygonF p;
    p << getTriangle_(angle_);
    angle_ += 90;
    p << getTriangle_(angle_);
    angle_ += 90;
    p << getTriangle_(angle_);
    angle_ += 90;
    p << getTriangle_(angle_);

    paint.drawPolygon(p);

    paint.end();
    this->setPixmap(pix);

}



//-----------------------------------------------------------------------------
//  Вернуть полигон треугольника
//-----------------------------------------------------------------------------
QPolygonF FanImitation::getTriangle_(double aDegree)
{
    double aRadian = qDegreesToRadians(aDegree);
    return QPolygonF({QPointF(cpX_ + r_*cos(aRadian - base_),
                              cpY_ + r_*sin(aRadian - base_)),
                      QPointF(cpX_ + r_*cos(aRadian + base_),
                              cpY_ + r_*sin(aRadian + base_)),
                      QPointF(cpX_,
                              cpY_)});
}
