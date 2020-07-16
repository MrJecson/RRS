//-----------------------------------------------------------------------------
//
//      Имитация вентилятра
//      (c) РГУПС, ВЖД 2/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Имитация вентилятра
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 2/09/2019
 */


#ifndef FANIMITATION_H
#define FANIMITATION_H

#include <QLabel>
#include <QTimer>

/*!
 * \class FanImitation
 * \brief Класс имитации вентилятора
 */
class FanImitation : public QLabel
{
    Q_OBJECT

public:
    /// Конструктор
    FanImitation(QSize _size, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~FanImitation();

    /// Запустить вентилятор
    void setAngle(int angle);


private:
    QImage img_;
    QTimer* timer_;

    int angle_; // текущий угол вентилятора

    double cpX_;    // central point X
    double cpY_;    // central point Y
    double r_;      // radius
    double base_;   // ширина оснований

    // Нарисовать вентилятор
    void draw_();

    // Вернуть полигон треугольника
    QPolygonF getTriangle_(double aDegree);

};

#endif // FANIMITATION_H
