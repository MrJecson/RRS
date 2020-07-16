//-----------------------------------------------------------------------------
//
//      Класс нижнего блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс нижнего блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */

#ifndef BOTTOMBLOCK_H
#define BOTTOMBLOCK_H


#include "abstract-block.h"

class ImageButton;

/*!
 * \class BottomBlock class
 * \brief Класс нижнего блока кнопок
 */
class BottomBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backgr - цвет фона
     * \param geo - геометрия
     */
    BottomBlock(QColor backgr, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~BottomBlock();


private:
    /// Размер кнопок на блоке
    const QSize CHILD_SIZE_ = QSize(60, 60);

    /// Список с кнопками для данного блока
    QList<ImageButton*> listButtons_;

    // ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
    /// Создаём все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;


// СПИСОК ИМЕН КНОПОК *********************************************************
    /// Список имен кнопок
    const QStringList BUTTON_NAMES_{"digit1", "digit2", "digit3", "digit4",
                                    "digit5", "digit6", "digit7", "digit8",
                                    "digit9", "digit0"};


// ПРЕФИКС ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ *******************************************
    /// Префикс нажатых клавиш
    const QString PRESSED_PREFIX_ = ":/hard-buttons-pressed/images/hard-buttons/pressed/";
    /// Префикс отпущенных клавиш
    const QString RELEASED_PREFIX_=":/hard-buttons-released/images/hard-buttons/released/";


// СПИСОК ИМЕН КНОПОК В ФАЙЛЕ РЕСУРСОВ ****************************************
    /// Список имен файлов
    const QStringList HARD_BUTTONS_{"digit1.png", "digit2.png", "digit3.png",
                                    "digit4.png", "digit5.png", "digit6.png",
                                    "digit7.png", "digit8.png", "digit9.png",
                                    "digit0.png"};

};

#endif // BOTTOMBLOCK_H
