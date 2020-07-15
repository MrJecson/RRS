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

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H


#include <QLabel>

class QPixmap;

/*!
 * \class ImageWidget
 * \brief Класс реализующий статичную картинку с возможностью смены
 */
class ImageWidget : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param imgName - имя картинки
     * \param imgSize -  размер картинки
     */
    ImageWidget(QString imgName, QSize imgSize,
                QWidget* parent = Q_NULLPTR);
    /// Дестркутор
    ~ImageWidget();

    /// Установить картинку QImage
    void setImage(QImage img);

    /// Отрисовать пустой
    void setBlank();

    /// Установить положение доп. надписи
    void setAdditionalTextPos(QPoint pt);

    /// Установить дополнительную надпись
    void setAdditionalText(QString txt);

    /*!
     * \struct text_opts
     * \brief структура опций отрисовки текста
     */
    struct text_opts
    {
        int paddingLeft{0};
        int paddingTop{0};
        Qt::Alignment alignment{Qt::AlignCenter};
        int weight{-1};
        QColor colorBackground{QColor(5, 20, 50)};
        QColor colorText{Qt::white};
    };

    ///
    void setText(const QString &_str, text_opts _opts);


private:
    // Положение доп надписи
    QPoint addTxtPt_; ///<  Положение доп надписи

    // Доп надпись
    QString addText_; ///< Доп надпись

    /// Метод создания картинки с ошибкой
    void errorImage_(QPixmap &pix);

};

#endif // IMAGEWIDGET_H
