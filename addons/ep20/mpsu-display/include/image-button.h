//-----------------------------------------------------------------------------
//
//      Класс картинки-кнопки с обработкой нажатия
//      (c) РГУПС, ВЖД 02/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс картинки-кнопки с обработкой нажатия
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 02/03/2017
 */

#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H


#include <QLabel>

#include "a-consts.h"

/*!
 * \class ImageButton
 * \brief Класс реализующий имитацию жестко запрограммированой кнопки
 */
class ImageButton : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Констркутор
     * \param butName - имя кнопки
     * \param pressed - картинка нажатой кнопки
     * \param released - картинка отпущенной кнопки
     * \param btSize - размер кнопки
     */
    ImageButton(QString butName, QWidget* parent = Q_NULLPTR);
    /// Дестуктор
    ~ImageButton();

    /// Установить имена картинок
    void setImagesNames(QString pressed, QString released);

    /// Установить идентификатор
    void setId(Local::ButtonId id);

    /// Вернуть имя кнопки
    QString imageName();


signals:
    /// Сигнал нажатия кнопки
    void sendPressed(Local::ButtonId id);

    /// Сигнал отпускания кнопки
    void sendReleased(Local::ButtonId id);


public slots:
    /// Обработка нажатия кнопок мыши
    void mousePressEvent(QMouseEvent* e);

    /// Обработка отжатия кнопок мыши
    void mouseReleaseEvent(QMouseEvent* e);


private:

    Local::ButtonId id_; ///< Уникальный идентификатор кнопки

    QString imageName_; ///< Имя картинки для идентификации

    QString pressed_; ///< Путь нажатой картинки

    QString released_; ///< Путь отжатой картинки

    /// Установтьб картинку
    void setImage_(QString imgName);

    /// Метод создания картинки с ошибкой
    void errorImage_(QPixmap &pix);

};
#endif // IMAGEBUTTON_H
