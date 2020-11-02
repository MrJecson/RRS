//-----------------------------------------------------------------------------
//
//      Класс статичной картинки
//      (c) РГУПС, ВЖД 07/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс статичной картинки
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 07/03/2017
 */

#include "image-widget.h"

#include <QStaticText>
#include <QPainter>
#include <QFile>


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
ImageWidget::ImageWidget(QString imgName, QSize imgSize, QWidget *parent)
    : QLabel(parent)      // Передаём родителя в базовый класс
//    , imageName_(imgName) // Устанавливаем имя картинки для ресурсов
    , addTxtPt_{0, 0}
    , addText_("")

{
    this->resize(imgSize);

    // Устанавливаем картинку с учетом ПРЕФИКСА и ИМЕНИ картики
//    this->setImage(imageName_);
    this->setBlank();
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
ImageWidget::~ImageWidget()
{

}



//-----------------------------------------------------------------------------
// Установить картинку QImage
//-----------------------------------------------------------------------------
void ImageWidget::setImage(QImage img)
{
    this->setPixmap(QPixmap::fromImage(img));
}



//-----------------------------------------------------------------------------
// Отрисовать пустой
//-----------------------------------------------------------------------------
void ImageWidget::setBlank()
{
    QImage img(this->size(), QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    p.setPen({200, 200, 200});
    p.setBrush(QColor(5, 20, 50));
    p.drawRect(0, 0, this->width() - 1, this->height());
    p.end();
    this->setPixmap(QPixmap::fromImage(img));
}



//-----------------------------------------------------------------------------
// Установить положение доп. надписи
//-----------------------------------------------------------------------------
void ImageWidget::setAdditionalTextPos(QPoint pt)
{
    addTxtPt_ = pt;
}



//-----------------------------------------------------------------------------
// Установить дополнительную надпись
//-----------------------------------------------------------------------------
void ImageWidget::setAdditionalText(QString txt)
{
    addText_ = txt;
}




void ImageWidget::setText(const QString &_str, text_opts _opts)
{
    QImage img(this->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(_opts.colorBackground);
    QPainter p(&img);
    p.setPen(_opts.colorText);
    p.setFont(QFont("Sans", 8, _opts.weight));

    p.drawText(_opts.paddingLeft,
               _opts.paddingTop,
               this->width() - 1,
               this->height() - 1,
               _opts.alignment,
               _str);

    p.setPen(QPen(QColor(Qt::black), 2));
    p.drawRect(0, 0, this->width() - 1, this->height());

    p.end();

    this->setPixmap(QPixmap::fromImage(img));
}



//-----------------------------------------------------------------------------
// Метод создания картинки с ошибкой
//-----------------------------------------------------------------------------
void ImageWidget::errorImage_(QPixmap &pix)
{
    QImage img(this->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(QColor(5, 20, 50));
    pix = QPixmap::fromImage(img);
    // Передаем пиксмэп в "рисователь"
    QPainter p(&pix);
    // Берем красное перо 2px
    p.setPen(QPen(QColor(255, 0, 0), 1));
    // Рисуем рамку и линию
    p.drawRect(0, 0, this->width() - 1, this->height() - 1);
    p.drawLine(0, 0, this->width() - 1, this->height() - 1);
    // Устанавливаем перо на "рисователь"
    p.setPen(QPen(QColor(255, 255, 255), 12));
    // Создаём статический текст
    QStaticText errText("no image");
    // Рисуем текст на картинке
    p.drawStaticText((this->width() - 42) / 2,
                     (this->height() - 12) / 2,
                     errText);
    p.end();
}
