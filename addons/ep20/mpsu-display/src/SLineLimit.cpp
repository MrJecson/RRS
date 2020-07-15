//-----------------------------------------------------------------------------
//
//      Линии ограничений на шкале спидометра
//      (c) РГУПС, ВЖД 12/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Линии ограничений на шкале спидометра
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 12/08/2019
 */


#include "SLineLimit.h"
#include <QtCore/qmath.h>

#include "CfgReader.h"

//const	QString		SLINELIMIT_CFG = "../cfg/display/SArcLimit.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SLineLimit::SLineLimit(const QString &config_dir, QWidget *parent)
    : QLabel(parent), SGlobalParams(config_dir + "SGlobalParams.xml")
{
    this->resize(parent->size());
    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;

    loadCfg_(config_dir);

    int otstup = 15;
    lengthLineInside_ = -otstup - lines_length_;
    lengthLineOutside_ = -otstup - 1;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
}

//-----------------------------------------------------------------------------
//  Нарисовать чёрточки
//-----------------------------------------------------------------------------
void SLineLimit::draw(int curLimit, int nextLimit)
{
    img_.fill(Qt::transparent);

    if (curLimit == 0)
        return;

    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    double angle = 0;

    paint.setPen(QPen( QColor(nextSpeedLim_color_),
                       lines_width_,
                       Qt::SolidLine,
                       Qt::RoundCap ));

    angle = (360.0 - sgp_angleArcEnd) - (sgp_maxSpeedScale - curLimit/5)*((360.0-sgp_arcSplitLength)/(sgp_maxSpeedScale/sgp_stepSpeed*2*2));
    angle = qDegreesToRadians(angle);

    double lengthLineInside = lengthLineInside_ - 5;

    // желтая черточка
    paint.drawLine( w_2_ + (w_2_ + lengthLineInside)*cos(angle),
                    h_2_ + (h_2_ + lengthLineInside)*sin(angle),
                    w_2_ + (w_2_ + lengthLineOutside_)*cos(angle),
                    h_2_ + (h_2_ + lengthLineOutside_)*sin(angle) );




    if ((nextLimit > 0) && (curLimit > 5))
    {
        paint.setPen(QPen( QColor(curSpeedPermit_color_),
                           lines_width_,
                           Qt::SolidLine,
                           Qt::RoundCap ));

        int foo = 0;
        (nextLimit < curLimit)? (foo = nextLimit) : (foo = curLimit - 5);
        angle = (360.0 - sgp_angleArcEnd) - (sgp_maxSpeedScale - foo/5)*((360.0-sgp_arcSplitLength)/(sgp_maxSpeedScale/sgp_stepSpeed*2*2));
        angle = qDegreesToRadians(angle);

        // зеленая черточка
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
bool SLineLimit::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName = "SArcLimit";

        // цвет
        if (!cfg.getString(sectionName, "arcLimitNext_color", nextSpeedLim_color_))
            nextSpeedLim_color_ = "#ffff00";
        // цвет
        if (!cfg.getString(sectionName, "arcPermitSpeed_color", curSpeedPermit_color_))
            curSpeedPermit_color_ = "#00ff00";
        // ширина
        if (!cfg.getInt(sectionName, "linesLimits_width", lines_width_))
            lines_width_ = 2;
        // длина
        if (!cfg.getInt(sectionName, "lineLimits_length", lines_length_))
            lines_length_ = 26;

    }
    else
    {
        // Параметры по умолчанию.
        nextSpeedLim_color_ = "#ffff00";   // цвет
        curSpeedPermit_color_ = "#00ff00";   // цвет
        lines_width_ = 2;           // ширина
        lines_length_ = 26;         // длина

    }

    return true;
}
