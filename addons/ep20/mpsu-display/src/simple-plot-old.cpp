//-----------------------------------------------------------------------------
// KILL
//-----------------------------------------------------------------------------
///*!
// *  \file
// *  \brief Класс обычного графика
// *  \copyright РГУПС, ВЖД
// *  \author Ковшиков С. В.
// *  \date 04/04/2017
// */

//#include "simple-plot-old.h"

//#include "simple-items-old.h"
//#include <QLabel>
//#include <QPainter>
//#include <math.h>

//// Расстояние между гистграммами по умолчанию
//const int CHILD_Y_PADDING = 5;

//const int MINOR_L= 70;
//const int MAJOR_L= 90;



////-----------------------------------------------------------------------------
//// КОНСТРУКТОР
////-----------------------------------------------------------------------------
//SimplePlotOld::SimplePlotOld(QString header, QString dimension, QWidget *parent)
//    : QWidget(parent)
//    , min_(0)
//    , max_(10)
//    , majorStep_(5)
//    , minorLength_(MINOR_L)
//    , coeff_(1)
//    , padding_(1)
//    , dimension_(dimension)
//{
//    this->setAutoFillBackground(true);
//    this->setPalette(QPalette(QColor(0, 0, 0)));
//    this->resize(150, 488);

//    // Создаем все виджеты
//    labelHeader_ = new QLabel(header, this);
//    labelHeader_->setStyleSheet("background: #000000;"
//                                "color: white");
//    labelHeader_->setFont(QFont("Arial", 11));
//    labelHeader_->setAlignment(Qt::AlignCenter);
//    labelHeader_->resize(130, 20);

//    labelGrid_ = new QLabel(this);
//    labelGrid_->setStyleSheet("background: black;");
//    labelGrid_->resize(130, labelGrid_->height());

//    labelFooter_ = new QLabel("power      kW", this);
//    labelFooter_->setStyleSheet("background: #000000;"
//                                "color: white;");
//    labelFooter_->setAlignment(Qt::AlignCenter);
//    labelFooter_->setFont(QFont("Arial", 11));
//    labelFooter_->resize(130, 20);

//    // Упорядочиваем все виджеты
//    arrangeChildren_();

//    // Устанавливаем диапазон по умолчанию
//    setRange(min_, max_);
//}



////-----------------------------------------------------------------------------
//// ДЕСТРУКТОР
////-----------------------------------------------------------------------------
//SimplePlotOld::~SimplePlotOld()
//{

//}



////-----------------------------------------------------------------------------
//// Метод прикрепления гистограммы на график
////-----------------------------------------------------------------------------
//void SimplePlotOld::attachItem(SimpleBarOld* item)
//{
//    item->setParent(labelGrid_);
//    item->setCoeff(coeff_);
//    item->setBaseLine(labelGrid_->height() - 1);
//    item->setValue(item->value());

//    listItems_.append(item);

//    replot();
//}



////-----------------------------------------------------------------------------
//// Установка расстояния между гистограммами
////-----------------------------------------------------------------------------
//void SimplePlotOld::setPadding(int padding)
//{
//    padding_ = padding;
//    replot();
//}



////-----------------------------------------------------------------------------
//// Установка диапазона шкалы
////-----------------------------------------------------------------------------
//void SimplePlotOld::setRange(double min, double max)
//{
//    min_ = min;
//    max_ = max;
//    replot(); // delete ??? !!!
//}



////-----------------------------------------------------------------------------
//// Получение диапазона шкалы
////-----------------------------------------------------------------------------
//double SimplePlotOld::getRange()
//{
//    return max_ - min_;
//}



////-----------------------------------------------------------------------------
//// Установить размер старшего шага
////-----------------------------------------------------------------------------
//void SimplePlotOld::setMajorStep(int step)
//{
//    majorStep_ = step;
//    generateGrid_(labelGrid_, min_, max_);
//}



////-----------------------------------------------------------------------------
//// Установить размер старшего шага
////-----------------------------------------------------------------------------
//void SimplePlotOld::setMinorLength(int length)
//{
//    minorLength_ = length;
//    generateGrid_(labelGrid_, min_, max_);
//}



////-----------------------------------------------------------------------------
//// Установка заголовка
////-----------------------------------------------------------------------------
//void SimplePlotOld::setTitle(QString tit)
//{
//    labelHeader_->setText(tit);
//}



////-----------------------------------------------------------------------------
//// Установка единиц измерения
////-----------------------------------------------------------------------------
//void SimplePlotOld::setDimension(QString dimension)
//{
//    dimension_ = dimension;
//}



////-----------------------------------------------------------------------------
//// Перестройка графика
////-----------------------------------------------------------------------------
//void SimplePlotOld::replot()
//{
//    // Заново генерируем шкалу
//    generateGrid_(labelGrid_, min_, max_);

//    // Создаем временный указатель (только для простоты обращения)
//    SimpleBarOld* si = Q_NULLPTR;

//    int summWidth = 0;

//    // Работаем с гистограммами
//    for (int i = 0; i < listItems_.count(); i++)
//    {
//        si = listItems_.at(i);
//        // Учитываем расстояние между гистограммами
//        summWidth += padding_;
//        // Смещаем гистограмму в ноль графика
//        si->move(summWidth, si->pos().y());
//        // Учитываем ширину гистограммы
//        summWidth += si->width();
//    }

//    // Если всего одна гистограмма delete ??? mb delete or abstract List ???
//                    // because we don't need this in this project ???
//    if (listItems_.count() == 1)
//    {
//        double value = listItems_.at(0)->value();
//        // "Собираем" строку для нижней надписи
//        QString foo = qAbs(value) < 0.005? "0" : QString::number(qAbs(value),
//                                      'f', 2);
//        foo.append(" ");
//        foo.append(dimension_);

//        labelFooter_->setText(foo);
//    }
//    else
//    {
//        labelFooter_->setText(dimension_);
//    }
//}



////-----------------------------------------------------------------------------
////
////-----------------------------------------------------------------------------
//void SimplePlotOld::arrangeChildren_()
//{
//    // Положение верхней надписи
//    int fooX = (this->width() - labelHeader_->width()) / 2;
//    int fooY = CHILD_Y_PADDING;
//    labelHeader_->move(fooX, fooY);

//    // Положение сетки
//    fooX = (this->width() - labelGrid_->width()) / 2;
//    fooY = labelHeader_->pos().y() + labelHeader_->height() + CHILD_Y_PADDING;
//    labelGrid_->move(fooX, fooY);

//    // Размер сетки
//    int fooH = this->height() - CHILD_Y_PADDING * 4 -
//            labelHeader_->height() - labelFooter_->height();

//    labelGrid_->resize(labelGrid_->width(), fooH);

//    // Положение нижней надписи
//    fooX = (this->width() - labelFooter_->width()) / 2;
//    fooY = this->height() - CHILD_Y_PADDING - labelFooter_->height();
//    labelFooter_->move(fooX, fooY);
//}



////-----------------------------------------------------------------------------
//// Генерация шкалы
////-----------------------------------------------------------------------------
//void SimplePlotOld::generateGrid_(QLabel* &lab, double min, double max)
//{
//    // Создаем и настраиваем изображение и художника
//    QImage img(lab->size(), QImage::Format_ARGB32_Premultiplied);
//    img.fill(Qt::transparent);
//    QPixmap pix = QPixmap::fromImage(img);
//    QPainter p(&pix);
//    p.setPen(QPen(QBrush(Qt::white), 1));
//    p.setFont(QFont("Arial", 11));
//    // Рисуем ось шкалы
//    p.drawLine(0, 5, 0, lab->height());

//    // Реальная цена минорного деления
//    double minorStep;
//    // Пиксельная цена минорного деления
//    int minorTick;
//    // Счетчик делений delete modify ??? because we can't use values < 0 !!!
//    int tickCount = 0;
//    // Рабочая часть холста для отрисовки
//    int fooH = lab->height() - 1;

//    // Вычисление реальной цены минорного деления
//    minorStep = calculateStep(min, max);
//    // Вычисление пиксельной цены деления минорного деления
//    minorTick = (lab->height() - 15) * minorStep / (max - min);

//    // Вычисляем коэффициент преобразования значения
//    coeff_ = 1.0 * minorTick / minorStep;

//    // Рисуем шкалу
//    for (int i = min; i < lab->height() - 50; i += minorTick)
//    {
//        // Если счетчик кратен 5
//        if (tickCount%majorStep_ == 0)
//        {
//            // Рисуем мажорную линию
//            p.drawLine(0, fooH - i, MAJOR_L, fooH - i);
//            // Рисуем текст со значением
//            p.drawText(MAJOR_L + 5,
//                       fooH - i + ((i != 0) ? 5 : 0),
//                       QString().number(tickCount * minorStep));
//        }
//        else
//        {
//            // Рисуем минорную линию
//            p.drawLine(0, fooH - i, minorLength_, fooH - i);

//        }
//        // Увеличиваем счетчик delete modify ??? only from 0
//        tickCount++;
//    }
//    p.end();

//    // Устанавливаем пиксмэп
//    lab->setPixmap(pix);
//}



////-----------------------------------------------------------------------------
//// Метод расчёта цены деления
////-----------------------------------------------------------------------------
//double SimplePlotOld::calculateStep(double min, double max)
//{
//    // ***********************************************
//    // *  Данный метод является довольно скверным и  *
//    // * будет переделан, если появится цель сделать *
//    // *        универсальный класс графика.         *
//    // ***********************************************
//    double foo = abs(max - min);

//    if (foo < 1)
//    {
//        return 0.1;
//    }
//    if (foo < 5)
//    {
//        return 0.2;
//    }
//    if (foo < 20)
//    {
//        return 1;
//    }
//    if (foo < 50)
//    {
//        return 2.5;
//    }
//    if (foo < 100)
//    {
//        return 5;
//    }
//    if (foo < 200)
//    {
//        return 10;
//    }
//    if (foo < 400)
//    {
//        return 20;
//    }
//    if (foo < 500)
//    {
//        return 25;
//    }
//    if (foo < 1000)
//    {
//        return 50;
//    }

//    return 500;
//}
