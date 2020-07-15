//-----------------------------------------------------------------------------
//
//      Класс верхнего блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс верхнего блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */

#include "top-block.h"

namespace
{
    namespace L = Local;
    const L::ButtonId BUTTONS_IDS_[] = {L::biOTM, L::biF1, L::biF2, L::biF3,
                                        L::biF4, L::biF5, L::biMINUS, L::biPLUS,
                                        L::biSTAR, L::biCORRECTION};
}


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
TopBlock::TopBlock(QColor backgr, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent) // Передаём базовому классу
{
    // Устанавливаем цвет фона
    this->setPalette(QPalette(backgr));

    // Вызываем метод создания всех кнопок
    createAllChildren_();
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
TopBlock::~TopBlock()
{

}



//-----------------------------------------------------------------------------
// ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
//-----------------------------------------------------------------------------
void TopBlock::createAllChildren_()
{
    // Собираем полное имя картинки для загрузки
    QString fooPressed = "";
    QString fooReleased = "";
    ImageButton* button = Q_NULLPTR;

    // Названия кнопок в ресурсах берем из массива в файле "consts.h"
    for (int i = 0, n = HARD_BUTTONS_.count(); i < n; ++i)
    {
        // Собираем полный путь кнопок в ресурсах
        fooPressed = PRESSED_PREFIX_ + HARD_BUTTONS_.at(i);
        fooReleased = RELEASED_PREFIX_ + HARD_BUTTONS_.at(i);

        button = new ImageButton(BUTTON_NAMES_[i], this);
        button->setId(BUTTONS_IDS_[i]);
        button->resize(CHILD_SIZE_);
        button->setImagesNames(fooPressed, fooReleased);
        listButtons_.append(button);

        connect(listButtons_.at(i), SIGNAL(sendPressed(Local::ButtonId)),
                this, SLOT(receiveChildPressed(Local::ButtonId)));
        connect(listButtons_[i], SIGNAL(sendReleased(Local::ButtonId)),
                this, SLOT(receiveChildReleased(Local::ButtonId)));
    }

    // Вызываем метод АБСТРАКТНОГО класса, выравниваем виджеты.
    autoChildrenPos_(20);
}
