#include "simple-extra-draw.h"

#include <QPainter>

ExtraDraw::ExtraDraw(SimpleGrid *_grid)
    : grid_(_grid)
{

}

ExtraDraw::~ExtraDraw()
{

}

void ExtraDraw::preDraw(QPainter &_p)
{
    Q_UNUSED(_p);
}

void ExtraDraw::postDraw(QPainter &_p)
{
    Q_UNUSED(_p);
}
