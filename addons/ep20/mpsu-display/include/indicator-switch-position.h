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

#ifndef INDICATORSWITCHPOSITION_H
#define INDICATORSWITCHPOSITION_H

#include <QLabel>

#include "display-shared-structures.h"


/*!
 * \class IndicatorSwitchPosition
 * \brief Класс, реализующий индикацию переключателей крана машиниста ККБ
 */
class IndicatorSwitchPosition : public QLabel
{
public:
    /// Конструктор
    IndicatorSwitchPosition(QSize _size, QWidget* parent = Q_NULLPTR);

    /// Установить переключатель крана
    void setSelect(NumIndicatorSwitchPosEnum numSwitch);

private:
    const QString str_[4]{"С", "О", "П", "Т"};

    QLabel* labISP_[4]; // элемента
    QLabel* labOver_;   // выделение элемента

    // создание элементов
    void createLabels_();

};

#endif // INDICATORSWITCHPOSITION_H
