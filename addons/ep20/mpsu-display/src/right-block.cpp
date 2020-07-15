//-----------------------------------------------------------------------------
//
//      Класс правого блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 06/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс правого блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 06/03/2017
 */

#include "right-block.h"

namespace
{
    namespace L = Local;
    const L::ButtonId BUTTONS_IDS_[] = {L::biLEFT,
                                        L::biRIGHT, L::biUP, L::biDOWN,
                                        L::biINPUT};
}


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
RightBlock::RightBlock(QColor backrg, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent) // Передаём базовому классу
{
    // Устанавливаем цвет фона
    this->setPalette(QPalette(backrg));

    // Вызываем метод создания всех кнопок
    createAllChildren_();
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
RightBlock::~RightBlock()
{

}



//-----------------------------------------------------------------------------
// ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
//-----------------------------------------------------------------------------
void RightBlock::createAllChildren_()
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

    // ****************************************************************
    // *   Вызываем метод АБСТРАКТНОГО класса, выравниваем виджеты.   *
    // * При этом -1 значит, что по оси X происходит автовыравнивание *
    // *       А по оси Y жестко установленное значение 110           *
    // ****************************************************************
    autoChildrenPos_(40, QPoint(-1, 150));
}

