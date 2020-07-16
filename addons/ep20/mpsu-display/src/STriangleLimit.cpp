//-----------------------------------------------------------------------------
//
//      Треугольник ограничения шкалы спидометра
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Треугольник ограничения шкалы спидометра
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "STriangleLimit.h"

#include "qmath.h"

#include "CfgReader.h"

//const	QString		STRIANGLELIMITS_CFG = "../cfg/display/STriangleLimits.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
STriangleLimit::STriangleLimit(const QString &config_dir, int _typeTriangle, QWidget *parent )
    : QLabel(parent)
    , SGlobalParams(config_dir + "SGlobalParams.xml")
    , speedVal_(0)
{
    this->resize( parent->size() );

    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    loadCfg_(config_dir + "STriangleLimits.xml", _typeTriangle);

    stepDeg_ = (360.0 - sgp_arcSplitLength)/sgp_maxSpeedScale;

    img_ = QImage( this->size(),
                   QImage::Format_ARGB32_Premultiplied );

}

//-----------------------------------------------------------------------------
//  Установить значение ограничения
//-----------------------------------------------------------------------------
void STriangleLimit::setVal(int speed)
{
    if (speed == 0)
    {
        img_.fill(Qt::transparent);
        return;
    }

    speedVal_ = speed;

    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать треугольник
//-----------------------------------------------------------------------------
void STriangleLimit::draw_()
{
    img_.fill(Qt::transparent);

    QPainter paint(&img_);
    // указываем цвет границы
    paint.setPen(QPen(QColor(colorTriangle_), 1, Qt::SolidLine));
    // указываем цвет заливки
    paint.setBrush(QColor(colorTriangle_));
    // повышаем качество рисовки
    paint.setRenderHint(QPainter::Antialiasing, true);


    double angleInDeg = (360.0-sgp_angleArcEnd) - (sgp_maxSpeedScale - speedVal_)*stepDeg_;

    int otstup = 15;
    double angle = qDegreesToRadians(angleInDeg);
    double fooAngle = qDegreesToRadians(90.0);
            // положение середины основания треугольника
    double  x0  = w_2_  + (w_2_ - otstup+2 - lengthTriangle_)*cos(angle),
            // положение середины основания треугольника
            y0  = h_2_ + (h_2_ - otstup+2 - lengthTriangle_)*sin(angle),
            // длина треугольника
            r  = lengthTriangle_,
            // половина ширины основания треугольника
            r2 = widthTriangle_;


    QPolygonF triangle;
    triangle << QPointF( x0 + r*cos(angle),
                         y0 + r*sin(angle) )
             << QPointF( x0 + r2*cos(angle+fooAngle),
                         y0 + r2*sin(angle+fooAngle) )
             << QPointF( x0 + r2*cos(angle-fooAngle),
                         y0 + r2*sin(angle-fooAngle) );


    paint.drawPolygon(triangle);
    paint.end();

    this->setPixmap(QPixmap::fromImage(img_));
}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool STriangleLimit::loadCfg_(QString cfg_path, int typeTriangle)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName("");
        switch (typeTriangle) {
        case typeTriangleLimit::cur:
            sectionName = "STriangleLimit_cur";
            break;
        case typeTriangleLimit::next:
            sectionName = "STriangleLimit_next";
            break;
        case typeTriangleLimit::setpointSpeed:
            sectionName = "STriangleSetpointSpeed";
            break;

        default:
            break;
        }

        // --- параметры треугольника ограничения скорости --- //
        // ширина основания
        if (!cfg.getDouble(sectionName, "widthTriangle", widthTriangle_))
            widthTriangle_ = 6.0;
        // длина
        if (!cfg.getDouble(sectionName, "lengthTriangle", lengthTriangle_))
            lengthTriangle_ = 20.0;
        // цвет
        if (!cfg.getString(sectionName, "colorTriangle", colorTriangle_))
            colorTriangle_ = "#ffffff";

    }
    else
    {
        // Параметры по умолчанию.

        // параметры треугольника ограничения скорости
        widthTriangle_ = 6.0;       // ширина основания
        lengthTriangle_ = 20.0;     // длина
        colorTriangle_ = "#ffffff"; // цвет


    }

    return true;
}
