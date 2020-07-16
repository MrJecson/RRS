//-----------------------------------------------------------------------------
//
//      Класс правого блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 06/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс правого блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 06/03/2017
 */

#ifndef RIGHTBLOCK_H
#define RIGHTBLOCK_H


#include "abstract-block.h"
#include "image-button.h"

/*!
 * \class RightBlock
 * \brief Класс правого блока кнопок
 */
class RightBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backrg - цвет фона
     * \param geo - геометрия
     */
    RightBlock(QColor backrg, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~RightBlock();

private:
    /// Размер кнопок блока
    const QSize CHILD_SIZE_ = QSize(60, 60);

    /// Список с кнопками для данного блока
    QList<ImageButton*> listButtons_;

    // ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;


    /// Список имен из ресурсов для кнопок правой панели
    const QStringList BUTTON_NAMES_ = QStringList() << "left"
                                                    << "right"
                                                    << "up"
                                                    << "down"
                                                    << "input";

    /// Префикс нажатых картинок
    const QString PRESSED_PREFIX_ = ":/hard-buttons-pressed/images/hard-buttons/pressed/";
    /// Префикс отпущенных картинок
    const QString RELEASED_PREFIX_=":/hard-buttons-released/images/hard-buttons/released/";

    /// Список имен из ресурсов для кнопок правой панели
    const QStringList HARD_BUTTONS_ = {"left.png",
                                       "right.png",
                                       "up.png",
                                       "down.png",
                                       "input.png"};

};

#endif // RIGHTBLOCK_H
