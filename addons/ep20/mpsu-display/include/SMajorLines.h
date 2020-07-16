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

#ifndef SMAJORLINES_H
#define SMAJORLINES_H

#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"

/*!
 * \class SMajorLines
 * \brief Основные чёрточки на дуге шкалы
 */
class SMajorLines : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    SMajorLines(const QString &config_dir, QWidget* parent = Q_NULLPTR);

private:
    double w_2_;
    double h_2_;

    double lengthLineInside_;   ///< длина чёрточки внутрь дуги шкалы
    double lengthLineOutside_;  ///< длина чёрточки наружу дуги шкалы

    QImage img_;

    // --- cfg параметры --- //
    QString lines_color_;   ///< цвет
    int     lines_width_;   ///< ширина
    int     lines_lenfth_;  ///< длина
    // --------------------- //

    /// Нарисовать чёрточки
    void draw_();

    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);
};

#endif // SMAJORLINES_H
