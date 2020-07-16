#line 1
#include "simple-grids-sapsan.h"

#include <QPainter>
#include <QPicture>
#include <QFontMetrics>

#include <cmath>

#include "directives.h"

#include "simple-extra-draw.h"


void applyFont(int &_wd, int &_ht, const QString &_str, grid_data_t _d);
void applyHeight(int &_hg, const QString &_str, grid_data_t _d);
int strwidth(const QString &_str, const grid_data_t &_d);
QString longerNum(double _one, double _two, int _prec);
int upToBot(grid_data_t &_d);


SimpleGrid::SimpleGrid(SimplePlot *plot)
    : x_(0)
    , y_(0)
    , w_(plot->canvas()->width())
    , h_(plot->canvas()->height())
    , topPadding_(0)
    , botPadding_(0)
    , min_(0.0)
    , max_(10.0)
    , majorStep_(1.0)
    , majorLength_(w_)
    , minorNumber_(5)
    , minorLength_(w_/2)
    , coeff_(1.0)
    , needRebuild_(true)
    , header_("")
    , footer_("")
    , dimension_("")
    , precision_(0)
    , zeroPrecision_(0)
    , extraDraw_(Q_NULLPTR)
{
    plot->canvas()->attachGrid(this);
}

void SimpleGrid::drawGrid(QPainter &_p)
{
    if (needRebuild_)
    {        
        if (extraDraw_)
        {
            painterGrid_.begin(&picturePreExtra_);
            extraDraw_->preDraw(painterGrid_);
            painterGrid_.end();

            painterGrid_.begin(&picturePostExtra_);
            extraDraw_->postDraw(painterGrid_);
            painterGrid_.end();
        }

        painterGrid_.begin(&pictureGrid);
        painterGrid_.setPen(Qt::white);

        painterValues_.begin(&pictureText);
        painterValues_.setPen(Qt::white);
        painterValues_.setFont({"Sans", d.valuesTextSize});

        painterHeaders_.begin(&pictureHeaders);
        painterHeaders_.setFont({"Sans", d.headerFontSize});
        painterHeaders_.setPen(Qt::white);

        // -  -  -  -
        // Отрисовка вертикальной линии
        painterGrid_.drawLine(d.vLine);
        // -  -  -  -


        // -  -  -  -
        // Отрисовка шапки
        painterHeaders_.fillRect(x_ + d.headerPadding,
                                 y_,
                                 d.headerWidth,
                                 d.headerHeight,
                                 Qt::black);

        painterHeaders_.drawText(x_ + d.headerPadding,
                                 y_,
                                 d.headerWidth,
                                 d.headerHeight,
                                 Qt::AlignLeft,
                                 header_);
        // -  -  -  -


        // -  -  -  -
        // Отрисовка нижней шапки
        painterHeaders_.fillRect(x_ + d.footerPadding,
                                 y_ + h_ - d.footerHeight,
                                 d.footerWidth,
                                 d.footerHeight, Qt::black);

        painterHeaders_.drawText(x_ + d.footerPadding,
                                 y_ + h_ - d.footerHeight,
                                 d.footerWidth,
                                 d.footerHeight,
                                 Qt::AlignLeft, footer_);
        // -  -  -  -


        // -  -  -  -
        // Отрисовка единиц измерения
        painterValues_.fillRect(d.dimensionX,
                                 y_ + h_ - d.valuesTextHeight - d.footerHeight - botPadding_*d.dimensionFollowMinLimit,
                                 d.dimensionWidth,
                                 d.valuesTextHeight, Qt::black);

        painterValues_.drawText(d.dimensionX,
                                y_ + h_ - d.valuesTextHeight - d.footerHeight - botPadding_*d.dimensionFollowMinLimit,
                                d.dimensionWidth,
                                d.valuesTextHeight,
                                Qt::AlignRight,
                                dimension_);
        // -  -  -  -

        // Создаём счетчик значений
        double value = min_;


        // -  -  -  -
        // Отрисовка нижней "лишней" части сетки, для кратных мажорных значений
        if (d.tale.majorTale > ZERO_EPS)
        {
            value += abs(d.tale.minorTale);

            for (int i = 0; i < d.tale.minorNum; ++i)
            {
                int currY = mapToGrid(value);
                painterGrid_.drawLine(d.minorX,
                                      currY,
                                      d.minorX + minorLength_ - 1,
                                      currY);
                value += d.minorStep;
            }
        }
        // -  -  -  -

        // Счётчик минорных линий для отрисовки мажорных
        int tickCount = 0;


        // -  -  -  -
        // Отрисовка основной части сетки
        while (value < max_ + d.minorStep/50.0)
        {
            // Преобразованное значение реальной величины к сетке
            int currY = mapToGrid(value);

            // Если счетчик кратен количеству минорных шагов в мажорном
            if (!(tickCount%minorNumber_))
            {
                // Рисуем мажорную линию
                painterGrid_.drawLine(1 + d.majorLeftPadding, currY, majorLength_, currY);

                // Рисуем заливку текста
                painterValues_.fillRect
                        (
                            d.valuesTextX,          // x
                            currY - d.valuesTextY,  // y
                            d.valuesTextWidth,      // w
                            d.valuesTextHeight,     // h
                            Qt::black               // цвет
                        );

                // Рисуем текст
                painterValues_.drawText
                        (
                            d.valuesTextX,          // x
                            currY - d.valuesTextY,  // y
                            d.valuesTextWidth,      // w
                            d.valuesTextHeight,     // h
                            Qt::AlignRight,         // выравнивание
                            valStr_(value)          // текст числа
                        );
            }
            else // Если не кратен (просто минорная линия)
            {
                // Рисуем минорную линию
                painterGrid_.drawLine(d.minorX,
                                      currY,
                                      d.minorX + minorLength_ - 1,
                                      currY);
            }

            // Наращиваем счётчики "текущего значения" и "номера деления"
            value += d.minorStep;
            ++tickCount;
        }


        // -  -  -  -
        // Отрисовка "принудительной" нижней линии для "гибридных" графиков
        if (d.bottomLine)
        {
            int yyy = y_ + h_ - d.footerHeight - d.dimensionHeight*(!d.dimensionFollowMinLimit) - 1;
            painterGrid_.drawLine(x_, yyy, majorLength_, yyy);
            painterValues_.drawText(w_ - d.bottomLineValueWidth,
                                    yyy - d.valuesTextHeight,
                                    d.bottomLineValueWidth,
                                    yyy - d.valuesTextHeight,
                                    Qt::AlignRight,
                                    d.bottomLineValue);
        }
        // -  -  -  -


        // -  -  -  -
        // Отрисовка красных маркеров

        painterGrid_.setPen(Qt::red);
        for (double dbl : listMarks_)
        {
            if (inside(dbl, min_, max_))
            {
                int currY = mapToGrid(dbl);
                painterGrid_.drawLine(1, currY, majorLength_, currY);
            }
        }
        // -  -  -  -

        painterGrid_.end();
        painterValues_.end();
        painterHeaders_.end();

        // "Опускаем" флаг необходимости пересчёта сетки
        needRebuild_ = false;
    }

    // Поочерёдно накладываем отрисованные (кэшированные) "слои"
    // Важно отрисовывать их именно в этом порядке
    _p.drawPicture(0, 0, picturePreExtra_);
    _p.drawPicture(0, 0, pictureGrid);
    _p.drawPicture(0, 0, pictureText);
    _p.drawPicture(0, 0, pictureHeaders);
    _p.drawPicture(0, 0, picturePostExtra_);
}

void SimpleGrid::move(int _x, int _y)
{
    x_ = _x;
    y_ = _y;

    needRebuild_ = true;
}

void SimpleGrid::resize(int _w, int _h)
{
    w_ = _w;
    h_ = _h;

    majorLength_ = w_;

    calculateWorkHeight_();

    needRebuild_ = true;
}

int SimpleGrid::height() const
{
    return h_;
}

void SimpleGrid::setPaddings(int _topP, int _botP)
{
    topPadding_ = _topP;
    botPadding_ = _botP;

    calculateWorkHeight_();

    needRebuild_ = true;
}

void SimpleGrid::setTopPadding(int _topPad)
{
    topPadding_ = _topPad;

    calculateWorkHeight_();

    needRebuild_ = true;
}

void SimpleGrid::setBotPadding(int _botPad)
{
    botPadding_ = _botPad;

    calculateWorkHeight_();
    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setMajorStep(double _step)
{
    if (majorStep_ ==  _step)
        return;

    majorStep_ = _step;

    calculateMinorStep_();

    needRebuild_ = true;
}

void SimpleGrid::setMajorFromVerticalLine(int _offset)
{
    d.majorLeftPadding = d.vLine.x + d.vLine.lPad + _offset;

    needRebuild_ = true;
}

void SimpleGrid::setMinorLength(int _len)
{
    minorLength_ = _len;

    calculateMinor_();

    needRebuild_ = true;
}

void SimpleGrid::setMinorNumber(int _number)
{
    minorNumber_ = _number > 0? _number : 1;

    calculateMinorStep_();

    needRebuild_ = true;
}

void SimpleGrid::setMinorAlignment(Qt::Alignment _ali)
{
    d.minorAlignment = _ali;

//    applyMinorAlign_();
    calculateMinor_();

    needRebuild_ = true;
}

void SimpleGrid::setMinorLeftPadding(int _lpad)
{
//    applyMinorAlign_();

    d.minorLeftPadding = _lpad;

    calculateMinor_();

    needRebuild_ = true;
}

void SimpleGrid::setMinorFromVerticalLine(int _offset)
{
    if (d.minorAlignment != d.vLine.align)
        return;

    d.minorX = d.vLine.x + 1 + _offset;
    d.minorLeftPadding = 0;

    needRebuild_ = true;
}

void SimpleGrid::setRange(double _min, double _max)
{
    if (fequal(min_, _min) && fequal(max_, _max))
        return;

    min_ = _min;
    max_ = _max;
    calculateWorkHeight_();
    calculateRange_();
    calculateTale_();
    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::setMax(double _max)
{
    max_ = _max;
    calculateWorkHeight_();
    calculateRange_();
    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::setMin(double _min)
{
    min_ = _min;
    calculateWorkHeight_();
    calculateRange_();
    calculateTale_();
    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::setPrecision(int _prec)
{
    precision_ = _prec;

    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::enableZeroPrecision(bool _zeroPrec)
{
    zeroPrecision_ = _zeroPrec;

    calculateValuesRect_();

    needRebuild_ = true;
}




void SimpleGrid::setHeader(const QString &_head)
{
    header_ = _head;

    applyFont(d.headerWidth, d.headerHeight, header_, d);
    calculateWorkHeight_();

    needRebuild_ = true;
}

void SimpleGrid::setHeaderFontSize(int _sz)
{
    d.headerFontSize = _sz;

    applyFont(d.headerWidth, d.headerHeight, header_, d);
    applyFont(d.footerWidth, d.footerHeight, footer_, d);
    calculateWorkHeight_();
    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setHeaderLeftPadding(int _lPad)
{
    d.headerPadding = _lPad;

    needRebuild_ = true;
}

void SimpleGrid::setHeaderFromVerticalLine(int _offset)
{
    d.headerPadding = d.vLine.x + _offset;

    needRebuild_ = true;
}




void SimpleGrid::setFooter(const QString &_foot)
{
    footer_ = _foot;

    applyFont(d.footerWidth, d.footerHeight, footer_, d);
    calculateWorkHeight_();
    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setFooterFontSize(int _sz)
{
    // FIXME - реализовать метод и возможности
}

void SimpleGrid::setFooterLeftPadding(int _lPad)
{
    d.footerPadding = _lPad;

    needRebuild_ = true;
}


void SimpleGrid::setFooterFromVerticalLine(int _offset)
{
    // FIXME - реализовать метод и возможности
}




void SimpleGrid::setDimension(const QString &_dim)
{
    dimension_ = _dim;

    applyHeight(d.dimensionHeight, dimension_, d); // FIXME - выделить в метод (-1-)
    d.dimensionWidth = strwidth(dimension_, d); // FIXME - выделить в метод (-1-)
    calculateWorkHeight_();
    calculateVerticalLine_();
    calculateDimension_();

    needRebuild_ = true;
}

void SimpleGrid::enableDimensionFollowMinLimit(bool _enable)
{
    d.dimensionFollowMinLimit = _enable;
}

void SimpleGrid::setDimensionAlignment(Qt::Alignment _ali)
{
    d.dimensionAlignment = _ali;

    calculateDimension_();

    needRebuild_ = true;
}

void SimpleGrid::setDimensionHorPadding(int _hPad)
{
    d.dimensionHorPadding = _hPad;

    calculateDimension_();

    needRebuild_ = true;
}

void SimpleGrid::adjustDimensionAndValues()
{
    if (d.valuesTextAlign != d.dimensionAlignment)
        return;

    if (d.dimensionWidth > d.valuesTextWidth)
    {
        d.valuesTextHorPadding = d.dimensionWidth - d.valuesTextWidth + d.dimensionHorPadding;
    }
    else
    {
        d.dimensionHorPadding = d.valuesTextWidth - d.dimensionWidth + d.valuesTextHorPadding;
    }

    calculateValuesRect_();
    calculateDimension_();

    needRebuild_ = true;
}

void SimpleGrid::setVerticalLineAlignment(Qt::Alignment _ali)
{
    d.vLine.align = _ali;

//    applyHLineAlign_();
//    switch (_ali) {
//    case Qt::AlignLeft:
//        d.vLine.x = x_;
//        break;
//    case Qt::AlignCenter:
//        d.vLine.x = x_ + w_/2;
//        break;
//    case Qt::AlignRight:
//        d.vLine.x = w_ - 1;
//        break;
//    default:
//        d.vLine.x = x_;
//        d.vLine.align = Qt::AlignLeft;
//        break;
//    }
    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setVerticalLineLeftPadding(int _lPad)
{
    d.vLine.lPad = _lPad;

    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setVerticalLineTopPadding(int _tPad)
{
    d.vLine.topPad = _tPad;

    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setVerticalLineBottomPadding(int _bPad)
{
    d.vLine.botPad = _bPad;

    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setVerticalLineNextTovalues(int _offset)
{
    if (d.valuesTextAlign != d.vLine.align)
        return;

    d.vLine.x = d.valuesTextHorPadding + d.valuesTextWidth + _offset;
    d.vLine.lPad = 0;

    needRebuild_ = true;
}

int SimpleGrid::getVerticalLineX() const
{
    return d.vLine.x;
}

void SimpleGrid::setValuesTextSize(int _sz)
{
    d.valuesTextSize = _sz;

    d.valuesTextHeight = QFontMetrics({"Sans", _sz}).height();
    applyHeight(d.dimensionHeight, dimension_, d); // FIXME - выделить в метод (-1-)
    d.dimensionWidth = strwidth(dimension_, d); // FIXME - выделить в метод (-1-)
    d.bottomLineValueWidth = strwidth(d.bottomLineValue, d);
    calculateWorkHeight_();
    calculateValuesRect_();
    calculateDimension_();
    calculateVerticalLine_();

    needRebuild_ = true;
}

void SimpleGrid::setValuesAlignment(Qt::Alignment _ali)
{
    d.valuesTextAlign = _ali;

    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::setValuesHorPadding(int _hPad)
{
    d.valuesTextHorPadding = _hPad;

    calculateValuesRect_();

    needRebuild_ = true;
}

void SimpleGrid::setValuesVerPadding(int _vPad)
{
    d.valuesTextVerPadding = _vPad;

    calculateValuesRect_();

    needRebuild_ = true;
}

int SimpleGrid::getValuesWidth() const
{
    return d.valuesTextWidth;
}

void SimpleGrid::enableBottomLine(QString _val, bool _enbl)
{
    if (_enbl)
        showBottomLine(_val);
    else
        hideBottomLine();
}

void SimpleGrid::showBottomLine(QString _val)
{
    d.bottomLine = true;
    d.bottomLineValue = _val;

    d.bottomLineValueWidth = strwidth(_val, d);

    needRebuild_ = true;
}

void SimpleGrid::hideBottomLine()
{
    d.bottomLine = false;

    needRebuild_ = true;
}

void SimpleGrid::addMark(double _mrk)
{
    listMarks_.append(_mrk);

    needRebuild_ = true;
}

void SimpleGrid::addMarks(QVector<double> _mrks)
{
    for (double d : _mrks)
    {
        listMarks_.append(d);
    }

    needRebuild_ = true;
}

void SimpleGrid::clearMarks()
{
    listMarks_.clear();

    needRebuild_ = true;
}

void SimpleGrid::setExtraDraw(ExtraDraw *_exDr)
{
    if (extraDraw_)
        delete extraDraw_;
    extraDraw_ = _exDr;
}

double SimpleGrid::getCoeff() const
{
    return coeff_;
}

int SimpleGrid::getBottomLine() const
{
    return y_ + h_ - d.dimensionHeight - d.footerHeight - 1; // FIXME - вот тута может быть беда если есть "footer"
}

int SimpleGrid::mapToGrid(double _val)
{
    return qRound(/*Предварительно считать!!!*/h_ - botPadding_ + y_ - d.footerHeight - d.dimensionHeight - 1 - (_val - min_) * coeff_);
}

void SimpleGrid::calculateWorkHeight_()
{
    d.workHeight = h_ - topPadding_ - botPadding_ - d.headerHeight - d.footerHeight - d.dimensionHeight - d.valuesTextHeight;
    calculateCoeff_();
}

void SimpleGrid::calculateRange_()
{
    d.range = qAbs(max_ - min_);
    calculateCoeff_();
}

void SimpleGrid::calculateMinorStep_()
{
    d.minorStep = majorStep_/static_cast<double>(minorNumber_);
    calculateTale_();
}

void SimpleGrid::calculateCoeff_()
{
    coeff_ = d.workHeight/d.range;
}

void SimpleGrid::calculateTale_()
{
    d.tale.majorTale= fmod(abs(min_) + 0.00000000001, majorStep_);
    if (d.tale.majorTale> ZERO_EPS)
    {
        if (min_ > 0)
        {
            d.tale.majorTale = majorStep_ - d.tale.majorTale;
            d.tale.majorTale += 0.00000000001;
        }

        d.tale.minorTale= fmod(d.tale.majorTale, d.minorStep);
        d.tale.minorNum = abs(d.tale.majorTale/d.minorStep);
    }
}

void SimpleGrid::calculateValuesRect_()
{
    d.valuesTextWidth = QFontMetrics({"Sans", d.valuesTextSize}).width(longerNum(min_, max_, precision_)) + 2;
    applyValuesAlign_();
    d.valuesTextX += d.valuesTextHorPadding;
    d.valuesTextY = d.valuesTextHeight - d.valuesTextVerPadding;
}

void SimpleGrid::calculateDimension_()
{
    switch (d.dimensionAlignment)
    {
    case Qt::AlignLeft: /* WARN FIXME */
        d.dimensionX = x_;
        break;
    case Qt::AlignCenter:
        d.dimensionX = x_ + (w_ - d.dimensionWidth)/2;
        break;
    default:
        d.dimensionX = x_ + w_ - d.dimensionWidth;
        d.dimensionAlignment = Qt::AlignRight;
        break;
    }

    d.dimensionX += d.dimensionHorPadding;
}

void SimpleGrid::calculateVerticalLine_()
{
//    painterGrid_.drawLine(x_,
//                          y_ + d.vLine.topPad,
//                          x_,
//                          y_ + h_ - d.dimensionHeight*upToBot(d) - d.footerHeight - d.vLine.botPad - 1);
    applyHLineAlign_();
    d.vLine.x += d.vLine.lPad;
    d.vLine.y1 = y_ + d.vLine.topPad;
    d.vLine.y2 = y_ + h_ - d.vLine.botPad - d.dimensionHeight*upToBot(d) - d.footerHeight - 1;
}

void SimpleGrid::calculateMinor_()
{
    applyMinorAlign_();

    d.minorX += d.minorLeftPadding;
}

void SimpleGrid::applyMinorAlign_()
{
    switch (d.minorAlignment) {
    case Qt::AlignLeft:
        d.minorX = x_;
        break;
    case Qt::AlignCenter:
        d.minorX = x_ + (w_ - minorLength_)/2;
        break;
    case Qt::AlignRight:
        d.minorX = x_ + w_ - minorLength_;
        break;
    default:
        d.minorX = x_;
        d.minorAlignment = Qt::AlignLeft;
        break;
    }
}

void SimpleGrid::applyHLineAlign_()
{
    switch (d.vLine.align) {
    case Qt::AlignLeft:
        d.vLine.x = x_;
        break;
    case Qt::AlignCenter:
        d.vLine.x = x_ + w_/2;
        break;
    case Qt::AlignRight:
        d.vLine.x = w_ - 1;
        break;
    default:
        d.vLine.x = x_;
        d.vLine.align = Qt::AlignLeft;
        break;
    }
}

void SimpleGrid::applyValuesAlign_() /* WARN FIXME */
{
    switch (d.valuesTextAlign) {
    case Qt::AlignLeft:
        d.valuesTextX = x_;
        break;
    case Qt::AlignCenter:
        d.valuesTextX = x_ + (w_ - d.valuesTextWidth)/2;
        break;
    case Qt::AlignRight:
        d.valuesTextX = x_ + w_ - d.valuesTextWidth;
        break;
    default:
        d.valuesTextAlign = Qt::AlignRight;
        d.valuesTextX = x_ + w_ - d.valuesTextWidth;
        break;
    }
}

QString SimpleGrid::valStr_(double _val) const
{
    return SNUM(_val, 'f', precision_*(!is_zero(_val) || zeroPrecision_));
}











void applyFont(int &_wd, int &_ht, const QString &_str, grid_data_t _d)
{
    _wd = 0;
    _ht = 0;
    if (!_str.isEmpty())
    {
        QFontMetrics m({"Sans", _d.headerFontSize});
        _wd = m.width(_str);
        _ht = m.height();
        if (_str.contains('\n'))
            _ht *= (_str.count('\n') + 1);
    }
}


void applyHeight(int &_hg, const QString &_str, grid_data_t _d)
{
    _hg = 0;
    if (!_str.isEmpty())
    {
        _hg = QFontMetrics({"Sans", _d.valuesTextSize}).height();
    }
}


int strwidth(const QString &_str, const grid_data_t &_d)
{
    return QFontMetrics({"Sans", _d.valuesTextSize}).width(_str);
}


QString longerNum(double _one, double _two, int _prec)
{
    QString oneStr(QString::number(_one, 'f', _prec));
    QString twoStr(QString::number(_two, 'f', _prec));
    if (oneStr.length() > twoStr.length())
        return oneStr;
    return twoStr;
}


int upToBot(grid_data_t &_d)
{
    return !_d.dimensionFollowMinLimit && (!_d.bottomLine || _d.bottomLine);
}




