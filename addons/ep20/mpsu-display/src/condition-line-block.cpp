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

#include "condition-line-block.h"

#include "image-widget.h"

#include "display-shared-structures.h"
#include "display-shared-data.h"
#include "directives.h"

#include <QPainter>
#include <QSvgRenderer>


constexpr int CONDITION_CELLS = 14;


void loadAllSvgImages(const QStringList &_names, QList<QImage> &_images);


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
ConditionLineBlock::ConditionLineBlock(QColor backrg, QRect geo,
                                       QWidget *parent)
    : AbstractBlock(geo, parent)
    , statusArray_{}
{
    this->setPalette({backrg});

    loadAllSvgImages_();

    // Создаем все дочерние виджеты
    createAllChildren_();

    loadSystemsFromCfg_(); // FIXME - загр. из конфигурационного файла ???
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
ConditionLineBlock::~ConditionLineBlock()
{

}



//-----------------------------------------------------------------------------
// (слот) Метод установки изображений в ячейки по вектору
//-----------------------------------------------------------------------------
void ConditionLineBlock::updateLine(condition_t* data)
{
    // Настраиваем опции отрисовки текста
    ImageWidget::text_opts opts;
    opts.alignment = Qt::AlignCenter;
    opts.weight = QFont::Black;

    QString speedVal = data->auditActive?
                            QString::number(data->refSpeed) :
                            "---";

    listImages_.first()->setText("Vз: " + speedVal, opts);

    for (int i = 0; i < ConditionLine::IMAGED_CELLS; ++i)
    {
        if (data->cells[i] == statusArray_[i])
            continue;

        statusArray_[i] = data->cells[i];
        // Индексы задаются на сервере перечислителем ConditionLine::Cells
        // поэтому необходимо привести их к нормальному виду (с нуля)
        int pictureIndex = data->cells[i] - 1;

        // ImageWidget'ы с картинками идут с 1 по 13, поэтому необходимо
        // начинать не с 0-го а с 1-го. (Виджеты 0, 14 выводят текст)
        int imgIdx = i + 1;

        if ( inRange(pictureIndex, ConditionLine::allCells) )
        {
            listImages_[imgIdx]->setImage(listPictures_[pictureIndex]);
        }
        else
        {
            listImages_[imgIdx]->setBlank();
        }
    }

    // FIXME - необходимо будет сделать мигание

    opts.colorBackground = Qt::yellow;
    opts.colorText = Qt::black;
    opts.weight = QFont::Normal;

    if ( (data->brokenSysIndex > 0) && inRange(data->brokenSysIndex, listSystems_) )
        listImages_.last()->setText("Неисправность в " +
                                    listSystems_[data->brokenSysIndex], opts);
    else
        listImages_.last()->setBlank();
}



//-----------------------------------------------------------------------------
// Метод создания дочерних виджетов
//-----------------------------------------------------------------------------
void ConditionLineBlock::createAllChildren_()
{
    // Создаем промежуточную переменную для размера виджета
    QSize foo;

    // Для всех картинок
    for (int i = 0; i < CONDITION_CELLS; ++i)
    {
        // Заносим размер
        foo = CHILD_SIZE_;

        if (i == 0)
        {
            foo = QSize(foo.width() * 2 - 1, foo.height());
        }
        else if (i == 13)
        {
            foo = QSize(foo.width() * 6 - 5, foo.height());
        }

        // Создаем список виджетов картинок
        listImages_.append(new ImageWidget("-", foo, this));
        listImages_.last()->setBlank();
    }

    // Упорядочиваем картинки (метод абстр класса)
    autoChildrenPos_(-1, {28, 2});
}



//-----------------------------------------------------------------------------
// Загрузка списка систем из файла конфигурации
//-----------------------------------------------------------------------------
void ConditionLineBlock::loadSystemsFromCfg_()
{
    // FIXME - сделать загрузку из конфигурационного файла, когда понадобится
    listSystems_ = QStringList{"", "БУТ 14", "Токопр. 1"};
}



//-----------------------------------------------------------------------------
// Буфферизация картинок в растровом виде
//-----------------------------------------------------------------------------
void ConditionLineBlock::loadAllSvgImages_()
{
    QSvgRenderer r;
    QPainter p;
    QString prefix(":condition-line/images/condition-line/");

    for (int i = 0, n = ConditionLine::allCells.count(); i < n; ++i)
    {
        // Добавляем буфферную картинку
        listPictures_.append(QImage(CHILD_SIZE_, DEF_FORMAT));
        // Ссылаемся на последнюю добавленную картинку
        QImage &img = listPictures_.last();
        img.fill(Qt::transparent);

        p.begin(&img);

        p.setPen({200, 200, 200});
        p.drawRect(0, 0, CHILD_SIZE_.width()-1, CHILD_SIZE_.height()-1);

        // Если есть SVG файл с таким именем и он корректный
        if (r.load(prefix + ConditionLine::allCells[i]))
        {
            r.render(&p, QRectF{1, 1,
                                qreal_cast(CHILD_SIZE_.width() - 2),
                                qreal_cast(CHILD_SIZE_.height() - 2)});
        }
        else // Если произошла ошибка загрузки
        {
            // Рисуем значок ошибки
            p.setPen(Qt::red);
            p.setBrush(Qt::black);
            p.drawRect(0, 0, CHILD_SIZE_.width()-1, CHILD_SIZE_.height()-1);
            p.drawLine(1, 1, CHILD_SIZE_.width()-2, CHILD_SIZE_.height()-2);
        }

        p.end();
    }
}
