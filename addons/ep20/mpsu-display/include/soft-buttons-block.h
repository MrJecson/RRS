//-----------------------------------------------------------------------------
//
//      Класс ряда программируемых клавиш экрана ласточки
//      (c) РГУПС, ВЖД 09/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс ряда программируемых клавиш экрана ласточки
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 09/03/2017
 */

#ifndef SOFTBUTTONSBLOCK_H
#define SOFTBUTTONSBLOCK_H


#include "abstract-block.h"
#include "image-widget.h"

/*!
 * \class SimplePlot
 * \brief Класс реализует блок программируемых клавиш
 */
class SoftButtonsBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backgr - цвет фона
     * \param geo - геометрия окна
     */
    SoftButtonsBlock(QColor backgr, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~SoftButtonsBlock();


public slots:
    ///
    //void setButtonsNames(const QStringList &_list);
    void setButtonsNames(const QStringList &_list, int idxCurScreen = -1,
                         QString head = "", int numCell = -1, int countCell = -1);


private:
    // Содержит информацию о текущем состоянии ячеек
    int statusArray_[9]; ///< Массив текущего состояния ячеек

    /// Размер кнопок блока
    const QSize CHILD_SIZE_ = QSize(81, 40);

    /// Префикс для загрузки картинок
    const QString BUTTONS_PREFIX_ = ":/soft/img/softpanelbuttons/";

    /// Список с кнопками для данного блока
    QList<ImageWidget*> listButtons_;
    //QList<ImageWidget*> listButtonsTop_;
    QLabel* labHead_;


    // ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;


// СПИСКИ НАЗВАНИЙ КАРТИНОК ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ **************************
    /// Спиков картинок первой ячейки
    const QStringList BT1  = QStringList() << "BT1/digit1.png"          //0
                                           << "BT1/doors.png"           //1
                                           << "BT1/on.png"              //2
                                           << "BT1/train1.png"          //3
                                           << "BT1/diagnostic.png";     //4

    /// Спиков картинок второй ячейки
    const QStringList BT2  = QStringList() << "BT2/context.png"         //0
                                           << "BT2/digit2.png"          //1
                                           << "BT2/dpd.png"             //2
                                           << "BT2/off.png"             //3
                                           << "BT2/train2.png"          //4
                                           << "BT2/trainmode.png"       //5
                                           << "BT2/showlog.png";        //6

    /// Спиков картинок третьей ячейки
    const QStringList BT3  = QStringList() << "BT3/block.png"           //0
                                           << "BT3/conditionline.png"   //1
                                           << "BT3/digit3.png"          //2
                                           << "BT3/fullcheck.png"       //3
                                           << "BT3/timeready.png"       //4
                                           << "BT3/upper.png";          //5

    /// Спиков картинок четвёртой ячейки
    const QStringList BT4  = QStringList() << "BT4/bushcontrol.png"     //0
                                           << "BT4/controlelements.png" //1
                                           << "BT4/digit4.png"          //2
                                           << "BT4/lower.png"           //3
                                           << "BT4/shortcheck.png"      //4
                                           << "BT4/unblock.png";        //5

    /// Спиков картинок пятой ячейки
    const QStringList BT5  = QStringList() << "BT5/digit5.png"          //0
                                           << "BT5/leftscreen.png"      //1
                                           << "BT5/powersys.png";       //2

    /// Спиков картинок шестой ячейки
    const QStringList BT6  = QStringList() << "BT6/climate.png"         //0
                                           << "BT6/digit6.png"          //1
                                           << "BT6/rightscreen.png"     //2
                                           << "BT6/to.png";             //3

    /// Спиков картинок седьмой ячейки
    const QStringList BT7  = QStringList() << "BT7/brakes.png"          //0
                                           << "BT7/controlelements.png" //1
                                           << "BT7/digit7.png";         //2

    /// Спиков картинок восьмой ячейки
    const QStringList BT8  = QStringList() << "BT8/autodrive.png"       //0
                                           << "BT8/digit8.png"          //1
                                           << "BT8/elemindi.png";       //2

    /// Спиков картинок девятой ячейки
    const QStringList BT9  = QStringList() << "BT9/back.png"            //0
                                           << "BT9/digit9.png"          //1
                                           << "BT9/trainconfig.png";    //2

    /// Спиков картинок десятой ячейки
    const QStringList BT10 = QStringList() << "BT10/digit0.png"         //0
                                           << "BT10/mainscreen.png";    //1

    /// Спиков всех списков
    const QList<QStringList> allCells_ = QList<QStringList>() << BT1
                                                              << BT2
                                                              << BT3
                                                              << BT4
                                                              << BT5
                                                              << BT6
                                                              << BT7
                                                              << BT8
                                                              << BT9
                                                              << BT10;

};

#endif // SOFTBUTTONSBLOCK_H
