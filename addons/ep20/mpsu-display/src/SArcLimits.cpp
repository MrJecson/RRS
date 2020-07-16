//-----------------------------------------------------------------------------
//
//      Дуга ограничения шкалы спидометра
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Дуга ограничения шкалы спидометра
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "SArcLimits.h"

#include "CfgReader.h"

//const	QString		SARCLIMIT_CFG = "../cfg/display/SArcLimit.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SArcLimits::SArcLimits(const QString &config_dir, QWidget *parent)
    : QLabel(parent)
    , SGlobalParams(config_dir + "SGlobalParams.xml")
    , nSL_(260)
    , cSL_(280)
    , aCSL_(0.0)
    , aNSL_(0.0)
    , aPermitS_(0.0)
{
    this->resize(parent->size());

    loadCfg_(config_dir);

    int otstup = 15;
    rect_.setRect( otstup,
                   otstup,
                   this->width()-otstup*2,
                   this->height()-otstup*2 );
    rect2_.setRect( otstup+2,
                    otstup+2,
                    this->width()-otstup*2-4,
                    this->height()-otstup*2-4 );
    rect3_.setRect( otstup+5,
                    otstup+5,
                    this->width()-otstup*2-10,
                    this->height()-otstup*2-10 );
    stepSpeedInDegrees_ = (360.0 - sgp_arcSplitLength)/sgp_maxSpeedScale;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
}

//-----------------------------------------------------------------------------
//  Установить значения ограничений
//-----------------------------------------------------------------------------
void SArcLimits::setVals(int curLimit, int nextLimit)
{
    if (curLimit == 0)
    {
        img_.fill(Qt::transparent);
        return;
    }

//    if (curLimit > sgp_maxSpeedScale - 3)
//        curLimit = sgp_maxSpeedScale - 3;
//    if (curLimit <= 3)
//        curLimit = 3;

    this->cSL_ = curLimit;
    this->nSL_ = nextLimit;

    aCSL_ = stepSpeedInDegrees_*(sgp_maxSpeedScale - cSL_)*16;
    aNSL_ = stepSpeedInDegrees_*(sgp_maxSpeedScale - nSL_)*16 - aCSL_;
    aPermitS_ = stepSpeedInDegrees_*16;
    (nSL_ < cSL_)? (aPermitS_ *= nSL_) : (aPermitS_ *= cSL_ - 5.0);

    draw_();
}

//-----------------------------------------------------------------------------
//  Нарисовать дуги ограничений
//-----------------------------------------------------------------------------
void SArcLimits::draw_()
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    int angleStart = 0;
    int angleLength = 0;

    if ((nSL_ > 0) && (cSL_ > 5))
    {
        // допустимая скорость
        paint.setPen(QPen( QColor(curPermitArc_color_),
                           widthArc_,
                           Qt::SolidLine ));
        angleStart = sgp_angleArcEnd*16 + aCSL_ + widthArc_*3;
        (nSL_ < cSL_)? (angleStart += aNSL_) : (angleStart += 5.0*16 + widthArc_*3*2);
        angleLength = aPermitS_ - widthArc_*4;
        paint.drawArc(rect_, angleStart, angleLength);
    }

    // следующее ограничение скорости
    paint.setPen(QPen( QColor(nextLimArc_color_),
                       widthArc_,
                       Qt::SolidLine ));
    angleStart = sgp_angleArcEnd*16 + aCSL_ + widthArc_*2;
    (nSL_ < cSL_)? (angleLength = aNSL_ - widthArc_*3*2) : (angleLength = 5.0*16);
    paint.drawArc(rect_, angleStart, angleLength);

    // текущее ограничение скорости
    if (cSL_ < sgp_maxSpeedScale)
    {
        paint.setPen(QPen( QColor(curLimArc_color_),
                           widthArc_,
                           Qt::SolidLine ));
        angleStart = sgp_angleArcEnd*16 + widthArc_;
        angleLength = aCSL_ - widthArc_*6;
        paint.drawArc(rect_, angleStart, angleLength);
    }

    paint.end();
    this->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool SArcLimits::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {

        QString sectionName = "SArcLimit";

        // ширина линии
        if (!cfg.getInt(sectionName, "arcLimit_width", widthArc_))
            widthArc_ = 4;
        // цвет
        if (!cfg.getString(sectionName, "arcLimit_color", curLimArc_color_))
            curLimArc_color_ = "#ff0000";
        // цвет
        if (!cfg.getString(sectionName, "arcLimitNext_color", nextLimArc_color_))
            nextLimArc_color_ = "#ffff00";
        // цвет
        if (!cfg.getString(sectionName, "arcPermitSpeed_color", curPermitArc_color_))
            curPermitArc_color_ = "#00ff00";

    }
    else
    {
        // Параметры по умолчанию.
        widthArc_ = 4;              // ширина линии
        curLimArc_color_ = "#ff0000";  // цвет
        nextLimArc_color_ = "#ffff00"; // цвет
        curPermitArc_color_ = "#00ff00"; // цвет

    }

    return true;
}

