//-----------------------------------------------------------------------------
//
//      Класс нижнего блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс нижнего блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */

#include "bottom-block.h"

#include "image-button.h"


namespace
{
    namespace L = Local;

    const L::ButtonId BUTTONS_IDS_[] = {L::biDIGIT1, L::biDIGIT2, L::biDIGIT3,
                                        L::biDIGIT4, L::biDIGIT5, L::biDIGIT6,
                                        L::biDIGIT7, L::biDIGIT8, L::biDIGIT9,
                                        L::biDIGIT0};
}


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
BottomBlock::BottomBlock(QColor backgr, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent)
{
    // Устанавливаем цвет фона
    this->setPalette({backgr});

    // Вызываем метод создания всех кнопок
    createAllChildren_();
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
BottomBlock::~BottomBlock()
{

}



//-----------------------------------------------------------------------------
// Создаём все дочерние виджеты
//-----------------------------------------------------------------------------
void BottomBlock::createAllChildren_()
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

        connect(listButtons_[i], SIGNAL(sendPressed(Local::ButtonId)),
                this, SLOT(receiveChildPressed(Local::ButtonId)));
        connect(listButtons_[i], SIGNAL(sendReleased(Local::ButtonId)),
                this, SLOT(receiveChildReleased(Local::ButtonId)));
    }

    // Вызываем метод АБСТРАКТНОГО класса, выравниваем виджеты.
    // В данном случае установлено доп. расстояние между кнопками 4px (padding)
    autoChildrenPos_(20);
}
