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

#ifndef SFON_H
#define SFON_H

#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"

/*!
 * \class SFon
 * \brief Фоновые элементы спидометра
 */
class SFon : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    SFon(const QString &config_dir, QWidget *parent = Q_NULLPTR);

private:
    double w_2_;
    double h_2_;

    QRectF rect_; ///< размер рисуемой плоскости

    QImage img_;

    // --- cfg параметры --- //
    /// дуга шкалы
    QString arcScale_color_;    ///< цвет
    int     arcScale_width_;    ///< ширина

    /// центральный круг
    QString centralCircle_color_;       ///< цвет
    int     centralCircle_diameter_;    ///< диаметр

    /// скоростя вокруг дуги шкалы
    QString speeds_color_;      ///< цвет
    int     speeds_fontSize_;   ///< размер шрифта
    int     speeds_margin_;     ///< отступ от дуги шкалы
    int     speeds_radius_dx_;  ///< довесок к радиусу по оси OX
    int     speeds_radius_dy_;  ///< довесок к радиусу по оси OY
    // --------------------- //

    /// Нарисовать все элементы
    void draw_();

    /// Нарисовать дугу шкалы
    void drawArc_(QPainter &paint);
    /// Нарисовать центральный круг
    void drawMidlCircle_(QPainter &paint);
    /// Нарисовать скоростя вокруг дуги шкалы
    void drawSpeeds_(QPainter &paint);

    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);

};

#endif // SFON_H
