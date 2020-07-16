//-----------------------------------------------------------------------------
//
//      Класс левого блока
//      (c) РГУПС, ВЖД 07/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс левого блока
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 07/03/2017
 */

#ifndef LEFTBLOCK_H
#define LEFTBLOCK_H


#include "abstract-block.h"

/*!
 * \class LeftBlock
 * \brief Класс левого блока с расположенным на нем блоком индикации
 */
class LeftBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backrg - цвет фона
     * \param geo - геометрия
     */
    LeftBlock(QColor backrg, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~LeftBlock();


private:
    /// Геометрия блока индикации
    const QRect  INDI_BLOCK_GEO_  = QRect(QPoint(10, 10), QSize(60, 40));


    // ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
    /// Метод создания дочерних элементов
    void createAllChildren_() Q_DECL_OVERRIDE;

};

#endif // LEFTBLOCK_H
