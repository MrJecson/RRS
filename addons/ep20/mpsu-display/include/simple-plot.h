#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <QWidget>

#include <QPicture>
#include <QPainter>

//class SimpleCanvas;
//class SimpleGrid;
//class SimpleBar;


//class SimplePlot : public QWidget
//{

//public:
//    ///
//    explicit SimplePlot(QWidget *parent = Q_NULLPTR);

//    ///
//    void resize(int _w, int _h);

//    ///
//    void attachCanvas(SimpleCanvas* _canvas);

//    ///
//    void replot();

//    ///
//    SimpleCanvas* canvas() const;

//signals:

//public slots:

//private:
//    //
//    SimpleCanvas* canvas_;

//};



//class SimpleCanvas : public QWidget
//{
//    Q_OBJECT

//public:
//    ///
//    explicit SimpleCanvas(SimplePlot* parent);

//    ///
//    void attachGrid(SimpleGrid* _grid);

//    ///
//    void attachBarItem(SimpleBar* _bar);

//    ///
//    SimpleGrid* grid() const;


//public slots:
//    ///
//    void paintEvent(QPaintEvent* e);

//private:
//    //
//    SimpleGrid* grid_;

//    //
//    QList<SimpleBar*> listItems_;
//};



//class SimpleGrid
//{
//public:
//    ///
//    explicit SimpleGrid(SimplePlot *plot);

//    ///
//    int height() const; // done

//    ///
//    void move(int _x, int _y); // done

//    ///
//    void resize(int _w, int _h); // done

//    ///
//    void setWorkPart(int _wY, int _wH); // delete ?

//    ///
//    void setPaddings(int _topP, int _botP); // done

//    ///
//    void setRange(double _min, double _max); // done

//    ///
//    double getCoeff() const; // done

//    ///
//    int getBottomLine() const; // done

//    ///
//    void setMajorStep(double _step); // done

//    ///
//    void setMinorNumber(int _number); // done

//    ///
//    void setMinorLength(int _len); // done

//    ///
//    void addMark(double _mrk); // done

//    ///
//    void addMarks(QVector<double> _mrks); // done

//    ///
//    virtual void drawGrid(QPainter &_p) = 0; // done

//    ///
//    void setHeader(const QString &header); // done

//    ///
//    void setDimension(const QString &dimension); // done

//    ///
//    void setPrecision(int _prec); // done

//    ///
//    void enableZeroPrecision(bool _zeroPrec = true); // done

//    ///
//    int mapToGrid_old(double _val);

//    ///
//    int mapAbsoluteToGrid(double _val);

//protected:
//    //
//    int x_;
//    //
//    int y_;
//    //
//    int w_;
//    //
//    int h_;

//    //
//    int topPadding_;
//    //
//    int botPadding_;


//    //
//    double min_;
//    //
//    double max_;

//    //
//    double majorStep_;
//    //
//    int majorLength_;

//    //
//    int minorNumber_;
//    //
//    int minorLength_;

//    //
//    double coeff_;

//    //
//    bool needRebuild_;

//    //
//    QString header_;

//    //
//    QString footer_;

//    //
//    QString dimension_;

//    //
//    int precision_;

//    //
//    bool zeroPrecision_;

//    //
//    QList<double> listMarks_;

//    QPicture pictureGrid;
//    QPicture pictureMarks;
//    QPicture pictureText;
//    QPicture pictureHeaders;
//    QPicture pictureLabels;
//};






class SimpleCanvas;
class SimpleGrid;
class NewBar;

class SimplePlot : public QWidget
{

public:
    ///
    explicit SimplePlot(QWidget *parent = Q_NULLPTR);

    ///
    void resize(int _w, int _h);

    ///
    void attachCanvas(SimpleCanvas* _canvas);

    ///
    void replot();

    ///
    SimpleCanvas* canvas() const;

signals:

public slots:

private:
    //
    SimpleCanvas* canvas_;

};




class SimpleCanvas : public QWidget
{
    Q_OBJECT

public:
    ///
    explicit SimpleCanvas(SimplePlot* parent);

    ///
    void attachGrid(SimpleGrid* _grid);

    ///
    void attachBarItem(NewBar* _bar);

    ///
    SimpleGrid* grid() const;


public slots:
    ///
    void paintEvent(QPaintEvent* e);

private:
    //
    SimpleGrid* grid_;

    //
    QList<NewBar*> listItems_;
};

#endif // SIMPLEPLOT_H
