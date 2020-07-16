//-----------------------------------------------------------------------------
//
//      Абстрактный класс панелей(блоков) управления/индикации
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс панелей(блоков) управления/индикации
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */

#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H


#include <QLabel>

#include "a-consts.h"

class QWidget;

/*!
 * \class AbstractBlock
 * \brief Базовый класс различных блоков с кнопками, картинками, индикаторами.
 */
class AbstractBlock : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param geo - геометрия блока
     */
    AbstractBlock(QRect geo, QWidget* parent = Q_NULLPTR); // !!! delete geo !!! move all GEOS to namespace !!!
    /// Деструктор
    ~AbstractBlock();

signals:
    /// Кнопка нажата
    void sendChildPressed(Local::ButtonId id);

    /// Кнопка отпущена
    void sendChildReleased(Local::ButtonId id);


public slots:
    /// Обработка нажатия кнопки
    void receiveChildPressed(Local::ButtonId id);

    /// Обработка отпускания кнопки
    void receiveChildReleased(Local::ButtonId id);


protected:
    /// Метод создания дочерних виджетов
    virtual void createAllChildren_() = 0;

    /// Автоматическое выравнивание дочерних виджетов
    virtual void autoChildrenPos_(int pad = 0, QPoint fixedPos =QPoint(-1,-1));


private:
    /// Выбор расчета суммарной высоты/ширины
    enum Property {
        WIDTH, HEIGHT
    };

    /// Вычисление суммарной ширины/высоты дочерних виджетов
    int getSumChildrenLength_(Property prop);

};

#endif // ABSTRACTBLOCK_H
