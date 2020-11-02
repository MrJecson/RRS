//-----------------------------------------------------------------------------
//
//      Стрелка спидометра
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Стрелка спидометра
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "SArrow.h"

#include <QtCore/qmath.h>

#include "CfgReader.h"

//const	QString		SARROW_CFG = "../cfg/display/SArrow.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SArrow::SArrow(const QString &config_dir, QWidget *parent)
    : QLabel(parent), SGlobalParams(config_dir + "SGlobalParams.xml")
    , speedVal_(0.0)
{
    this->resize(parent->size());
    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    loadCfg_(config_dir);

    stepDeg_ = (360.0 - sgp_arcSplitLength)/sgp_maxSpeedScale;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    draw_();
}

//-----------------------------------------------------------------------------
//  Установить стрелку
//-----------------------------------------------------------------------------
void SArrow::setVal(double speedValue, QString color)
{
    this->speedVal_ = speedValue;
    this->color_ = color;

    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать стрелку
//-----------------------------------------------------------------------------
void SArrow::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    double angleInDeg = (360.0-sgp_angleArcEnd) - (sgp_maxSpeedScale - speedVal_)*stepDeg_;

    double angle = qDegreesToRadians(angleInDeg);
    double foo   = qDegreesToRadians(90.0);

    paint.setPen(QPen(QColor(color_), 1, Qt::SolidLine));
    paint.setBrush(QColor(color_));

//    QPolygonF triangle;
//    triangle << QPointF( w_2_ + (w_2_*koefLength_)*cos(angle),
//                         h_2_ + (h_2_*koefLength_)*sin(angle) )
//             << QPointF( w_2_ + widthBase_*cos(angle+foo),
//                         h_2_ + widthBase_*sin(angle+foo) )
//             << QPointF( w_2_ + widthBase_*cos(angle-foo),
//                         h_2_ + widthBase_*sin(angle-foo) );

//    paint.drawPolygon(triangle);


    paint.setPen(QPen(QColor(color_), 3, Qt::SolidLine, Qt::RoundCap));
    paint.drawLine(w_2_,
                   h_2_,
                   w_2_ + (w_2_*koefLength_)*cos(angle),
                   h_2_ + (h_2_*koefLength_)*sin(angle));

    paint.end();
    this->setPixmap(pix);

}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool SArrow::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName = "SArrow";

        // коэфициент длины стрелки (от ширины спидометра)
        if (!cfg.getDouble(sectionName, "koef_length", koefLength_))
            koefLength_ = 0.8;
        // ширина основания стрелки
        if (!cfg.getDouble(sectionName, "widthBase", widthBase_))
            widthBase_ = 6.0;
        // цвет стрелки спидометра
        if (!cfg.getString(sectionName, "color", color_))
            color_ = "#ffffff";

    }
    else
    {
        // Параметры по умолчанию.
        koefLength_ = 0.8;  // коэфициент длины стрелки (от ширины спидометра)
        widthBase_ = 6.0;   // ширина основания стрелки
        color_ = "#ffffff"; // цвет стрелки спидометра

    }

    return true;
}


