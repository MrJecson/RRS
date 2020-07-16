//-----------------------------------------------------------------------------
//
//      Спидометр
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Спидометр
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "Speedometer.h"
#include "cmath"

#include "CfgReader.h"

//const	QString		SPEEDOMETER_CFG = "../cfg/display/SArcLimit.xml";

const double EPS = 0.0001;

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SPeedometer::SPeedometer(const QString &config_dir, QSize _size, QWidget *parent)
    : QLabel(parent), SGlobalParams(config_dir + "SGlobalParams.xml")
    , curLimit_(0)
    , nextLimit_(0)
    , curLimit_old_(-1)
    , nextLimit_old_(-1)
    , speedCur_old_d_(-1.0)
    , speedCur_old_i_(-1)
    , setpointSpeed_old_(-1)
{
    this->resize(_size);

    loadCfg_(config_dir + "SArcLimit.xml");

    // border
    QLabel* labelForThisBorder = new QLabel(this);
    labelForThisBorder->resize(this->width(), 268);
    labelForThisBorder->setStyleSheet("border: 1px solid black");

    //
    timeCount_ = 3;
    timerForBlink_ = new QTimer();
    timerForBlink_->setInterval(500);
    connect(timerForBlink_, SIGNAL(timeout()), this, SLOT(onTimer()));

    sFon_               = new SFon(config_dir + "SFon.xml", this);
    sMajorLines_        = new SMajorLines(config_dir, this);
    sLineLimit_         = new SLineLimit(config_dir + "SArcLimits.xml", this);
    sArcLimits_         = new SArcLimits(config_dir + "SArcLimits.xml", this);
    sArrow_             = new SArrow(config_dir + "SArrow.xml", this);
    sCentralElements_   = new SCentralElements(config_dir + "SCentralElements.xml", this);
//    sTriangleLimitNext_ = new STriangleLimit(typeTriangleLimit::next, this);
//    sTriangleLimitCur_  = new STriangleLimit(typeTriangleLimit::cur, this);
    sTriangleSetpointSpeed_ = new STriangleLimit(config_dir, typeTriangleLimit::setpointSpeed, this);

    timerForBlink_->start();
}



//-----------------------------------------------------------------------------
//  Деструктор
//-----------------------------------------------------------------------------
SPeedometer::~SPeedometer()
{
    timerForBlink_->stop();
}



//-----------------------------------------------------------------------------
//  Установить значения спидометра
//-----------------------------------------------------------------------------
void SPeedometer::setVals(double speed, int setpointSpeed, int curLimit, int nextLimit)
{
    setSpeedLimits_(curLimit, nextLimit);
    setSetpointSpeed_(setpointSpeed);
    setCurSpeed_(speed);
}



//-----------------------------------------------------------------------------
//  Установить координату поезда
//-----------------------------------------------------------------------------
void SPeedometer::setTrainPos(double pos)
{
    sCentralElements_->setPosTrain(pos);
}



//-----------------------------------------------------------------------------
//  Моргание значения текущей скорости, при приближении к значению ограничения
//-----------------------------------------------------------------------------
void SPeedometer::onTimer()
{
    if (curLimit_ == 0)
        return;

    // условие значения приближения
    if (curLimit_old_ - speedCur_old_i_ <= 2)
    {
        timeCount_++;
        // "время ожидания" перед миганием
        if (timeCount_ > 2)
        {
            // процесс мигания
            sCentralElements_->getCurSpeed()->setVisible(!sCentralElements_->getCurSpeed()->isVisible());
        }
    }
    else
    {
        timeCount_ = 3;
        sCentralElements_->getCurSpeed()->setVisible(true);
    }
}



//-----------------------------------------------------------------------------
//  Установить ограничения скоростей
//-----------------------------------------------------------------------------
void SPeedometer::setSpeedLimits_(int curLimit, int nextLimit)
{
    // zБогос. Проверить. Задать значения ограничений == -10.
    if (curLimit == curLimit_old_)
        return;
    if (nextLimit == nextLimit_old_)
        return;

    if (curLimit > sgp_maxSpeedScale)
        curLimit = sgp_maxSpeedScale;
    if (curLimit < 0)
        curLimit = 0;
    if (nextLimit < 0)
        nextLimit = 0;

    curLimit_ = curLimit;
    nextLimit_ = nextLimit;
    if (nextLimit > curLimit)
        nextLimit_ = curLimit;

    // ограничения дугами
    sArcLimits_->setVals(curLimit, nextLimit);

    // черточки цветные
    sLineLimit_->draw(curLimit, nextLimit);

//    // ограничения треугольниками
//    sTriangleLimitCur_->setVal(curLimit);
//    sTriangleLimitNext_->setVal(nextLimit);

    // текущее ограничение в центре
    //sCentralElements_->setLimitSpeed(curLimit);


    curLimit_old_ = curLimit;
    nextLimit_old_ = nextLimit;
}



//-----------------------------------------------------------------------------
//  Установить текущую скорость
//-----------------------------------------------------------------------------
void SPeedometer::setCurSpeed_(double speedValue)
{
    if ( abs(speedCur_old_d_ - speedValue) < EPS )
        return;
    speedCur_old_d_ = speedValue;

    if (speedValue < 0.0)
        return;
    if (speedValue > sgp_maxSpeedScale)
        return;

    QString color("#ffffff");
    if (speedValue <= nextLimit_)
        color = curPermitArc_color_;
    else
    if (speedValue <= curLimit_)
        color = nextLimArc_color_;
    else
        color = curLimArc_color_;

    if (curLimit_ == 0)
        color = "#ffffff";

    // установить стрелку и его цвет
    sArrow_->setVal(speedValue, color);

    // установить центральный круг и его цвет
    sCentralElements_->drawCenterCircle(color);


    if ( speedCur_old_i_ == round(speedValue) )
        return;
    speedCur_old_i_ = round(speedValue);

    // установить значение скорости на центральном круге
    sCentralElements_->setCurSpeed(speedCur_old_i_);
}



//-----------------------------------------------------------------------------
//  Установить заданную скорость
//-----------------------------------------------------------------------------
void SPeedometer::setSetpointSpeed_(int setpointSpeed)
{
    if (setpointSpeed == setpointSpeed_old_)
        return;
    if (setpointSpeed > sgp_maxSpeedScale)
        return;
    if (setpointSpeed < 0)
        return;

    // заданная скорость треугольником
    sTriangleSetpointSpeed_->setVal(setpointSpeed);

    // заданная скорость в центре
    sCentralElements_->setSetpointSpeed(setpointSpeed);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool SPeedometer::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {

        QString sectionName = "SArcLimit";

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
        curLimArc_color_ = "#ff0000";  // цвет
        nextLimArc_color_ = "#ffff00"; // цвет
        curPermitArc_color_ = "#00ff00"; // цвет

    }

    return true;
}

