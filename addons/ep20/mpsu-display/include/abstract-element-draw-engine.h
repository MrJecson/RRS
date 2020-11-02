//-----------------------------------------------------------------------------
//
//      Абстрактный класс отрисовки элементов (разработка приостановлена)
//      (c) РГУПС, ВЖД 05/07/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс отрисовки элементов
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 05/07/2017
 */

#ifndef ABSTRACTELEMENTDRAWENGINE_H
#define ABSTRACTELEMENTDRAWENGINE_H

#include <QObject>

class AbstractElement;
class QPainter;

/*!
 * \class AbstractElementDrawEngine
 * \brief Абстрактный класс отрисовки элементов
 */
class AbstractElementDrawEngine
{
public:
    ///
    AbstractElementDrawEngine(AbstractElement* elem);
    virtual ~AbstractElementDrawEngine();

    ///
    virtual void drawElement() = 0;

protected:
    ///
    AbstractElement* element_;

//    int h();

//    int w();

//    int x();

//    int y();

    void drawDisconnected(QPainter &p);

    void drawBase(QPainter &p);

    void drawCross(QPainter &p);

    void drawTriangle(QPainter &p, bool back); // here !!!
};

#endif // ABSTRACTELEMENTDRAWENGINE_H
