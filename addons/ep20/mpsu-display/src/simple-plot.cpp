#include "simple-plot.h"

#include "simple-bar.h"
#include "simple-grids-sapsan.h"

//#include <QPainter>

#include <cmath>

#include <QFontMetrics>

#define EPS  0.000001
#define EPS1 0.000001
#define EPS2 0.999999

//bool isMult(double _fst, double _scn);



//SimplePlot::SimplePlot(QWidget *parent)
//    : QWidget(parent)
//    , canvas_(new SimpleCanvas(this))
//{
//    setStyleSheet("background: green;"); // delete
//}

//void SimplePlot::resize(int _w, int _h)
//{
//    this->QWidget::resize(_w, _h);
//    canvas_->resize(_w, _h);
//}

//void SimplePlot::attachCanvas(SimpleCanvas *_canvas)
//{
//    delete canvas_;
//    canvas_ = _canvas;
//}

//void SimplePlot::replot()
//{
//    canvas_->update();
//}

//SimpleCanvas *SimplePlot::canvas() const
//{
//    return canvas_;
//}




////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################


//SimpleCanvas::SimpleCanvas(SimplePlot *parent)
//    : QWidget(parent)
//    , grid_(Q_NULLPTR)
//{

//}

//void SimpleCanvas::attachGrid(SimpleGrid * _grid)
//{
//    grid_ = _grid;
//}

//void SimpleCanvas::attachBarItem(SimpleBar *_bar)
//{
//    listItems_.append(_bar);
//}

//SimpleGrid *SimpleCanvas::grid() const
//{
//    return grid_;
//}

//void SimpleCanvas::paintEvent(QPaintEvent *e)
//{
//    Q_UNUSED(e);

//    QPainter p(this);
////    p.setRenderHint(QPainter::NonCosmeticDefaultPen);
//    if (grid_)
//        grid_->drawGrid(p);
//    for (SimpleBar* item : listItems_)
//    {
//        item->draw(p);
//    }

////    p.drawLine(0, 0, 30, 0);

////    p.drawLine(0, this->height() - 1, 30, this->height() - 1);

//    p.end();
//}




////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################
////#############################################################################

//struct grid_label_t
//{
//    int x;
//    int y;
//    QString labelText_;
//};

//SimpleGrid::SimpleGrid(SimplePlot *plot)
//    : x_(0)
//    , y_(0)
//    , w_(plot->canvas()->width())
//    , h_(plot->canvas()->height())
//    , topPadding_(0)
//    , botPadding_(0)
//    , min_(0.0)
//    , max_(10.0)
//    , majorStep_(1.0)
//    , majorLength_(w_)
//    , minorNumber_(5)
//    , minorLength_(w_/2)
//    , coeff_(1.0)
//    , needRebuild_(true)
//    , header_("")
//    , footer_("")
//    , dimension_("")
//    , precision_(0)
//{
//    plot->canvas()->attachGrid(this);
//}

//int SimpleGrid::height() const
//{
//    return h_;
//}

//void SimpleGrid::move(int _x, int _y)
//{
//    x_ = _x;
//    y_ = _y;

//    needRebuild_ = true;
//}

//void SimpleGrid::resize(int _w, int _h)
//{
//    w_ = _w;
//    h_ = _h;

//    majorLength_ = w_;

//    needRebuild_ = true;
//}

//void SimpleGrid::setPaddings(int _topP, int _botP)
//{
//    topPadding_ = _topP;
//    botPadding_ = _botP;

//    needRebuild_ = true;
//}

//void SimpleGrid::setRange(double _min, double _max)
//{
//    min_ = _min;
//    max_ = _max;

//    needRebuild_ = true;
//}

//double SimpleGrid::getCoeff() const
//{
//    return coeff_;
//}

//int SimpleGrid::getBottomLine() const
//{
//    return y_ + h_;
//}

//void SimpleGrid::setMajorStep(double _step)
//{
//    majorStep_ = _step;

//    needRebuild_ = true;
//}

//void SimpleGrid::setMinorNumber(int _number)
//{
//    minorNumber_ = _number;

//    needRebuild_ = true;
//}

//void SimpleGrid::setMinorLength(int _len)
//{
//    minorLength_ = _len;

//    needRebuild_ = true;
//}

//void SimpleGrid::addMark(double _mrk)
//{
//    listMarks_.append(_mrk);

//    needRebuild_ = true;
//}

//void SimpleGrid::addMarks(QVector<double> _mrks)
//{
//    for (double d : _mrks)
//    {
//        listMarks_.append(d);
//    }

//    needRebuild_ = true;
//}

//void SimpleGrid::setHeader(const QString &header)
//{
//    header_ = header;

//    needRebuild_ = true;
//}

//void SimpleGrid::setDimension(const QString &dimension)
//{
//    dimension_ = dimension;

//    needRebuild_ = true;
//}

//void SimpleGrid::setPrecision(int _prec)
//{
//    precision_ = _prec;

//    needRebuild_ = true;
//}

//void SimpleGrid::enableZeroPrecision(bool _zeroPrec)
//{
//    zeroPrecision_ = _zeroPrec;
//}

//int SimpleGrid::mapToGrid_old(double _val)
//{
////    return y_ + h_ - botPadding_ -  (_val - min_)*coeff_;
//    return qRound(y_ + h_ - botPadding_ -  (_val - min_)*coeff_);
//}

//int SimpleGrid::mapAbsoluteToGrid(double _val)
//{
//    return qRound(y_ + h_ - botPadding_ -  _val*coeff_);
//}









//bool isMult(double _fst, double _scn)
//{
//    double rou = _fst;
//    double fmo = fmod(rou, _scn);
//    double qab = qAbs(fmo);

//    return (qab < EPS1 || qab > EPS2);
////    return (qAbs(fmod(round(_fst), _scn)) < EPS);
//}


SimplePlot::SimplePlot(QWidget *parent)
    : QWidget(parent)
    , canvas_(new SimpleCanvas(this))
{
//    setStyleSheet("background: orange;"); // delete
}

void SimplePlot::resize(int _w, int _h)
{
    this->QWidget::resize(_w, _h);
    canvas_->resize(_w, _h);
}

void SimplePlot::attachCanvas(SimpleCanvas *_canvas)
{
    delete canvas_;
    canvas_ = _canvas;
}

void SimplePlot::replot()
{
    canvas_->update();
}

SimpleCanvas *SimplePlot::canvas() const
{
    return canvas_;
}




//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################


SimpleCanvas::SimpleCanvas(SimplePlot *parent)
    : QWidget(parent)
    , grid_(Q_NULLPTR)
{

}

void SimpleCanvas::attachGrid(SimpleGrid * _grid)
{
    grid_ = _grid;
}

void SimpleCanvas::attachBarItem(NewBar *_bar)
{
    listItems_.append(_bar);
}

SimpleGrid *SimpleCanvas::grid() const
{
    return grid_;
}

void SimpleCanvas::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);
//    p.setRenderHint(QPainter::NonCosmeticDefaultPen);
    if (grid_)
        grid_->drawGrid(p);
    for (NewBar* item : listItems_)
    {
        item->draw(p);
    }

//    p.drawLine(0, 0, 30, 0);

//    p.drawLine(0, this->height() - 1, 30, this->height() - 1);

    p.end();
}
