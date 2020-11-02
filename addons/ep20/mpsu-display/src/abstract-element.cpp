//-----------------------------------------------------------------------------
//
//      Абстрактный класс элементов индикации/управления
//      (c) РГУПС, ВЖД 17/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс элементов управления/индикации
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 17/04/2017
 */

#include "abstract-element.h"

#include "element-nodraw-engine.h"

#include <QPainter>
#include <QTimer>

#include "CfgReader.h"


// Размер элемента
const int SIZE = 30;

// Интервал мигания по умолчанию
constexpr int DEF_BLINK_INTERVAL = 250;

// Умолч. ожидание ответа до отключения мигания и отмены заданного состояния
constexpr int DEF_RESPONSE_WAITING = 15000;

// TODO - -(.)^(.)-
//
constexpr int DEF_UNTOUCHABLE = 5;

//
constexpr int DEF_REQ_INTERVAL = 100;

//
constexpr int DEF_UNTOUCHABLE_TIME = 500;

// Массив цветов включенных элементов
const QStringList COL_ON = {"#ffffff", "#00ff00", "#0096ff",
                            "#ff9600", "#ffff00", "#ff0000"};

// Массив цветов выключенных элементов
const QStringList COL_OFF = {"#ffffff", "#ffffff", "#0096ff",
                             "#ff9600", "#ffff00", "#ff0000"};

// Массив массивов (выше)
const QList<QStringList> LIST = QList<QStringList>() << COL_OFF << COL_ON;



//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
AbstractElement::AbstractElement(QString name, bool state, Elements::IconType type,
                                 QWidget *parent)
    : QLabel(parent)
    , name_(name)
    , type_(type)
    , state_(state)
    , refState_(state_)
    , curBlocked_(false)
    , refBlocked_(false)
    , timerBlink_(Q_NULLPTR)
    , timerBlinkInterval_(DEF_BLINK_INTERVAL)
    , responseWaitingConstant_(DEF_RESPONSE_WAITING)
    , currentWaiting_(0)
    , blink_(false)
    , untouchableTimeConstant_(DEF_UNTOUCHABLE)
    , untouchableCounter_(0)
    , canvas_(Q_NULLPTR)
    , firstUpdate_(true)
    , drawEngine_(new ElementNoDrawEngine(this))
    , manual_(false)
    , manualBlock_(false)
{
    CfgReader cfg;

    if (cfg.load("../cfg/display/display-core.xml"))
    {
        cfg.getInt("ControlElements", "BlinkInterval", timerBlinkInterval_);
        cfg.getInt("ControlElements", "ResponseWaiting", responseWaitingConstant_);
        int interval = DEF_REQ_INTERVAL;
        int untouchableTime = DEF_UNTOUCHABLE_TIME;
        cfg.getInt("Core", "RequestTimerInterval", interval);
        cfg.getInt("ControlElements", "UntouchableTime", untouchableTime);
        if (untouchableTime > interval)
        {
            untouchableTimeConstant_ = untouchableTime/interval;
        }
    }

    this->resize(SIZE, SIZE);
    this->setMaximumSize(SIZE, SIZE);
    this->setMinimumSize(SIZE, SIZE);

    setBoxSize(width() - 14, height() - 14);

    // Создаём холст
    canvas_ = new QLabel(this);
    canvas_->resize(this->size());

    // Создаём таймер мигания
    timerBlink_ = new QTimer(this);
    timerBlink_->setInterval(250);
    connect(timerBlink_, SIGNAL(timeout()),
            this, SLOT(onTimerBlink()));
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
AbstractElement::~AbstractElement()
{

}



//-----------------------------------------------------------------------------
// Вернуть название эелемента
//-----------------------------------------------------------------------------
QString AbstractElement::name()
{
    return name_;
}



//-----------------------------------------------------------------------------
// Установить информацию
//-----------------------------------------------------------------------------
void AbstractElement::setInfo(QString screenName, int columnNumber)
{
    screen_ = screenName;
    column_ = QString::number(columnNumber);
}



//-----------------------------------------------------------------------------
// Метод активации мигания элемента
//-----------------------------------------------------------------------------
void AbstractElement::activateBlink()
{
    if (!timerBlink_->isActive())
    {
        setUntouchable_();
        timerBlink_->start();
    }
}



//-----------------------------------------------------------------------------
// Метод деактивации мигания элемента
//-----------------------------------------------------------------------------
void AbstractElement::deactivateBlink()
{
    if (timerBlink_->isActive())
    {
        timerBlink_->stop();
        blink_ = false;
        resetResponseWaiting_();
        setUntouchable_();
        drawElement_();
    }
}



//-----------------------------------------------------------------------------
// Вернуть статус активности мигания элемента
//-----------------------------------------------------------------------------
bool AbstractElement::isActive()
{
    return timerBlink_->isActive();
}



//-----------------------------------------------------------------------------
// Вернуть тип элемента (itNORMAL - itDISCONNECT)
//-----------------------------------------------------------------------------
Elements::IconType AbstractElement::type()
{
    return type_;
}



//-----------------------------------------------------------------------------
// Вернуть состояние элемента (вкл/выкл)
//-----------------------------------------------------------------------------
bool AbstractElement::state()
{
    return state_;
}



//-----------------------------------------------------------------------------
// Установить заданное состояние (вкл/выкл) [установка вручную]
//-----------------------------------------------------------------------------
void AbstractElement::setRefStateManual(bool refSt)
{
    Q_UNUSED(refSt);
}



//-----------------------------------------------------------------------------
// Установить заданное состояние (вкл/выкл) [установка системой]
//-----------------------------------------------------------------------------
void AbstractElement::setRefStateSystem(bool refSt)
{
    if (untouchableCounter_)
    {
        --untouchableCounter_;
        return;
    }

    // Если заданное и текущее состояния не совпадают
    if (refState_ != refSt || firstUpdate_)
    {
        refState_ = refSt;

        // Если заданное и текущее состояния не совпали
        // Может возникнить при изменении состояния технически (сервером)
        if (refState_ != state_)
        {
            // Активируем мигание
            this->activateBlink();
        }
        else
        {
            // Деактивируем мигание
            this->deactivateBlink();
        }

        firstUpdate_ = false;
    }
}



//-----------------------------------------------------------------------------
// Вернуть заданное состояние (вкл/выкл)
//-----------------------------------------------------------------------------
bool AbstractElement::refState()
{
    return refState_;
}



//-----------------------------------------------------------------------------
// Задать характеристики элемента
//-----------------------------------------------------------------------------
void AbstractElement::updateElement(bool rfSt, bool st, uchar tp)
{
    //if (rfSt != st)
    this->setState_(st);

    if (!manual_)
    {
        this->setRefStateSystem(rfSt);
    }
    else
    {
        manual_ = false;
    }

    // here

    if (tp < Elements::itMAXIMUM)
    {
        setType_(static_cast<Elements::IconType>(tp));
    }
    else
    {
        setType_(Elements::itDISCONNECT);
    }
}



//-----------------------------------------------------------------------------
// Задать состояние блокировки элемента
//-----------------------------------------------------------------------------
void AbstractElement::updateBlocking(bool rfBlk, bool curBlk)
{
    this->setCurBlocked_(curBlk);

    if (!manualBlock_)
    {
        this->setRefBlockedBySystem(rfBlk);
    }
    else
    {
        manualBlock_ = false;
    }
}



//-----------------------------------------------------------------------------
// Вернуть указатель на текущее состояние (!)
//-----------------------------------------------------------------------------
bool* AbstractElement::curState_ptr()
{
    // ///////////////////////////////////////////////////// //
    //                   ОПАСНЫЙ МЕТОД!!!                    //
    //      Данная функция используется для уменьшения       //
    //    количества используемых циклов проверки путем      //
    //  возможности передачи указателя заданного состояния.  //
    // ///////////////////////////////////////////////////// //
    return &state_;
}



//-----------------------------------------------------------------------------
// Вернуть указатель на заданное состояние (!)
//-----------------------------------------------------------------------------
bool *AbstractElement::refState_ptr()
{
    // ///////////////////////////////////////////////////// //
    //                   ОПАСНЫЙ МЕТОД!!!                    //
    //      Данная функция используется для уменьшения       //
    //    количества используемых циклов проверки путем      //
    //  возможности передачи указателя заданного состояния.  //
    // ///////////////////////////////////////////////////// //
    return &refState_;
}



//-----------------------------------------------------------------------------
// Вернуть указатель на текущую блокировку
//-----------------------------------------------------------------------------
bool *AbstractElement::curBlock_ptr()
{
    // ///////////////////////////////////////////////////// //
    //                   ОПАСНЫЙ МЕТОД!!!                    //
    //      Данная функция используется для уменьшения       //
    //    количества используемых циклов проверки путем      //
    //  возможности передачи указателя заданного состояния.  //
    // ///////////////////////////////////////////////////// //
    return &curBlocked_;
}



//-----------------------------------------------------------------------------
// Вурнеть указатель на заданную блокировку
//-----------------------------------------------------------------------------
bool *AbstractElement::refBlock_ptr()
{
    // ///////////////////////////////////////////////////// //
    //                   ОПАСНЫЙ МЕТОД!!!                    //
    //      Данная функция используется для уменьшения       //
    //    количества используемых циклов проверки путем      //
    //  возможности передачи указателя заданного состояния.  //
    // ///////////////////////////////////////////////////// //
    return &refBlocked_;
}



//-----------------------------------------------------------------------------
// Установить заданную блокировку вручную
//-----------------------------------------------------------------------------
void AbstractElement::setRefBlockedManually(bool blocked)
{
    Q_UNUSED(blocked);
}



//-----------------------------------------------------------------------------
// Установить заданную блокировку системой
//-----------------------------------------------------------------------------
void AbstractElement::setRefBlockedBySystem(bool rfBlk)
{
    if (untouchableCounter_)
    {
        --untouchableCounter_;
        return;
    }

    //
    if (refBlocked_ != rfBlk)
    {
        refBlocked_ = rfBlk;
        drawElement_();
    }
}



//-----------------------------------------------------------------------------
// Переключить заданную блокировку
//-----------------------------------------------------------------------------
void AbstractElement::toggleRefBlock()
{
    setRefBlockedManually(!refBlocked_);
}



//-----------------------------------------------------------------------------
// Вернуть статут текущей блокировки
//-----------------------------------------------------------------------------
bool AbstractElement::isBlocked() const
{
    return curBlocked_ || refBlocked_;
}



//-----------------------------------------------------------------------------
// Вернуть статус любой блокировки
//-----------------------------------------------------------------------------
bool AbstractElement::isAnyBlockedNew() const
{
    return curBlocked_ || refBlocked_;
}



//-----------------------------------------------------------------------------
// Вернуть не нарушена ли связь с элементом
//-----------------------------------------------------------------------------
bool AbstractElement::isConnected()
{
    return type_ != Elements::itDISCONNECT;
}



//-----------------------------------------------------------------------------
// Установить метод отрисовки
//-----------------------------------------------------------------------------
void AbstractElement::setElementDrawEngine(AbstractElementDrawEngine *engine)
{
    if (engine != NULL)
    {
        delete drawEngine_;
        drawEngine_ = engine;
    }
}



//-----------------------------------------------------------------------------
// Сброс всех состояний при разрыве связи
//-----------------------------------------------------------------------------
void AbstractElement::resetOnDisconnect()
{
    deactivateBlink();

    refState_ = false;

    state_ = false;

    type_ = Elements::itDISCONNECT;

    refBlocked_ = false;

    curBlocked_ = false;

    currentWaiting_ = 0;

    blink_ = false;

    untouchableCounter_ = 0;

    drawElement_();
}



//-----------------------------------------------------------------------------
// (слот) Обработка таймаута таймера мигания
//-----------------------------------------------------------------------------
void AbstractElement::onTimerBlink()
{
    blink_ = !blink_;
    // Отрисовка элемента с учётом мигания
    drawElement_();
    // Метод ожидания ответа от сервера
    waitForResponseFromServer_();
}



//-----------------------------------------------------------------------------
// Установить состояние элемента (вкл/выкл)
//-----------------------------------------------------------------------------
void AbstractElement::setState_(bool state)
{
    if (state_ != state) // ???
    {
        state_ = state;

        // Отрисовка элемента
        drawElement_();

        // Если мигал и заданное и текущее состояние совпадают
        if (state_ == refState() && isActive())
        {
            // Останавливаем мигание
            this->deactivateBlink();
        }
    }
}



//-----------------------------------------------------------------------------
// Установить тип элемента (itNORMAL - itDISCONNECT)
//-----------------------------------------------------------------------------
void AbstractElement::setType_(Elements::IconType type)
{
    if (type_ != type && type >= 0 && type <= COL_ON.count())
    {
        type_ = type;

        // Отрисовка элемента
        drawElement_();
    }
}



//-----------------------------------------------------------------------------
// Метод обработки ожидания ответа от сервера
//-----------------------------------------------------------------------------
void AbstractElement::waitForResponseFromServer_()
{
    currentWaiting_ += timerBlinkInterval_;
    if (currentWaiting_ > responseWaitingConstant_)
    {
        setRefStateForced_(state_);
        deactivateBlink();
    }
}



//-----------------------------------------------------------------------------
// Сбросить счетчик ожидания ответа от сервера
//-----------------------------------------------------------------------------
void AbstractElement::resetResponseWaiting_()
{
    currentWaiting_ = 0;
}



//-----------------------------------------------------------------------------
// Сделать элемент "неприкосновенным" на заданное время
//-----------------------------------------------------------------------------
void AbstractElement::setUntouchable_()
{
    untouchableCounter_ = untouchableTimeConstant_;
}



//-----------------------------------------------------------------------------
// Жестко задать текущее состояние блокировки
//-----------------------------------------------------------------------------
void AbstractElement::setCurBlocked_(bool blocked)
{
    if (curBlocked_ != blocked)
    {
        curBlocked_ = blocked;

        drawElement_();
    }
}



//-----------------------------------------------------------------------------
// Принудительно изменить значение заданного состояния
//-----------------------------------------------------------------------------
void AbstractElement::setRefStateForced_(bool refSt)
{
    refState_ = refSt;
}



//-----------------------------------------------------------------------------
// Принудительно изменить заданную блокировку
//-----------------------------------------------------------------------------
void AbstractElement::setRefBlockedForced_(bool rfBlk)
{
    refBlocked_ = rfBlk;
    setUntouchable_();
}



//-----------------------------------------------------------------------------
// Вернуть положение бокса по X
//-----------------------------------------------------------------------------
int AbstractElement::boxX()
{
    return boxX_;
}



//-----------------------------------------------------------------------------
// Вернуть положение бокса по Y
//-----------------------------------------------------------------------------
int AbstractElement::boxY()
{
    return boxY_;
}



//-----------------------------------------------------------------------------
// Вернуть ширину бокса
//-----------------------------------------------------------------------------
int AbstractElement::boxW()
{
    return boxW_;
}



//-----------------------------------------------------------------------------
// Вернуть высоту бокса
//-----------------------------------------------------------------------------
int AbstractElement::boxH()
{
    return boxH_;
}



//-----------------------------------------------------------------------------
// Установить положение бокса
//-----------------------------------------------------------------------------
void AbstractElement::setBoxPos(int x, int y)
{
    boxX_ = x;
    boxY_ = y;
}



//-----------------------------------------------------------------------------
// Усановить размер бокса
//-----------------------------------------------------------------------------
void AbstractElement::setBoxSize(int w, int h)
{
    boxW_ = w - 1;
    boxH_ = h - 1;
}

//-----------------------------------------------------------------------------
// Отрисовка треугольника
//-----------------------------------------------------------------------------
void AbstractElement::drawTriangle_(QPainter &p, bool back)
{
    // ////////////////////////////////////////////////// //
    //    Отрисовка происходит "варварским" методом.      //
    //        Треугольник составляется из линий.          //
    //         Причина использования - большая            //
    //  погрешность QPainter при рисовании треугольников  //
    // ////////////////////////////////////////////////// //
    int fooX1 = boxX_ - 3 + (back ? 2 : 0);
    int fooY1 = boxY_ - 3 + (back ? 2 : 0);
    int fooX2 = boxX_ + boxW_ + 3 + (back ? 2 : 0);
    int fooY2 = boxY_ + boxH_ + 3 + (back ? 2 : 0);
    int fooX = boxX_ - 3 + (back ? 2 : 0);
    int fooY = boxY_ - 3 + (back ? 2 : 0);
    int fooL = height() - 8;

    QColor fooCol = back ? QColor(Qt::white) : QColor(Qt::yellow);

    p.setPen(QPen(Qt::black, 1));
    p.drawLine(fooX1, fooY1, fooX2, fooY1);
    p.drawLine(boxX_ + (boxW_ - 1)/2 + (back ? 2 : 0), fooY2,
               boxX_ + (boxW_ + 1)/2 + (back ? 2 : 0), fooY2);

    p.setPen(QPen(Qt::black, 2));
    for (int i = 1; i < fooL/2; i++)
    {
        p.drawLine(i + fooX, i * 2 + fooY, fooL - i + fooX, i * 2 + fooY);
    }

    p.setPen(QPen(fooCol, 2));
    for (int i = 1; i < fooL/2; i++)
    {
        p.drawLine(i + fooX + 1, i * 2 + fooY,
                   fooL - i + fooX - 1, i * 2 + fooY);
    }
}



//-----------------------------------------------------------------------------
// Чистый виртуальный метод полной отрисовки элемента
//-----------------------------------------------------------------------------
void AbstractElement::drawElement_()
{
    // must be overridden later!
}



//-----------------------------------------------------------------------------
// Отрисовка самого значка (чекбокса) элемента
//-----------------------------------------------------------------------------
QImage AbstractElement::drawBox()
{
    QPainter p;
    QImage img(canvas_->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    p.begin(&img);

//    if (isAnyBlocked()) // Если блокирован
    if (isAnyBlockedNew()) // Если блокирован
    {
        // Рисуем треугольник
        drawTriangle_(p);
    }
    else if (!isConnected()) // Если потеряна связь
    {
        drawDisconnected(p);
    }
    else // Если связь не нарушена
    {
        drawBase(p);
        drawCross(p);
    }

    p.end();

    // Устанавливаем пиксмэп на лейбл холст
    canvas_->setPixmap(QPixmap::fromImage(img));

    // Возвращаем полученное изображение
    return img;
}



//-----------------------------------------------------------------------------
// Отрисовка элемента при отсутствии соединения
//-----------------------------------------------------------------------------
void AbstractElement::drawDisconnected(QPainter &p)
{
    // Выбираем цвета в зависимости от типа элемента
    p.setPen(QColor(Qt::red));
    p.setBrush(QColor(Qt::red));

    // Рисуем красный квадрат
    p.drawRect(5, 5, width() - 11, height() - 11);

    // Настраиваем перо и пишем знак "?"
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 15, QFont::Bold));
    p.drawText(width()/2 - 6, height()/2 + 7, "?");
}



//-----------------------------------------------------------------------------
// Отрисовка базовой части бокса
//-----------------------------------------------------------------------------
void AbstractElement::drawBase(QPainter &p)
{
    p.setPen(QColor(Qt::black));
    if (blink_)
    {
        p.setBrush(QColor(Qt::black));
    }
    else
    {
        p.setBrush(QColor(LIST[static_cast<int>(state_)][type_]));
    }

    // Рисуем квадрат чекбокса
    p.drawRect(boxX_, boxY_, boxW_, boxH_);
}



//-----------------------------------------------------------------------------
// Отрисовка крестика выбора
//-----------------------------------------------------------------------------
void AbstractElement::drawCross(QPainter &p)
{
    if (state_)
    {
        if (blink_)
        {
            p.setPen(QPen(QColor(LIST[1][type_]), 2));
        }
        else
        {
            p.setPen(QPen(Qt::black, 2));
        }

        // Рисуем крестик
        p.drawLine(boxX_ + 4,  boxY_ + 4,
                   boxX_ + boxW_ - 3, boxY_ + boxH_ - 3);

        p.drawLine(boxX_ + boxW_ - 3, boxY_ + 4,
                   boxX_ + 4, boxY_ + boxH_ - 3);
    }
}



//-----------------------------------------------------------------------------
// Событие скрытия элемента
//-----------------------------------------------------------------------------
void AbstractElement::hideEvent(QHideEvent *e)
{
    Q_UNUSED(e);
    setElementDrawEngine(new ElementNoDrawEngine(this));
}

