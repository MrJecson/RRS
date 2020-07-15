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

#ifndef ELEMENTINDICATOR_H
#define ELEMENTINDICATOR_H


#include "abstract-element.h"
#include "a-consts.h"

/*!
 * \class ElementIndicator
 * \brief Класс элементов индикации состояния различных систем
 */
class ElementIndicator : public AbstractElement
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param state - статус вкл/выкл
     * \param type - состояние элемента
     */
    ElementIndicator(QString name, bool state, Elements::IconType type,
                     QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~ElementIndicator();

    /// Установить положение подножки
    void setFootboardSide(Local::FootboardSide fs);

    /// Вернуть положение подножки
    Local::FootboardSide getFootboardSide();

    /// Установить состояние подножки
    void setFootboardEnabled(bool enabled);

    /// Вернуть состояние подножки
    bool isFootboardEnabled();


private:
    Local::FootboardSide footBoardSide_;    ///< Положение подножки

    bool footBoardEnabled_;  ///< Состояние подножки

    /// Метод полной отрисовки элемента индикации
    void drawElement_() Q_DECL_OVERRIDE;


private slots:
    /// Слот обработки показа элемента
    void showEvent(QShowEvent* e);

};

#endif // ELEMENTINDICATOR_H
