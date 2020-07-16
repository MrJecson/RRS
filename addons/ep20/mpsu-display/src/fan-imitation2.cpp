//-----------------------------------------------------------------------------
//
//      Имитация вентилятра
//      (c) РГУПС, ВЖД 24/10/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Имитация вентилятра
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 24/10/2019
 */

#include "fan-imitation2.h"

#include <QPainter>
#include <QtCore/qmath.h>

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
FanImitation2::FanImitation2(int _size, int stepAngle, int cOtstup, QWidget* parent)
    : QLabel(parent)
    , state_(false)
    , angle_(0)
    , speed_(0.0)
    , stepAngle_(stepAngle)
    , cOtstip_(cOtstup)
{
    this->resize(_size, _size);

    timer_ = new QTimer();
    timer_->setInterval(200);
    connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));

    //
    cpX_ = this->width()/2.0;
    cpY_ = this->height()/2.0;
    r_ = this->width()/2.0 - 2.0;
    r2_ = cpX_ - cOtstip_ - 2.0;
    base_ = qDegreesToRadians(8.0);
    base_ = 2.0;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    draw_();
}



//-----------------------------------------------------------------------------
//  Деструктор
//-----------------------------------------------------------------------------
FanImitation2::~FanImitation2()
{
    timer_->stop();
}



//-----------------------------------------------------------------------------
//  Установить состояние вентилятора
//-----------------------------------------------------------------------------
void FanImitation2::setState(FanStateEnum state)
{
    switch (state)
    {
    case FanStateEnum::fsOn :
    case FanStateEnum::fsOff :
        state_ = true;
        timer_->start();
        break;

    case FanStateEnum::fsDefect :
        state_ = false;
        break;
    }
}



//-----------------------------------------------------------------------------
//  Установить скорость вращения вентилятора
//-----------------------------------------------------------------------------
void FanImitation2::setSpeed(double val)
{
    speed_ = val;
}



//-----------------------------------------------------------------------------
//  Процесс вращения вентилятора
//-----------------------------------------------------------------------------
void FanImitation2::onTimer()
{
    if (!state_)
        timer_->stop();

    timer_->setInterval(speed_*10);     // подобрать значения.
    angle_ += static_cast<int>(speed_); // подобрать значения.

    draw_();
}



//-----------------------------------------------------------------------------
// Нарисовать вентилятор
//-----------------------------------------------------------------------------
void FanImitation2::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    QColor colorLine((state_) ? ("#a1e8e8") : ("#ff0000"));
    paint.setBrush(QColor(colorLine));

    //
    paint.setPen(QPen(QColor(Qt::white), 1));

    //
    paint.drawArc(0, 1, this->width()-2, this->height()-2, 0*16, 360*16);

    //
    paint.setPen(QPen(colorLine, 1));

    //
    paint.drawArc(cpX_ - cOtstip_, cpY_ - cOtstip_,
                  cOtstip_*2, cOtstip_*2, 0*16, 360*16);


    QPolygonF p;
    //
    for (int i = 0; i < 360/stepAngle_; ++i)
    {
        if (stepAngle_ == 90)
            p << getTriangle_(angle_);
        else
            paint.drawLine(getLine_(angle_));
        angle_ += stepAngle_;
    }

    //
    if (stepAngle_ == 90)
        paint.drawPolygon(p);


    paint.end();
    this->setPixmap(pix);
}



//-----------------------------------------------------------------------------
//  Вернуть полигон треугольника
//-----------------------------------------------------------------------------
QPolygonF FanImitation2::getTriangle_(double aDegree)
{
    double aRadian = qDegreesToRadians(aDegree);
    double foo   = qDegreesToRadians(90.0);
    return QPolygonF({QPointF(cpX_ + base_*cos(aRadian + foo),
                              cpY_ + base_*sin(aRadian + foo)),
                      QPointF(cpX_ + r_*cos(aRadian),
                              cpY_ + r_*sin(aRadian)),
                      QPointF(cpX_ + base_*cos(aRadian - foo),
                              cpY_ + base_*sin(aRadian - foo))});
}



//-----------------------------------------------------------------------------
//  Вернуть линию-вентиль вентилятора
//-----------------------------------------------------------------------------
QLineF FanImitation2::getLine_(double aDegree)
{
    double aRadian = qDegreesToRadians(aDegree);
    return QLineF(cpX_ + cOtstip_*cos(aRadian),
                  cpY_ + cOtstip_*sin(aRadian),
                  cpX_ + (cOtstip_ + r2_)*cos(aRadian),
                  cpY_ + (cOtstip_ + r2_)*sin(aRadian));
}
