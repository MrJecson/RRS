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

#ifndef STRIANGLELIMIT_H
#define STRIANGLELIMIT_H

#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"

//-----------------------------------------------------------------------------
//  Тип треугольника ограничения
//-----------------------------------------------------------------------------
enum typeTriangleLimit
{
    cur = 0,
    next = 1,
    setpointSpeed = 2
};


/*!
 * \class STriangleLimit
 * \brief Треугольник ограничения шкалы спидометра
 */
class STriangleLimit : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    STriangleLimit(const QString &config_dir, int _typeTriangle, QWidget *parent = Q_NULLPTR );

    /// Установить значение ограничения
    void setVal(int speed);


private:
    double w_2_;
    double h_2_;

    QImage   img_;

    double stepDeg_;    ///< единица скорости в градусах
    int speedVal_;      ///< значение скорости

    // --- cfg параметры --- //
    double widthTriangle_;  ///< ширина основания
    double lengthTriangle_; ///< длина
    QString colorTriangle_; ///< цвет
    // --------------------- //

    /// Нарисовать треугольник
    void draw_();

    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path, int typeTriangle);

};

#endif // STRIANGLELIMIT_H
