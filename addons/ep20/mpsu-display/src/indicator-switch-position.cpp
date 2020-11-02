//-----------------------------------------------------------------------------
//
//      Индикатор положения переключателей крана машиниста ККБ
//      (c) РГУПС, ВЖД 28/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Индикатор положения переключателей крана машиниста ККБ
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 28/08/2019
 */

#include "indicator-switch-position.h"


//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
IndicatorSwitchPosition::IndicatorSwitchPosition(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);
    this->setStyleSheet("border: 1px solid black;"
                        "color: white;"
                        "font: 20pt Arial;"
                        "font-weight: 900;");

    createLabels_();
}



//-----------------------------------------------------------------------------
//  Установить переключатель крана
//-----------------------------------------------------------------------------
void IndicatorSwitchPosition::setSelect(NumIndicatorSwitchPosEnum numSwitch)
{
    if (numSwitch == NumIndicatorSwitchPosEnum::outPosition)
    {
        labOver_->setVisible(false);
    }
    else
    {
        labOver_->setVisible(true);
        labOver_->move(0, this->height()/4*numSwitch);
        labOver_->setText(str_[numSwitch]);
    }
}



//-----------------------------------------------------------------------------
//  Создание элементов
//-----------------------------------------------------------------------------
void IndicatorSwitchPosition::createLabels_()
{

    for (int i = 0; i < 4; ++i)
    {
        labISP_[i] = new QLabel(str_[i], this);
        labISP_[i]->resize(this->width(), this->height()/4);
        labISP_[i]->move(0, this->height()/4*i);
        labISP_[i]->setAlignment(Qt::AlignCenter);
    }

    labOver_ = new QLabel(this);
    labOver_->resize(this->width(), this->height()/4);
    labOver_->setStyleSheet("background: white;"
                            "color: #051432;");
    labOver_->setAlignment(Qt::AlignCenter);


}
