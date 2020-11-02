//-----------------------------------------------------------------------------
//
//      Класс отображения давления
//      (c) РГУПС, ВЖД 29/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс отображения давления
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 29/08/2019
 */

#ifndef PRESSURES_H
#define PRESSURES_H

#include <QLabel>


/*!
 * \class Pressures
 * \brief Класс отображения давления на основном экране дисплея
 */
class Pressures : public QLabel
{
public:
    Pressures(QSize _size, QString name, QWidget* parent = Q_NULLPTR);

    void setVal(double val);

private:
    QLabel* lab_;

};

#endif // PRESSURES_H
