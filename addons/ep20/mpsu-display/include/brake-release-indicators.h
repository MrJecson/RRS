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

#ifndef BRAKERELEASEINDICATORS_H
#define BRAKERELEASEINDICATORS_H

#include <QLabel>

/*!
 * \class BrakeReleaseIndicators
 * \brief Сигнализаторы неотпуска тормоза
 */
class BrakeReleaseIndicators : public QLabel
{
public:
    /// Конструктор
    BrakeReleaseIndicators(QSize _size, QWidget* parent = Q_NULLPTR);

    /// Установить значения ТЦ
    void setVals(bool TC1, bool TC2, bool TC3);

private:
    QLabel* lab_[3];

    QString getStyleSheet_(bool flag);


};

#endif // BRAKERELEASEINDICATORS_H
