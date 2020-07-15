//-----------------------------------------------------------------------------
//
//      Класс простой вкладки
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс простой вкладки
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#include "simple-tab.h"
#include <QWidget>
#include <QLabel>

#include "element-indicator.h"

#include "display-shared-structures.h"
//#include "structures-display.h"


//-----------------------------------------------------------------------------
// Конструктор
//-----------------------------------------------------------------------------
SimpleTab::SimpleTab(QString tabName, QWidget *container)
    : container_(container)
    , tabName_(tabName)
    , isVisible_(false)
    , prevTab_(Q_NULLPTR)
    , nextTab_(Q_NULLPTR)
{

}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
SimpleTab::~SimpleTab()
{

}



//-----------------------------------------------------------------------------
// Добавить элемент нужного типа
//-----------------------------------------------------------------------------
SimpleTab *SimpleTab::addElement(QString name, SimpleTab::FieldType type)
{
    //
    QLabel* lab = new QLabel(name, container_);
    lab->setVisible(false);
    listLabels_.append(lab);

    //
    auto makeField = [&]()
    {
        QLabel* field = new QLabel("-00000", container_);
        field->setStyleSheet("background: white;"
                             "color: black;");
        field->setAlignment(Qt::AlignRight);
        field->adjustSize();
        field->setVisible(false);
        listAllElements_.append(field);
        return field;
    };

    //
    switch (type) {
    case ftBOX:
    {
        //
        ElementIndicator* el = new ElementIndicator(name, false,
                                                    Elements::itNONE,
                                                    container_);
        el->setVisible(false);
        listBoxes_.append(el);
        listAllElements_.append(el);
        break;
    }

    case ftFIELD_UINT:
    {
        //
        listFieldsUint_.append(makeField());
        break;
    }

    case ftFIELD_INT:
    {
        //
        listFieldsInt_.append(makeField());
        break;
    }

    default:
        break;
    }

    arrangeAll_();

    return this;
}



//-----------------------------------------------------------------------------
// Добавить список элементов
//-----------------------------------------------------------------------------
void SimpleTab::addElementsList(QList<QPair<QString, SimpleTab::FieldType> > list)
{
    for (auto pair : list)
    {
        addElement(pair.first, pair.second);
    }
}



//-----------------------------------------------------------------------------
// Добавить нижнюю строку
//-----------------------------------------------------------------------------
void SimpleTab::addFooter(QString str)
{
    QLabel* label = new QLabel(str, container_);
    label->setStyleSheet("font-family: \'Arial\';"
                         "font-size: 16px;"
                         "color: white;");
    label->adjustSize();

    int x = (container_->width() - label->width())/2;
    int y = container_->height() - label->height() - 20;
    label->move(x, y);
    label->setVisible(false);

    listAllElements_.append(std::move(label));
}



//-----------------------------------------------------------------------------
// Сделать вкладку видимой
//-----------------------------------------------------------------------------
void SimpleTab::setTabVisible(bool visible)
{
    isVisible_ = visible;
    for (QLabel* lab : listLabels_)
    {
        lab->setVisible(visible);
    }

    for (QLabel* lab : listAllElements_)
    {
        lab->setVisible(visible);
    }
}



//-----------------------------------------------------------------------------
// Перейти на предыдущую вкладку
//-----------------------------------------------------------------------------
SimpleTab* SimpleTab::getPrevTab()
{
    return prevTab_ ? prevTab_ : this;
}



//-----------------------------------------------------------------------------
// Перейти на следующую вкладку
//-----------------------------------------------------------------------------
SimpleTab* SimpleTab::getNextTab()
{
    return nextTab_ ? nextTab_ : this;
}


//-----------------------------------------------------------------------------
// Установить предыдущую вкладку
//-----------------------------------------------------------------------------
void SimpleTab::setPrevTab(SimpleTab *prev)
{
    prevTab_ = prev;
}


//-----------------------------------------------------------------------------
// Устанвоить следующую вкладку
//-----------------------------------------------------------------------------
void SimpleTab::setNextTab(SimpleTab *next)
{
    nextTab_ = next;
}



//-----------------------------------------------------------------------------
// Вернуть имя вкладки
//-----------------------------------------------------------------------------
QString SimpleTab::getTabName()
{
    return tabName_;
}


//-----------------------------------------------------------------------------
// Обновить данные вкладки
//-----------------------------------------------------------------------------
//void SimpleTab::updateTab(panel_diagnostic_t *data)
//{
//    for (int i = 0, n = listBoxes_.count(); i < n; ++i)
//    {
//        listBoxes_[i]->updateElement(data->flags[i],
//                                     data->flags[i],
//                                     Elements::itNORMAL);
//    }

//    for (int i = 0, n = listFieldsUint_.count(); i < n; ++i)
//    {
//        listFieldsUint_[i]->setText(QString::number(data->uintFields[i]));
//    }

//    for (int i = 0, n = listFieldsInt_.count(); i < n; ++i)
//    {
//        listFieldsInt_[i]->setText(QString::number(data->intFields[i]));
//    }
//}



//template<typename T>
//void SimpleTab::updateTab(screen_data_t *data)
//{
//    T* tmp = static_cast<T*>(data);
//    for (int i = 0, n = listBoxes_.count(); i < n; ++i)
//    {
//        listBoxes_[i]->updateElement(tmp->flags[i],
//                                     tmp->flags[i],
//                                     Elements::itNORMAL);
//    }

//    for (int i = 0, n = listFieldsUint_.count(); i < n; ++i)
//    {
//        listFieldsUint_[i]->setText(QString::number(tmp->uintFields[i]));
//    }

//    for (int i = 0, n = listFieldsInt_.count(); i < n; ++i)
//    {
//        listFieldsInt_[i]->setText(QString::number(tmp->intFields[i]));
//    }
//}

//template<typename T>
//void SimpleTab::updateT(T data)
//{
////    T* tmp = static_cast<T*>(data);
//    for (int i = 0, n = listBoxes_.count(); i < n; ++i)
//    {
//        listBoxes_[i]->updateElement(data->flags[i],
//                                     data->flags[i],
//                                     Elements::itNORMAL);
//    }

//    for (int i = 0, n = listFieldsUint_.count(); i < n; ++i)
//    {
//        listFieldsUint_[i]->setText(QString::number(data->uintFields[i]));
//    }

//    for (int i = 0, n = listFieldsInt_.count(); i < n; ++i)
//    {
//        listFieldsInt_[i]->setText(QString::number(data->intFields[i]));
//    }
//}



//-----------------------------------------------------------------------------
// Упорядочить все подконтрольные виджеты
//-----------------------------------------------------------------------------
void SimpleTab::arrangeAll_()
{
    if ( (listLabels_.count() != listAllElements_.count()) ||
         listLabels_.isEmpty() )
    {
        return;
    }

    int h = 0;

    for (QLabel* label : listAllElements_)
    {
        if (label->height() > h)
            h = label->height();
    }

    int ruler = 0;
    int semiW = container_->width()/2;
    int topPadding = 50;
    int leftPadding = 10;
    int rightPadding = 50;
    int padding = 25;
    int sumPadding = topPadding;

    auto rX = [&](QLabel* lab)
    {
        int x = ruler + semiW - lab->width() - rightPadding;
        x -= lab->width() == lab->height() ? 0 : 8;
        return x;
    };

    auto eY = [&](QLabel* lab, QLabel* el)
    {
        return lab->y() - (el->height() - lab->height())/2 - 5;
    };


    for (int i = 0, n = listLabels_.count(); i < n; ++i)
    {
        if ( (sumPadding + h > container_->height()) && ruler == 0 )
        {
            ruler = semiW;
            sumPadding = topPadding;
        }

        QLabel* lab = listLabels_[i];
        lab->move(ruler + leftPadding, sumPadding);

        QLabel* el = listAllElements_[i];
        //int y =
        el->move(rX(el), eY(lab, el)/*sumPadding*/);

        sumPadding += padding;
    }
}

