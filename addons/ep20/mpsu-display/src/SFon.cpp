//-----------------------------------------------------------------------------
//
//      Фоновые элементы спидометра
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Фоновые элементы спидометра
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "SFon.h"
#include <QtCore/qmath.h>

#include "CfgReader.h"

//const	QString		SFON_CFG = "../cfg/display/SFon.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SFon::SFon(const QString &config_dir, QWidget *parent)
    : QLabel(parent), SGlobalParams(config_dir + "SGlobalParams.xml")
{
    this->resize(parent->size());
    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    loadCfg_(config_dir);

    int otstup = 15;
    rect_.setRect( otstup,
                   otstup,
                   this->width()-otstup*2,
                   this->height()-otstup*2 );

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать все элементы
//-----------------------------------------------------------------------------
void SFon::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    drawArc_(paint);
    //drawMidlCircle_(paint);
    drawSpeeds_(paint);

    paint.end();
    this->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//  Нарисовать дугу шкалы
//-----------------------------------------------------------------------------
void SFon::drawArc_(QPainter &paint)
{
    paint.setPen(QPen( QColor(arcScale_color_),
                       arcScale_width_,
                       Qt::SolidLine ));
    paint.drawArc(rect_,
                  sgp_angleArcEnd*16,
                  (360.0 - sgp_arcSplitLength)*16);

}

//-----------------------------------------------------------------------------
//  Нарисовать центральный круг
//-----------------------------------------------------------------------------
void SFon::drawMidlCircle_(QPainter &paint)
{
    paint.setPen(QPen( QColor(centralCircle_color_),
                        centralCircle_diameter_,
                        Qt::SolidLine,
                        Qt::RoundCap ));
    paint.drawPoint( this->width()/2,
                     this->height()/2 );
}

//-----------------------------------------------------------------------------
//  Нарисовать скоростя вокруг дуги шкалы
//-----------------------------------------------------------------------------
void SFon::drawSpeeds_(QPainter &paint)
{
    double rr  = - rect_.x() - speeds_margin_;
    int dx = speeds_radius_dx_; // "для овальности"
    int dy = speeds_radius_dy_; // "для овальности"
    paint.setPen(QPen(QColor(speeds_color_)));
    paint.setFont(QFont("Arial", speeds_fontSize_));

    for (int i = 0, n = sgp_maxSpeedScale/sgp_stepSpeed; i <= n; ++i)
    {
        double angle = (360.0 - sgp_angleArcEnd) - i*((360.0-sgp_arcSplitLength)/n);
        angle = qDegreesToRadians(angle);

        paint.drawText( (w_2_ - 18) + (w_2_ + rr + dx)*cos(angle),
                        (h_2_ + 7) + (h_2_ + rr + dy)*sin(angle),
                        QString::number(sgp_maxSpeedScale - i*sgp_stepSpeed) );
    }
}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool SFon::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName = "SFon";

        // --- дуга шкалы --- //
        // цвет
        if (!cfg.getString(sectionName, "arcScale_color", arcScale_color_))
            arcScale_color_ = "#ffffff";
        // ширина
        if (!cfg.getInt(sectionName, "arcScale_width", arcScale_width_))
            arcScale_width_ = 1;

        // --- центральный круг --- //
        // цвет
        if (!cfg.getString(sectionName, "centralCircle_color", centralCircle_color_))
            centralCircle_color_ = "#0096ff";
        // диаметр
        if (!cfg.getInt(sectionName, "centralCircle_diameter", centralCircle_diameter_))
            centralCircle_diameter_ = 100;

        // --- скоростя вокруг дуги шкалы --- //
        // цвет
        if (!cfg.getString(sectionName, "speeds_color", speeds_color_))
            speeds_color_ = "#ffffff";
        // размер шрифта
        if (!cfg.getInt(sectionName, "speeds_fontSize", speeds_fontSize_))
            speeds_fontSize_ = 18;
        // отступ от дуги шкалы
        if (!cfg.getInt(sectionName, "speeds_margin", speeds_margin_))
            speeds_margin_ = 50;
        // довесок к радиусу по оси OX
        if (!cfg.getInt(sectionName, "speeds_radius_dx", speeds_radius_dx_))
            speeds_radius_dx_ = 0;
        // довесок к радиусу по оси OY
        if (!cfg.getInt(sectionName, "speeds_radius_dy", speeds_radius_dy_))
            speeds_radius_dy_ = 10;

    }
    else
    {
        // Параметры по умолчанию.
        // дуга шкалы
        arcScale_color_ = "#ffffff";    // цвет
        arcScale_width_ = 1;            // ширина

        // центральный круг
        centralCircle_color_ = "#0096ff";   // цвет
        centralCircle_diameter_ = 100;      // диаметр

        // скоростя вокруг дуги шкалы
        speeds_color_ = "#ffffff";  // цвет
        speeds_fontSize_ = 18;      // размер шрифта
        speeds_margin_ = 50;        // отступ от дуги шкалы
        speeds_radius_dx_ = 0;      // довесок к радиусу по оси OX
        speeds_radius_dy_ = 10;     // довесок к радиусу по оси OY

    }

    return true;
}
