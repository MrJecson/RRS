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

#include "left-block.h"


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
LeftBlock::LeftBlock(QColor backrg, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent) // Передаём все в абстр. класс
{
    this->setPalette(QPalette(backrg));

    // Вызываем метод создания всех дочерних элементов
    createAllChildren_();

}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
LeftBlock::~LeftBlock()
{

}



//-----------------------------------------------------------------------------
// ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
//-----------------------------------------------------------------------------
void LeftBlock::createAllChildren_()
{

}