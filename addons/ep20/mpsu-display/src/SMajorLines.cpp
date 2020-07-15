//-----------------------------------------------------------------------------
//
//      Основные чёрточки на дуге шкалы
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Основные чёрточки на дуге шкалы
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "SMajorLines.h"
#include <QtCore/qmath.h>

#include "CfgReader.h"

//const	QString		SMAJORLINES_CFG = "../cfg/display/SMajorLines.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SMajorLines::SMajorLines(const QString &config_dir, QWidget *parent)
    : QLabel(parent), SGlobalParams(config_dir + "SGlobalParams.xml")
{
    this->resize(parent->size());
    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    loadCfg_(config_dir + "SMajorLines.xml");

    int otstup = 15;
    lengthLineInside_ = -otstup - lines_lenfth_;
    lengthLineOutside_ =  -otstup + 0;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать чёрточки
//-----------------------------------------------------------------------------
void SMajorLines::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    paint.setPen(QPen( QColor(lines_color_),
                       lines_width_,
                       Qt::SolidLine,
                       Qt::RoundCap ));

    for (int i = 0, n = sgp_maxSpeedScale/sgp_stepSpeed*2*2; i <= n; ++i)
    {
        double angle = (360.0 - sgp_angleArcEnd) - i*((360.0-sgp_arcSplitLength)/n);
        angle = qDegreesToRadians(angle);

        double lengthLineInside = 0;
        if (i%2 == 0)
            lengthLineInside = lengthLineInside_;
        else
            lengthLineInside = lengthLineInside_ + 7;

        paint.drawLine( w_2_ + (w_2_ + lengthLineInside)*cos(angle),
                        h_2_ + (h_2_ + lengthLineInside)*sin(angle),
                        w_2_ + (w_2_ + lengthLineOutside_)*cos(angle),
                        h_2_ + (h_2_ + lengthLineOutside_)*sin(angle) );
    }


    paint.end();
    this->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool SMajorLines::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName = "SMajorLines";

        // цвет
        if (!cfg.getString(sectionName, "lines_color", lines_color_))
            lines_color_ = "#ffffff";
        // ширина
        if (!cfg.getInt(sectionName, "lines_width", lines_width_))
            lines_width_ = 2;
        // длина
        if (!cfg.getInt(sectionName, "lines_length", lines_lenfth_))
            lines_lenfth_ = 26;

    }
    else
    {
        // Параметры по умолчанию.
        lines_color_ = "#ffffff";   // цвет
        lines_width_ = 2;           // ширина
        lines_lenfth_ = 26;         // длина

    }

    return true;
}
