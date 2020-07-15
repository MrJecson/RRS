//-----------------------------------------------------------------------------
//
//      Класс верхнего блока жестко запрограммированных клавиш
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс верхнего блока жестко запрограммированных клавиш
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */

#ifndef TOPBLOCK_H
#define TOPBLOCK_H


#include "abstract-block.h"
#include "image-button.h"

/*!
 * \class TopBlock
 * \brief Верхний блок кнопок
 */
class TopBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backgr - цвет фона
     * \param geo - геометрия
     */
    TopBlock(QColor backgr, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~TopBlock();


private:    
    /// Размер кнопок блока
    const QSize CHILD_SIZE_ = QSize(60, 60);

    /// Список с кнопками для данного блока
    QList<ImageButton*> listButtons_;

    // ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;

    /// Список имен кнопок верхней панели
    const QStringList BUTTON_NAMES_ = QStringList() << "Otm"
                                                    << "F1"
                                                    << "F2"
                                                    << "F3"
                                                    << "F4"
                                                    << "F5"
                                                    << "minus"
                                                    << "plus"
                                                    << "star"
                                                    << "correction";

    /// Префикс нажатых кнопок
    const QString PRESSED_PREFIX_ = ":/hard-buttons-pressed/images/hard-buttons/pressed/";
    /// Префикс отпущенных кнопок
    const QString RELEASED_PREFIX_=":/hard-buttons-released/images/hard-buttons/released/";

    /// Список имен из ресурсов для кнопок верхней панели
    const QStringList HARD_BUTTONS_ = {"Otm.png",
                                       "F1.png",
                                       "F2.png",
                                       "F3.png",
                                       "F4.png",
                                       "F5.png",
                                       "minus.png",
                                       "plus.png",
                                       "star.png",
                                       "correction.png"};

};

#endif // TOPBLOCK_H
