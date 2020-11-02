#ifndef SIMPLE_EXTRA_DRAW_H
#define SIMPLE_EXTRA_DRAW_H

class SimpleGrid;

class QPainter;

class ExtraDraw
{
public:
    ///
    ExtraDraw(SimpleGrid* _grid);
    ///
    virtual ~ExtraDraw();

    ///
    virtual void preDraw(QPainter &_p);
    ///
    virtual void postDraw(QPainter &_p);

protected:
    SimpleGrid* grid_;
};

#endif // SIMPLE_EXTRA_DRAW_H
