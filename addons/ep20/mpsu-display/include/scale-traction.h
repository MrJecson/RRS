//-----------------------------------------------------------------------------
//
//      Шкала тяги
//      (c) РГУПС, ВЖД 14/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Шкала тяги
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 14/08/2019
 */

#ifndef SCALETRACTION_H
#define SCALETRACTION_H

#include <QLabel>

/*!
 * \class ScaleTraction
 * \brief Шкала тяги
 */
class ScaleTraction : public QLabel
{
public:
    /// Конструктор
    ScaleTraction(QSize _size, QWidget* parent = Q_NULLPTR);

private:
    QImage img_;

    /// Нарисовать шкалу
    void draw_();

};

#endif // SCALETRACTION_H
