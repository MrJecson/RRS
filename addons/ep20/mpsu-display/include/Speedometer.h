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

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "SFon.h"
#include "SArcLimits.h"
#include "SMajorLines.h"
#include "SLineLimit.h"
#include "SArrow.h"
#include "SCentralElements.h"
#include "STriangleLimit.h"
#include "SGlobalParams.h"

#include <QTimer>

/*!
 * \class SPeedometer
 * \brief Спидометр
 */
class SPeedometer : public QLabel, SGlobalParams
{
    Q_OBJECT

public:
    /// Конструктор
    SPeedometer(const QString &config_dir, QSize _size, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~SPeedometer();

    /// Установить значения спидометра
    void setVals(double speed, int setpointSpeed, int curLimit, int nextLimit);

    /// Установить координату поезда
    void setTrainPos(double pos);


public slots:
    /// Моргание значения тек. скорости, при приближении к значению ограничения
    void onTimer();

private:
    SFon*               sFon_;              ///< Фон
    SArcLimits*         sArcLimits_;        ///< Дуга ограничений
    SMajorLines*        sMajorLines_;       ///< Основные чёрточки на дуге шкалы
    SLineLimit*         sLineLimit_;
    SArrow*             sArrow_;            ///< Стрелка
    SCentralElements*   sCentralElements_;   ///< Центральные эл-ы (динамические)
//    STriangleLimit*     sTriangleLimitNext_;///< Треугольник огран-я скорости
//    STriangleLimit*     sTriangleLimitCur_; ///< Треугольник огран-я скорости
    STriangleLimit*     sTriangleSetpointSpeed_;

    int     curLimit_;
    int     nextLimit_;
    int     curLimit_old_;      ///< старое зн. текущего ограничения скорости
    int     nextLimit_old_;     ///< старое зн. следующего ограничения скорости
    double  speedCur_old_d_;    ///< старое зн. текущей скорости (вещ-е число)
    int     speedCur_old_i_;    ///< старое зн. текущей скорости (целое число)
    int     setpointSpeed_old_;

    QTimer* timerForBlink_; ///< таймер для "мигания" значения тек. скорости
    int timeCount_;


    QString curLimArc_color_;  ///< цвет
    QString nextLimArc_color_; ///< цвет
    QString curPermitArc_color_; ///< цвет

    /// Установить ограничения скоростей
    void setSpeedLimits_(int curLimit, int nextLimit);
    /// Установить текущую скорость
    void setCurSpeed_(double speedValue);
    // Установить заданную скорость
    void setSetpointSpeed_(int setpointSpeed);


    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);

};

#endif // SPEEDOMETER_H
