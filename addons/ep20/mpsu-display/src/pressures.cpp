//-----------------------------------------------------------------------------
//
//      Класс отображения давления
//      (c) РГУПС, ВЖД 29/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс отображения давления
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 29/08/2019
 */

#include "pressures.h"


//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
Pressures::Pressures(QSize _size, QString name, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size);
    this->setText(name);
    this->setStyleSheet("border: 1px solid black;"
                        "color: white;"
                        "font: 14pt Arial;"
                        "font-weight: 600;"
                        "padding-left: 5px;"
                        "padding-bottom: 3px;");

    //
    lab_ = new QLabel("0.00", this);
    lab_->resize(this->width()/2, this->height());
    lab_->move(this->width()/2, 0);
    lab_->setStyleSheet("border: none;");
}

//-----------------------------------------------------------------------------
//  Установить значение давления
//-----------------------------------------------------------------------------
void Pressures::setVal(double val)
{
//    if (val > 1.0)
//        val = 1.0;
//    if (val < 0.0)
//        val = 0.0;

    lab_->setText(QString::number(val, 'f', 2));
}
