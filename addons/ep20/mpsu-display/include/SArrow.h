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

#ifndef SARROW_H
#define SARROW_H

#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"

/*!
 * \class SArrow
 * \brief Стрелка спидометра
 */
class SArrow : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    SArrow(const QString &config_dir, QWidget* parent = Q_NULLPTR);

    /// Установить стрелку
    void setVal(double speedValue, QString color);

private:
    double w_2_;
    double h_2_;

    QImage img_;

    double stepDeg_;    ///< единица скорости в градусах
    double speedVal_;   ///< значение скорости

    // --- cfg параметры --- //
    double  koefLength_;    ///< коэфициент длины стрелки (от ширины спидометра)
    double  widthBase_;     ///< ширина основания стрелки
    QString color_;         ///< цвет стрелки
    // --------------------- //

    /// Нарисовать стрелку
    void draw_();

    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);

};

#endif // SARROW_H
