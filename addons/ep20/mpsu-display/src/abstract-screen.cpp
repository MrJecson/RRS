//-----------------------------------------------------------------------------
//
//      Абстрактный класс экранов
//      (c) РГУПС, ВЖД 11/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс экранов
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/04/2017
 */

#include "abstract-screen.h"
#include "element-indicator.h"

#define PSD PowerSystemData
PSD::PowerType AbstractScreen::powerType_ = PSD::PT_DC;


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
AbstractScreen::AbstractScreen(QString scrName, QRect scrGeo, QWidget *parent)
    : QWidget(parent)
    , buttonsNames_({"","","","","","","","","",""})
    , buttonsNamesTop_({"","","","","","","","","",""})
    , buttonNamesHead_("")
    , buttonNamesHeadNum_(-1)
    , buttonNamesHeadCount_(-1)
    , buttonSelectedIdx_(-1)
    , availableToGo_(true)
    , SCREEN_NAME_(scrName)
{
    this->setAutoFillBackground(true);
    this->setPalette({{5, 20, 50}});
    this->setGeometry(scrGeo);

    for (int i = 0; i < 20; i++)
    {
        listScreens_.append(Q_NULLPTR);
    }
}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
AbstractScreen::~AbstractScreen()
{

}



//-----------------------------------------------------------------------------
// Вернуть имя экрана
//-----------------------------------------------------------------------------
QString AbstractScreen::getScreenName()
{
    return SCREEN_NAME_;
}



//-----------------------------------------------------------------------------
// Установить возможность перехода на данный экран
//-----------------------------------------------------------------------------
void AbstractScreen::setAvailableToGo(bool available)
{
    availableToGo_ = available;
}



//-----------------------------------------------------------------------------
// Вернуть возможность перехода на данных экран
//-----------------------------------------------------------------------------
bool AbstractScreen::isAvailableToGo()
{
    return availableToGo_;
}



//-----------------------------------------------------------------------------
// Переход на экран по номеру клавиши
//-----------------------------------------------------------------------------
bool AbstractScreen::goToScreen(int num, AbstractScreen* &currScr)
{
    // Если для данного экрана существует экран под таким номером
    if ( (num >= 0) && (num < 20) && (listScreens_[num] != Q_NULLPTR) &&
         listScreens_[num]->isAvailableToGo())
    {
        this->doOnComeOut();

        AbstractScreen * foo = listScreens_.at(num);

        foo->show();

        foo->doOnComeIn();

        this->hide();

        // Отправляем ссылку на выбранный экран в "middle block"
        currScr = foo;

        return true;
    }

    return false;
}



//-----------------------------------------------------------------------------
// Добавление экрана в список доступных
//-----------------------------------------------------------------------------
AbstractScreen* AbstractScreen::setScreen(int ind, AbstractScreen *scr)
{
    // Если номер входит в допустимый диапазон (Кнопок 10!)
    if ( (ind >= 0) && (ind < 10) )
    {
        // Меняем нулевые указатели на "живые"
        listScreens_.replace(ind, scr);
    }

    // Возвращаем указатель на класс
    return this;
}



//-----------------------------------------------------------------------------
// Установить экраны в список доступных
//-----------------------------------------------------------------------------
void AbstractScreen::setScreens(QVector<ScreenPair> _vec)
{
    for (ScreenPair p : _vec)
    {
        listScreens_.replace(p.first, p.second);
    }
}




//-----------------------------------------------------------------------------
// Вернуть имена кнопок для блока программируемых кнопок
//-----------------------------------------------------------------------------
const QStringList AbstractScreen::getButtonsNames()
{
    return buttonsNames_;
}

const QStringList AbstractScreen::getButtonsNamesTop()
{
    return buttonsNamesTop_;
}

const QString AbstractScreen::getButtonsNamesHead()
{
    return buttonNamesHead_;
}

int AbstractScreen::getButtonsNamesHeadNum()
{
    return buttonNamesHeadNum_;
}

int AbstractScreen::getButtonsNamesHeadCount()
{
    return buttonNamesHeadCount_;
}

int AbstractScreen::getButtonSelectedIdx()
{
    return buttonSelectedIdx_;
}



//-----------------------------------------------------------------------------
// Установить индикатор по индексу
//-----------------------------------------------------------------------------
void AbstractScreen::setIndicator(int index, ElementIndicator *element)
{
    if (index < listIndicators_.count())
    {
        listIndicators_.replace(index, element);
    }
}



//-----------------------------------------------------------------------------
// Установить род тока
//-----------------------------------------------------------------------------
void AbstractScreen::setPowerType(PowerSystemData::PowerType _pt)
{
    powerType_ = _pt;
}



//-----------------------------------------------------------------------------
// Вернуть род тока
//-----------------------------------------------------------------------------
PowerSystemData::PowerType AbstractScreen::getPowerType()
{
    return powerType_;
}



//-----------------------------------------------------------------------------
// Сброс экрана и всех подконтрольных элементов при разрыве соединения
//-----------------------------------------------------------------------------
void AbstractScreen::resetOnDisconnect()
{
    foreach (ElementIndicator* el, listIndicators_)
    {
        if (el)
        {
            el->resetOnDisconnect();
        }
    }
}



//-----------------------------------------------------------------------------
// Действия при переходе на этот экран
//-----------------------------------------------------------------------------
void AbstractScreen::doOnComeIn()
{
    // По умолчанию ничего не делаем. Будет переопределён при необходимости
}



//-----------------------------------------------------------------------------
// Действия при переходе с этого экрана
//-----------------------------------------------------------------------------
void AbstractScreen::doOnComeOut()
{
    // По умолчанию ничего не делаем. Будет переопределён при необходимости
}



//-----------------------------------------------------------------------------
// Обработка не цифровых кнопок
//-----------------------------------------------------------------------------
void AbstractScreen::receiveOtherButton(Local::ButtonId id)
{
    Q_UNUSED(id);
}



//-----------------------------------------------------------------------------
// Заполнить список индикаторов нулевыми указателями
//-----------------------------------------------------------------------------
void AbstractScreen::initIndicators_(int number)
{
    for (int i = 0; i < number; i++)
    {
        listIndicators_.append(Q_NULLPTR);
    }
}
