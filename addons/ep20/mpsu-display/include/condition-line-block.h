//-----------------------------------------------------------------------------
//
//      Класс информационной строки
//      (c) РГУПС, ВЖД 29/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс информационной строки
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 29/03/2017
 */

#ifndef CONDITIONLINEBLOCK_H
#define CONDITIONLINEBLOCK_H


#include "abstract-block.h"
#include "display-shared-structures.h"

class ImageWidget;


/*!
 * \class ConditionLineBlock
 * \brief Класс строки над программируемыми клавишами
 */
class ConditionLineBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backrg - цвет фона
     * \param geo - геометрия
     */
    ConditionLineBlock(QColor backrg, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~ConditionLineBlock();

public slots:
    /// Метод установки изображений в ячейки по вектору
    void updateLine(condition_t* data);


private:
    // Содержит информацию о текущем состоянии ячеек
//    qint8 statusArray_[IMAGED_CELLS]; ///< Массив текущего состояния ячеек
    ConditionLine::CellsIndexes statusArray_; ///< Массив текущего состояния ячеек

    // Размер дочерних элементов
    const QSize CHILD_SIZE_ = QSize(38, 38); ///< Размер дочерних элементов

    /// Префикс для загрузки из ресурсов
    const QString IMAGES_PREFIX_ = ":/condition/img/conditionimages/";

    // Список виджетов картинок
    QList<ImageWidget*> listImages_;

    // Список подгруженных и от рендеренных картинок
    QList<QImage> listPictures_;

    // Список названий систем для послденей ячейки
    QStringList listSystems_;

    // Переопределение чистого виртуального метода абстр. класса
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;

    /// Загрузка списка систем из файла конфигурации
    void loadSystemsFromCfg_();

    /// Буфферизация картинок в растровом виде
    void loadAllSvgImages_();

};

#endif // CONDITIONLINEBLOCK_H
