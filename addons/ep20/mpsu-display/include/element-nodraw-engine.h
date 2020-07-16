//-----------------------------------------------------------------------------
//
//      Класс отсутствия отрисовки элемента если элемент невидим
//      (c) РГУПС, ВЖД 05/07/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс отсутствия отрисовки элемента если элемент невидим
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 05/07/2017
 */

#ifndef ELEMENTNODRAWENGINE_H
#define ELEMENTNODRAWENGINE_H

#include "abstract-element-draw-engine.h"

/*!
 * \class ElementIndicatorDrawEngine
 * \brief Класс отсутствия отрисовки элемента если элемент невидим
 */
class ElementNoDrawEngine Q_DECL_FINAL : public AbstractElementDrawEngine
{
public:
    /*!
     * \brief Конструктор
     * \param elem - указатель на элемент для отрисовки
     */
    ElementNoDrawEngine(AbstractElement* elem);

    /// Отрисовка элемента
    void drawElement() Q_DECL_OVERRIDE;
};

#endif // ELEMENTNODRAWENGINE_H
