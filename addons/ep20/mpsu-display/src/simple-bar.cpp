#include "simple-bar.h"

#include "float.h"

#include "simple-plot.h"

#include <QPainter>


NewBar::NewBar()
    : value_(0.0)
    , minValue_(-DBL_MAX)
    , maxValue_(DBL_MAX)
    , x_(0)
    , w_(10)
    , drawValue_(true)
    , precision_(0)
    , normalColor_({0, 100, 255})
    , lessMinColor_({255, 50, 0})
    , overMaxColor_({255, 50, 0})
    , baseLine_(0.0)
    , grid_(Q_NULLPTR)
{

}

void NewBar::attach(SimplePlot *_plot)
{
    grid_ = _plot->canvas()->grid();
    _plot->canvas()->attachBarItem(this);
}

void NewBar::setValue(double _val)
{
    value_ = _val;
}

double NewBar::maxValue() const
{
    return maxValue_;
}

void NewBar::setMaxValue(double maxValue)
{
    maxValue_ = maxValue;
}

double NewBar::minValue() const
{
    return minValue_;
}

void NewBar::setMinValue(double minValue)
{
    minValue_ = minValue;
}

void NewBar::setX(int _x)
{
    x_ = _x;
}

int NewBar::getX() const
{
    return x_;
}

void NewBar::setWidth(int _w)
{
    w_ = _w;
}

int NewBar::width() const
{
    return w_;
}

void NewBar::enableValueDraw(bool _enb)
{
    drawValue_ = _enb;
}

void NewBar::setPrecision(int _prec)
{
    precision_ = _prec;
}

void NewBar::setBaseLine(double _bLine)
{
    baseLine_ = _bLine;
}

void NewBar::setColor(QColor _col)
{
    normalColor_ = _col;
}

void NewBar::setColorLessMin(QColor _col)
{
    lessMinColor_ = _col;
}

void NewBar::setColorOverMax(QColor _col)
{
    overMaxColor_ = _col;
}
