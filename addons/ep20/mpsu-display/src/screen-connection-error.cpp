//-----------------------------------------------------------------------------
//
//      Экран сбоя связи
//      (c) РГУПС, ВЖД 11/07/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Экран сбоя связи
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/07/2017
 */

#include "screen-connection-error.h"

#include "middle-block.h"

#include "a-consts.h"

#include <QLabel>
#include <QPainter>
#include <QImage>


const QSize ERROR_RECT = QSize(500, 350);


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
ScreenConnectionError::ScreenConnectionError(MiddleBlock *parent)
    : enabled_(true)
    , visible_(true)
{
    // Создаём виджет "экрана"
    labelError_ = new QLabel(parent);
    labelError_->resize(parent->size());

    // Рисуем прямоугольник с надписью
    //drawErrorScreen_();   // zБогос - раскоментить!!
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
ScreenConnectionError::~ScreenConnectionError()
{
    // Удаляем виджет "экрана"
    // delete labelError_;
}



//-----------------------------------------------------------------------------
// Показать "экран"
//-----------------------------------------------------------------------------
void ScreenConnectionError::enable()
{
    enabled_ = true;
    // Если дисплей включен
    if (visible_)
    {
        labelError_->setVisible(true);
    }
}



//-----------------------------------------------------------------------------
// Скрыть "экран"
//-----------------------------------------------------------------------------
void ScreenConnectionError::disable()
{
    enabled_ = false;
    labelError_->setVisible(false);
}



//-----------------------------------------------------------------------------
// Сделать видимым/невидимым (при вкл/выкл дисплее)
//-----------------------------------------------------------------------------
void ScreenConnectionError::setVisible(bool visible)
{
    if (visible)
    {
        // Показать, если включен
        labelError_->setVisible(enabled_);
    }
    else
    {
        labelError_->setVisible(visible);
    }
    this->visible_ = visible;
}


//-----------------------------------------------------------------------------
// Вернуть статус включённости
//-----------------------------------------------------------------------------
bool ScreenConnectionError::isEnabled() const
{
    return enabled_;
}



//-----------------------------------------------------------------------------
//Метод отрисовки "экрана"
//-----------------------------------------------------------------------------
void ScreenConnectionError::drawErrorScreen_()
{
    QImage img(labelError_->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::black);

    int fooX = (labelError_->width() - ERROR_RECT.width()) / 2;
    int fooY = (labelError_->height() - ERROR_RECT.height()) / 2;

    QPainter p(&img);

    // Рисуем прямоугольник
    p.setBrush(Qt::red);
    p.drawRect(fooX, fooY, ERROR_RECT.width() - 1, ERROR_RECT.height() - 1);

    p.setBrush(Qt::black);
    p.drawRect(fooX + 4, fooY + 4,
               ERROR_RECT.width() - 9, ERROR_RECT.height() - 9);

    p.setBrush(Qt::red);
    p.drawRect(fooX + 8, fooY + 8,
               ERROR_RECT.width() - 17, ERROR_RECT.height() - 17);

    // Выводим надпись
    p.setFont(QFont("Arial", 22, 86));
    p.drawText(fooX + 123, fooY + 188, QString("Нарушение связи"));

    // Рисуем серую рамку
    p.setPen(Qt::gray);
    p.setBrush(Qt::transparent);
    p.drawRect(0, 0, labelError_->width() - 1, labelError_->height() - 1);

    p.end();

    // Устанавливаем пиксмэп
    labelError_->setPixmap(QPixmap::fromImage(img));
}
