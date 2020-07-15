#include "abstract-element-draw-engine.h"
#include "abstract-element.h"

#include <QPainter>


const QStringList COL_ON = {"#ffffff", "#00ff00", "#0096ff",
                            "#ff9600", "#ffff00", "#ff0000"};

const QStringList COL_OFF = {"#ffffff", "#ffffff", "#0096ff",
                             "#ff9600", "#ffff00", "#ff0000"};

const QList<QStringList> LIST = QList<QStringList>() << COL_OFF << COL_ON;


AbstractElementDrawEngine::AbstractElementDrawEngine(AbstractElement *elem)
    : element_(elem)
{

}

AbstractElementDrawEngine::~AbstractElementDrawEngine()
{
    // Обнуляем указатель на подконтрольный элемент
    element_ = Q_NULLPTR;
}


//int AbstractElementDrawEngine::w()
//{
//    return element_->width();
//}


//int AbstractElementDrawEngine::h()
//{
//    return element_->height();
//}


//int AbstractElementDrawEngine::x()
//{
//    return element_->x();
//}


//int AbstractElementDrawEngine::y()
//{
//    return element_->y();
//}


void AbstractElementDrawEngine::drawDisconnected(QPainter &p)
{
    // Выбираем цвета в зависимости от типа элемента
    p.setPen(QColor(Qt::red));
    p.setBrush(QColor(Qt::red));

    // Рисуем красный квадрат
    p.drawRect(5, 5, element_->width() - 11, element_->height() - 11);

    // Настраиваем перо и пишем знак "?"
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 15, QFont::Bold));
    p.drawText(element_->width()/2 - 6, element_->height()/2 + 7, "?");
}


void AbstractElementDrawEngine::drawBase(QPainter &p)
{
    p.setPen(QColor(Qt::black));
    if (element_->blink_)
    {
        p.setBrush(QColor(Qt::black));
    }
    else
    {
        p.setBrush(
              QColor(
                LIST[element_->state_][element_->type_]
                    )
                  );
    }

    // Рисуем квадрат чекбокса
    p.drawRect(element_->boxX_, element_->boxY_,
               element_->boxW_, element_->boxH_);
}


void AbstractElementDrawEngine::drawCross(QPainter &p)
{
    // TODO - реализовать метод
    Q_UNUSED(p);
}


void AbstractElementDrawEngine::drawTriangle(QPainter &p, bool back)
{
    // TODO - реализовать метод
    Q_UNUSED(p);
    Q_UNUSED(back);
}
