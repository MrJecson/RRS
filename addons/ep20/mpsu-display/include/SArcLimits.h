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

#ifndef SARCLIMITS_H
#define SARCLIMITS_H

#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"

/*!
 * \class SArcLimits
 * \brief Дуга ограничения шкалы спидометра
 */
class SArcLimits : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    SArcLimits(const QString &config_dir, QWidget* parent = Q_NULLPTR);

    /// Установить значения ограничений
    void setVals(int curLimit, int nextLimit);

private:
    QImage img_;

    QRectF rect_; ///< размер рисуемой плоскости
    QRectF rect2_;
    QRectF rect3_;

    double stepSpeedInDegrees_; ///< шаг скорости в градусах

    int nSL_;       ///< значение следующего ограничения
    int cSL_;       ///< значение текущего ограничения
    double aCSL_;   ///< угол "nSL_"
    double aNSL_;   ///< угол "cSL_"
    double aPermitS_;

    // --- cfg параметры --- //
    int     widthArc_;      ///< ширина линии дуги
    QString curLimArc_color_;  ///< цвет
    QString nextLimArc_color_; ///< цвет
    QString curPermitArc_color_; ///< цвет
    // --------------------- //

    /// Нарисовать дуги ограничений
    void draw_();

    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);

};

#endif // SARCLIMITS_H
