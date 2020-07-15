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


#ifndef SLINELIMIT_H
#define SLINELIMIT_H


#include <QLabel>
#include <QPainter>

#include "SGlobalParams.h"


/*!
 * \class SLineLimit
 * \brief Линии ограничений на шкале спидометра
 */
class SLineLimit : public QLabel, SGlobalParams
{
public:
    /// Конструктор
    SLineLimit(const QString &config_dir, QWidget* parent = Q_NULLPTR);

    /// Нарисовать чёрточки
    void draw(int curLimit, int nextLimit);

private:
    double w_2_;
    double h_2_;

    double lengthLineInside_;   ///< длина чёрточки внутрь дуги шкалы
    double lengthLineOutside_;  ///< длина чёрточки наружу дуги шкалы

    QImage img_;

    // --- cfg параметры --- //
    QString nextSpeedLim_color_;   ///< цвет
    QString curSpeedPermit_color_;   ///< цвет
    int     lines_width_;   ///< ширина
    int     lines_length_;  ///< длина
    // --------------------- //


    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);
};



#endif // SLINELIMIT_H
