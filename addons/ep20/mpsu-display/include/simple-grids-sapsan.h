#ifndef SIMPLE_GRIDS_SAPSAN_H
#define SIMPLE_GRIDS_SAPSAN_H

#include "simple-plot.h"


struct grid_data_t
{
    struct v_line_t
    {
        int x, y1, y2, lPad, topPad, botPad, align;

        v_line_t() : x(0), y1(0), y2(0), lPad(0),
            topPad(0), botPad(0), align(Qt::AlignLeft){ }

        inline operator QLine(){return {x, y1, x, y2};}
    };

    struct tale_t
    {
        double majorTale;
        double minorTale;
        int minorNum;
        tale_t() : majorTale(0.0), minorTale(0.0), minorNum(0) {}
    };

    struct values_t
    {
        int x{0};
        int y{0};
        int w{0};
        int h{17}; // FIXME - считать в конструкторе !!!
        int fontSize{10};
        Qt::Alignment hAlign{Qt::AlignRight};
        int horPad{0};
        int verPad{0};
    };

    struct dimension_t
    {
        int x{0};
        // int y; // FIXME - добавить и считать
        int w{0};
        int h{0};
        // int fontSize; // FIXME - добавить и считать
        Qt::Alignment hAlign{Qt::AlignRight};
        int horPad{0};
        // int verPad; // FIXME - добавить и считать
        bool followMinLimit{false};
    };

    struct header_t
    {
        int w;
        int h;
        int fontSize;
        int leftPadding;
    };

    v_line_t    vLine;

    tale_t      tale;

    values_t    values;

    int     majorLeftPadding;

    int     minorAlignment;
    int     minorLeftPadding;
    int     minorX;

    int     workHeight;
    double  range;
    double  minorStep;

    int     valuesTextX;
    int     valuesTextY;
    int     valuesTextSize;
    int     valuesTextHeight;
    int     valuesTextWidth;
    int     valuesTextAlign;
    int     valuesTextHorPadding;
    int     valuesTextVerPadding;

    int     dimensionX;
    int     dimensionHeight;
    int     dimensionWidth;
    bool    dimensionFollowMinLimit;
    int     dimensionAlignment;
    int     dimensionHorPadding;

    int     headerFontSize;
    int     headerWidth;
    int     headerHeight;
    int     headerPadding;

    //        int footerFontSize - FIXME - надо бы замутить наверное
    int     footerWidth;
    int     footerHeight;
    int     footerPadding;

    bool    bottomLine;
    QString bottomLineValue;
    int     bottomLineValueWidth;

    grid_data_t()
        : majorLeftPadding(0)

        , minorAlignment(Qt::AlignLeft)
        , minorLeftPadding(0)
        , minorX(0)

        , workHeight(0)
        , range(0.0)
        , minorStep(0.0)

        , valuesTextX(0)
        , valuesTextY(0)
        , valuesTextSize(10)
        , valuesTextHeight(17)
        , valuesTextWidth(0)
        , valuesTextAlign(Qt::AlignRight)
        , valuesTextHorPadding(0)
        , valuesTextVerPadding(0)

        , dimensionX(0)
        , dimensionHeight(0)
        , dimensionWidth(0)
        , dimensionFollowMinLimit(false)
        , dimensionAlignment(Qt::AlignRight)
        , dimensionHorPadding(0)

        , headerFontSize(10)
        , headerWidth(0)
        , headerHeight(0)
        , headerPadding(0)

        , footerWidth(0)
        , footerHeight(0)
        , footerPadding(0)

        , bottomLine(false)
        , bottomLineValue("0")
        , bottomLineValueWidth(QFontMetrics({"Sans", valuesTextWidth})
                               .width(bottomLineValue))
    {

    }
};



class ExtraDraw;


class SimpleGrid
{
public:
    ///
    explicit SimpleGrid(SimplePlot* plot);

    ///
    void drawGrid(QPainter &_p);

    ///
    void move(int _x, int _y);

    ///
    void resize(int _w, int _h);

    ///
    int height() const;

    ///
    void setPaddings(int _topP, int _botP);
    void setTopPadding(int _topPad);
    void setBotPadding(int _botPad);

    ///
    void setMajorStep(double _step);
    void setMajorFromVerticalLine(int _offset = 0);

    ///
    void setMinorLength(int _len);
    void setMinorNumber(int _number);
    void setMinorAlignment(Qt::Alignment _ali);
    void setMinorLeftPadding(int _lpad);
    void setMinorFromVerticalLine(int _offset = 0);


    ///
    void setRange(double _min, double _max);
    void setMax(double _max);
    void setMin(double _min);


    ///
    void setPrecision(int _prec);
    void enableZeroPrecision(bool _zeroPrec = true);


    ///
    void setHeader(const QString &_head);
    void setHeaderFontSize(int _sz);
    void setHeaderLeftPadding(int _lPad);
    void setHeaderFromVerticalLine(int _offset = 0);


    ///
    void setFooter(const QString &_foot);
    void setFooterFontSize(int _sz);
    void setFooterLeftPadding(int _lPad);
    void setFooterFromVerticalLine(int _offset = 0);


    ///
    void setDimension(const QString &_dim);
    void enableDimensionFollowMinLimit(bool _enable = true);
    void setDimensionAlignment(Qt::Alignment _ali);
    void setDimensionHorPadding(int _hPad);
    void adjustDimensionAndValues();


    ///
    void setVerticalLineAlignment(Qt::Alignment _ali);
    void setVerticalLineLeftPadding(int _lPad);
    void setVerticalLineTopPadding(int _tPad);
    void setVerticalLineBottomPadding(int _bPad);
    void setVerticalLineNextTovalues(int _offset = 0);

    int getVerticalLineX() const;

    ///
    void setValuesTextSize(int _sz);
    void setValuesAlignment(Qt::Alignment _ali);
    void setValuesHorPadding(int _hPad);
    void setValuesVerPadding(int _vPad);

    int getValuesWidth() const;


    ///
    void enableBottomLine(QString _val = "0", bool _enbl = true);
    void showBottomLine(QString _val = QString("0"));
    void hideBottomLine();

    ///
    void addMark(double _mrk);
    void addMarks(QVector<double> _mrks);
    void clearMarks();

    ///
    void setExtraDraw(ExtraDraw* _exDr);

    ///
    double getCoeff() const;

    ///
    int getBottomLine() const; // REALIZE

    ///
    int mapToGrid(double _val);


private:
    //
    grid_data_t d;

    QPainter painterGrid_;
    QPainter painterValues_;
    QPainter painterHeaders_;
    QPainter painterLabels_;

    void calculateWorkHeight_();
    void calculateRange_();
    void calculateMinorStep_();
    void calculateCoeff_();
    void calculateTale_();
    void calculateValuesRect_();
    void calculateDimension_();
    void calculateVerticalLine_();
    void calculateMinor_();

    inline void applyMinorAlign_();
    inline void applyHLineAlign_();
    inline void applyValuesAlign_();

    ///
    QString valStr_(double _val) const;

    //
    int x_;
    //
    int y_;
    //
    int w_;
    //
    int h_;

    //
    int topPadding_;
    //
    int botPadding_;


    //
    double min_;
    //
    double max_;

    //
    double majorStep_;
    //
    int majorLength_;

    //
    int minorNumber_;
    //
    int minorLength_;

    //
    double coeff_;

    //
    bool needRebuild_;

    //
    QString header_;

    //
    QString footer_;

    //
    QString dimension_;

    //
    int precision_;

    //
    bool zeroPrecision_;

    //
    QList<double> listMarks_;

    QPicture pictureGrid;
    QPicture pictureMarks;
    QPicture pictureText;
    QPicture pictureHeaders;
    QPicture pictureLabels;

    ExtraDraw* extraDraw_;

    QPicture picturePreExtra_;
    QPicture picturePostExtra_;
};

#endif // SIMPLE_GRIDS_SAPSAN_H
