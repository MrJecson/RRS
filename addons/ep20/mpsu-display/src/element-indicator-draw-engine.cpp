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

#include "element-indicator-draw-engine.h"

#include <QImage>
#include <QPainter>

#include "abstract-element.h"
#include "element-indicator.h"
#include "a-consts.h"


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
ElementIndicatorDrawEngine::ElementIndicatorDrawEngine(AbstractElement *elem)
    : AbstractElementDrawEngine(elem)
{

}



//-----------------------------------------------------------------------------
// Отрисовка элемента
//-----------------------------------------------------------------------------
void ElementIndicatorDrawEngine::drawElement()
{
    ElementIndicator* fooEl = (ElementIndicator*)element_;
    // Рисуем сам "чекбокс"
    fooEl->drawBox();

    QImage img(fooEl->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter p(&img);

    if (fooEl->isConnected() && fooEl->isFootboardEnabled())
    {
        p.setBrush(QColor("#ffffff"));
        if (fooEl->getFootboardSide() == Local::fsTOP)
        {
            p.drawRect(fooEl->boxX(), fooEl->boxY() - 3,
                       fooEl->boxW(), 3);
        }
        else if (fooEl->getFootboardSide() == Local::fsBOT)
        {
            p.drawRect(fooEl->boxX(), fooEl->boxY() + fooEl->boxH(),
                       fooEl->boxW(), 3);
        }
    }
    p.end();

    // Устанавливаем пиксмэп
    fooEl->setPixmap(QPixmap::fromImage(img));
}
