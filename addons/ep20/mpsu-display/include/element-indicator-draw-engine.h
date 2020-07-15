//-----------------------------------------------------------------------------
//
//      Класс отрисовки элементов индикаторов
//      (c) РГУПС, ВЖД 05/07/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс отрисовки элементов индикаторов
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 05/07/2017
 */

#ifndef ELEMENTINDICATORDRAWENGINE_H
#define ELEMENTINDICATORDRAWENGINE_H

#include "abstract-element-draw-engine.h"

class QPainter;

/*!
 * \class ElementIndicatorDrawEngine
 * \brief Класс отрисовки элементов индикаторов
 */
class ElementIndicatorDrawEngine Q_DECL_FINAL: public AbstractElementDrawEngine
{
public:
    /*!
     * \brief Конструктор
     * \param elem - указатель на элемент для отрисовки
     */
    ElementIndicatorDrawEngine(AbstractElement* elem);

    /// Отрисовка элемента
    void drawElement() Q_DECL_OVERRIDE;
};

#endif // ELEMENTINDICATORDRAWENGINE_H
