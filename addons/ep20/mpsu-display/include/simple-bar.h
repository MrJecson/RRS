#ifndef SIMPLE_BAR_H
#define SIMPLE_BAR_H

#include <QColor>

class QPainter;

class SimplePlot;
class SimpleGrid;

class NewBar
{
public:
    ///
    NewBar();

    ///
    void attach(SimplePlot* _plot);

    ///
    void setValue(double _val);

    ///
    double maxValue() const;

    ///
    void setMaxValue(double maxValue);

    ///
    double minValue() const;

    ///
    void setMinValue(double minValue);

    ///
    void setX(int _x);

    ///
    int getX() const;

    ///
    void setWidth(int _w);

    ///
    int width() const;

    ///
    void enableValueDraw(bool _enb = true);

    ///
    void setPrecision(int _prec);

    ///
    void setBaseLine(double _bLine);

    ///
    void setColor(QColor _col);

    ///
    void setColorLessMin(QColor _col);

    ///
    void setColorOverMax(QColor _col);

    ///
    virtual void draw(QPainter &_p) = 0;

protected:
    //
    double value_;
    //
    double minValue_;
    //
    double maxValue_;
    //
    int x_;
    //
    int w_;
    //
    bool drawValue_;
    //
    int precision_;
    //
    QColor normalColor_;
    //
    QColor lessMinColor_;
    //
    QColor overMaxColor_;
    //
    double baseLine_;

    //
    SimpleGrid* grid_;

};

#endif // SIMPLE_BAR_H
