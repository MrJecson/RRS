//-----------------------------------------------------------------------------
//
//      Сигнализаторы неотпуска тормоза
//      (c) РГУПС, ВЖД 29/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Сигнализаторы неотпуска тормоза
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 29/08/2019
 */


#include "brake-release-indicators.h"

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
BrakeReleaseIndicators::BrakeReleaseIndicators(QSize _size, QWidget *parent)
    : QLabel(parent)
{
    this->resize(_size.width(), _size.height());

    this->setStyleSheet("border: 1px solid black");

    //
    for (int i = 0; i < 3; ++i)
    {
        lab_[i] = new QLabel("ТЦ" + QString::number(i + 1), this);
        lab_[i]->resize(32, 32);
        lab_[i]->move(6 + 40*i, 4);
        lab_[i]->setAlignment(Qt::AlignCenter);
    }

    setVals(false, false, false);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void BrakeReleaseIndicators::setVals(bool TC1, bool TC2, bool TC3)
{
    lab_[0]->setStyleSheet(getStyleSheet_(TC1));
    lab_[1]->setStyleSheet(getStyleSheet_(TC2));
    lab_[2]->setStyleSheet(getStyleSheet_(TC3));
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
QString BrakeReleaseIndicators::getStyleSheet_(bool flag)
{
    QString color((flag) ? ("red") : ("green"));

    return "border: 1px solid white;"
           "color: " + color + ";"
           "font: 8pt Arial;"
           "font-weight: 500;";
}

