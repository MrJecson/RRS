//-----------------------------------------------------------------------------
//
//      Класс элементов индикации
//      (c) РГУПС, ВЖД 17/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс элементов идникации
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 17/04/2017
 */

#include "element-indicator.h"

#include "element-indicator-draw-engine.h"
#include "element-nodraw-engine.h"

#include <QPainter>


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
ElementIndicator::ElementIndicator(QString name, bool state,
                                   Elements::IconType type, QWidget *parent)
    : AbstractElement(name, state, type, parent)
    , footBoardSide_(Local::fsBOT)
    , footBoardEnabled_(false)
{
    setBoxPos(7, 7);

    drawElement_();
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
ElementIndicator::~ElementIndicator()
{

}



//-----------------------------------------------------------------------------
// Установить положение подножки
//-----------------------------------------------------------------------------
void ElementIndicator::setFootboardSide(Local::FootboardSide fs)
{
    footBoardSide_ = fs;
}



//-----------------------------------------------------------------------------
// Вернуть положение подножки
//-----------------------------------------------------------------------------
Local::FootboardSide ElementIndicator::getFootboardSide()
{
    return footBoardSide_;
}



//-----------------------------------------------------------------------------
// Установить состояние подножки
//-----------------------------------------------------------------------------
void ElementIndicator::setFootboardEnabled(bool enabled)
{
    if (footBoardEnabled_ != enabled)
    {
        footBoardEnabled_ = enabled;

        drawElement_();
    }
}



//-----------------------------------------------------------------------------
// Вернуть состояние подножки
//-----------------------------------------------------------------------------
bool ElementIndicator::isFootboardEnabled()
{
    return footBoardEnabled_;
}



//-----------------------------------------------------------------------------
// Отрисовка элемента
//-----------------------------------------------------------------------------
void ElementIndicator::drawElement_()
{
    drawEngine_->drawElement();
}



//-----------------------------------------------------------------------------
// (слот) Слот обработки показа элемента
//-----------------------------------------------------------------------------
void ElementIndicator::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
    setElementDrawEngine(new ElementIndicatorDrawEngine(this));
    drawElement_();
}

