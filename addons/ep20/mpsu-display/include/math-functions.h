//------------------------------------------------------------------------------
//
//      Математические функции
//      (с) РГУПС, ВЖД 24/04/2018
//      Разработали: Притыкин Д.Е., Даглдиян Б.Д., Ковшиков С.В.
//
//------------------------------------------------------------------------------


#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <vector>
#include <cmath>
#include <algorithm>

namespace MathFunc
{


/// Звено с гистерезисом
template <typename T>
bool hysteresis(T x, T xdt, T x_min, T x_max)
{
    return (x < x_min) || ((x < x_max) && (xdt > 0));
}


/// Функция Хевисайда (численная)
template<typename T>
inline T hs_p(T _val)
{
    return static_cast<T>( _val > static_cast<T>(0) );
}


/// Функция Хевисайда (логическая)
template<typename T>
inline bool hs_pb(T _val)
{
    return _val > static_cast<T>(0);
}


/// Функция Хевисайда (численная) (для отрицательных чисел)
template<typename T>
inline T hs_n(T _val)
{
    return static_cast<T>( _val < static_cast<T>(0) );
}


/// Функция Хевисайда (логическая) (для отрицательных чисел)
template<typename T>
inline bool hs_nb(T _val)
{
    return _val < static_cast<T>(0);
}


/// Фильтр положительного значения
template<typename T>
inline T pf(T _val)
{
    return _val > static_cast<T>(0)? _val : static_cast<T>(0);
}


/// Фильтр отрицательного значения
template<typename T>
inline T nf(T _val)
{
//    return -pf(-_val);
    return _val < static_cast<T>(0)? _val : static_cast<T>(0);
}


/// Функция ограничени значения
template<typename T>
inline T cut(T _val, T _min, T _max)
{
    if (_val <= _min)
        return _min;

    if (_val >= _max)
        return _max;

    return _val;
}


/// Реле
template<typename T>
inline T relay(T _val, T _deltaInNegative, T _deltaInPositive)
{
    if (_val > _deltaInPositive)
        return static_cast<T>(1);
    else if (_val < _deltaInNegative)
        return static_cast<T>(-1);
    else
        return static_cast<T>(0);
}


/// Реле (доп. версия)
template<typename T, typename TRes>
inline TRes relay(T _val, T _min, T _max, TRes _left, TRes _mid, TRes _right)
{
    if (_val <= _min)
        return _left;

    if (_val >= _max)
        return _right;

    return _mid;
}


///
inline bool mas_or(std::vector<bool> _vec)
{
    return std::find(_vec.begin(), _vec.end(), true) != _vec.end();
}


///
inline bool mas_and(std::vector<bool> _vec)
{
    return std::find(_vec.begin(), _vec.end(), false) == _vec.end();
}


///
inline double try_div(double _divident, double _diveder, double _zeroEps)
{
    if (std::abs(_diveder) > _zeroEps)
        return _divident / _diveder;

    return 0.0;
}


/*!
 * \class Trigger
 * \brief Реализация простого триггера
 */
class Trigger
{
public:
    ///
    Trigger(bool _locked = false)
        : locked_(_locked)
    {

    }


    ///
    bool isLocked() const
    {
        return locked_;
    }


    ///
    template<typename T>
    T lckd()
    {
        return static_cast<T>(locked_);
    }


    ///
    operator double() const
    {
        return static_cast<double>(locked_);
    }


    ///
    void step(bool _set, bool _reset)
    {
        if (_set)
        {
            locked_ = true;
            return;
        }

        if (_reset)
        {
            locked_ = false;
        }
    }


private:
    ///
    bool locked_;

};



}


#endif // MATHFUNCTIONS_H
