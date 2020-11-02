//-----------------------------------------------------------------------------
//
//      Имитация вентилятра
//      (c) РГУПС, ВЖД 24/10/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Имитация вентилятра
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 24/10/2019
 */


#ifndef FANIMITATION2_H
#define FANIMITATION2_H

#include <QLabel>
#include <QTimer>

#include "display-shared-structures.h"

/*!
 * \class FanImitation2
 * \brief Класс имитации вентилятора
 */
class FanImitation2 : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param _size - размер (=радиус=ширина)
     * \param stepAngle - угол между "вентилями"
     * \param cOtstup - отступ "вентилей" от центра
     */
    FanImitation2(int _size, int stepAngle, int cOtstup, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~FanImitation2();

    /// Установить состояние вентилятора
    void setState(FanStateEnum state);

    /// Установить скорость вращения вентилятора
    void setSpeed(double val);


public slots:
    /// Процесс вращения вентилятора
    void onTimer();


private:
    QImage img_;
    QTimer* timer_;

    bool state_;

    int angle_; // текущий угол вентилятора
    double speed_;

    int stepAngle_;
    int cOtstip_;

    double cpX_;    // central point X
    double cpY_;    // central point Y
    double r_;      // radius
    double r2_;
    double base_;   // ширина оснований

    // Нарисовать вентилятор
    void draw_();

    // Вернуть полигон треугольника
    QPolygonF getTriangle_(double aDegree);

    QLineF getLine_(double aDegree);

};

#endif // FANIMITATION2_H
