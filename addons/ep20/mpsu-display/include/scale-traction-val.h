//-----------------------------------------------------------------------------
//
//      Динамические величины на шкале тяги
//      (c) РГУПС, ВЖД 15/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Динамические величины на шкале тяги
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 15/08/2019
 */

#ifndef SCALETRACTIONVAL_H
#define SCALETRACTIONVAL_H

#include <QLabel>

/*!
 * \class ScaleTractionVal
 * \brief Динамические величины на шкала тяги
 */
class ScaleTractionVal : public QLabel
{
public:
    /// Конструктор
    ScaleTractionVal(QSize _size, QWidget* parent = Q_NULLPTR);

    /// Установить значения динамическим элементам
    void setVal(int setVal, int actualVal);

private:
    QImage img_;

    /// Нарисовать динамические элементы
    void draw_(int setVal, int actualVal);

};

#endif // SCALETRACTIONVAL_H
