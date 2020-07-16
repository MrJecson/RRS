//-----------------------------------------------------------------------------
//
//      Класс простого менеджера вкладок
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс простого менеджера вкладок
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#include "simple-tab-control.h"
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPainter>

#include "simple-tab.h"

#include "display-shared-structures.h"
//#include "structures-display.h"

namespace
{
    constexpr int hOfst = 5;
    constexpr int vOfst = 5;
}



//-----------------------------------------------------------------------------
// Конструктор
//-----------------------------------------------------------------------------
SimpleTabControl::SimpleTabControl(QWidget *container)
    : container_(container)
    , currentTab_(Q_NULLPTR)
{
    QString styleSheetName("font-family: Arial;"
                      "font-size: 14pt;"
                      "color: white;");

    QString styleSheetOther("font-family: Arial;"
                            "font-size: 9pt;"
                            "color: #969696;");

    labelHead_ = new QLabel(container);

    labelBack_ = new QLabel(container_);
    labelBack_->resize(15, 15);
    drawArrowImage_(labelBack_, adLEFT);

    labelPrev_ = new QLabel("prevTab...", container_);
    labelPrev_->setStyleSheet(styleSheetOther);


    labelName_ = new QLabel("labelCurrent", container_);
    labelName_->setStyleSheet(styleSheetName);

    labelNext_ = new QLabel("...labelNext", container_);
    labelNext_->setStyleSheet(styleSheetOther);

    labelFrwd_ = new QLabel(container_);
    labelFrwd_->resize(15, 15);
    drawArrowImage_(labelFrwd_, adRIGHT);

    arrangeHead_();
}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
SimpleTabControl::~SimpleTabControl()
{

}



//-----------------------------------------------------------------------------
// Перейти на следующую вкладку
//-----------------------------------------------------------------------------
void SimpleTabControl::goNextTab()
{
    setCurrettab_(currentTab_->getNextTab());
}



//-----------------------------------------------------------------------------
// Перейти на предыдущую вкладку
//-----------------------------------------------------------------------------
void SimpleTabControl::goPrevTab()
{
    setCurrettab_(currentTab_->getPrevTab());
}



//-----------------------------------------------------------------------------
// Добавить вкладку
//-----------------------------------------------------------------------------
void SimpleTabControl::addTab(SimpleTab *tab, QString mapKey)
{
    listTabs_.append(tab);
    if (mapKey.isEmpty())
    {
        mapKey = tab->getTabName();
    }
    mapTabs_.insert(mapKey, tab);
    connectTabs_();
    setCurrettab_(listTabs_.first());
}



//-----------------------------------------------------------------------------
// Обновить вкладку
//-----------------------------------------------------------------------------
//void SimpleTabControl::updateTab(QString tabName, panel_diagnostic_t *data)
//{
//    SimpleTab* tab = mapTabs_.value(tabName, Q_NULLPTR);

//    if (tab)
//    {
//        tab->updateTab(data);
//    }
//}



//template<typename T>
//void SimpleTabControl::updateTab(QString tabName, screen_data_t *data)
//{
//    SimpleTab* tab = mapTabs_.value(tabName, Q_NULLPTR);

//    if (tab)
//    {
//        tab->updateT<T>(data);
//    }
//}

//template<typename T>
//void SimpleTabControl::updateTab(QString tabName, T data)
//{
//    SimpleTab* tab = mapTabs_.value(tabName, Q_NULLPTR);

//    if (tab)
//    {
//        tab->updateT(data);
//    }
//}



//-----------------------------------------------------------------------------
// Вернуть имя текущей вкладки
//-----------------------------------------------------------------------------
QString SimpleTabControl::getCurrentTabName()
{
    if (currentTab_)
        return currentTab_->getTabName();

    return "null";
}



//-----------------------------------------------------------------------------
// Выровнять заголовок
//-----------------------------------------------------------------------------
void SimpleTabControl::arrangeHead_()
{
    labelPrev_->adjustSize();
    labelName_->adjustSize();
    labelNext_->adjustSize();

    labelPrev_->move(hOfst*2 + labelBack_->width(), vOfst);

    labelBack_->move(hOfst, vOfst);

    int nameX = (container_->width() - labelName_->width())/2;
    labelName_->move(nameX, 0);

    int nextDiff = container_->width() - labelNext_->width();
    labelNext_->move(nextDiff - hOfst*2 - labelFrwd_->width(), vOfst);

    labelFrwd_->move(container_->width() - labelFrwd_->width() - hOfst,
                     vOfst);

    labelHead_->resize(container_->width(), labelName_->height() + hOfst/2);
    drawHead_();
}



//-----------------------------------------------------------------------------
// Соединить указатели вкладок
//-----------------------------------------------------------------------------
void SimpleTabControl::connectTabs_()
{
    if (listTabs_.count() > 1)
    {
        listTabs_.first()->setPrevTab(listTabs_.last());

        for (int i = 0, n = listTabs_.count() - 1; i < n; ++i)
        {
            listTabs_[i]->setNextTab(listTabs_[i+1]);
            listTabs_[i+1]->setPrevTab(listTabs_[i]);
        }

        listTabs_.last()->setNextTab(listTabs_.first());
    }
}



//-----------------------------------------------------------------------------
// Установить текущую вкладку
//-----------------------------------------------------------------------------
void SimpleTabControl::setCurrettab_(SimpleTab *otherTab)
{
    if (otherTab != currentTab_)
    {
        if (currentTab_)
        {
            currentTab_->setTabVisible(false);
        }
        currentTab_ = otherTab;
    }
    currentTab_->setTabVisible(true);
    labelPrev_->setText(currentTab_->getPrevTab()->getTabName() + "...");
    labelName_->setText(currentTab_->getTabName());
    labelNext_->setText("..." + currentTab_->getNextTab()->getTabName());
    arrangeHead_();
}



//-----------------------------------------------------------------------------
// Отрисовать линии шапки заголовка
//-----------------------------------------------------------------------------
void SimpleTabControl::drawHead_()
{
    int w = labelHead_->width();
    int h = labelHead_->height();

    QImage img(labelHead_->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);

    QPainter p(&img);
    p.setPen(QColor("#969696"));

    p.drawLine(0, h - 1, container_->width() - 1, h - 1);
    p.drawLine(w/4, 0, w/4, h);
    p.drawLine(w/4*3, 0, w/4*3, h);

    p.end();

    labelHead_->setPixmap(QPixmap::fromImage(img));
}



//-----------------------------------------------------------------------------
// Отрисовать стрелочку
//-----------------------------------------------------------------------------
void SimpleTabControl::drawArrowImage_(QLabel* label, ArrowDir arrDir)
{
    int w = label->width();
    int h = label->height();
    int m = w/2;

    QImage img(label->size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);

    QPainter p(&img);
    p.setPen(Qt::white);

    p.drawPoint(0, m);
    int i = 0;
    int tall = 0;

    while(i < w && tall < h)
    {
        ++i;
        p.drawLine(i, m - tall, i, m + tall);
        ++tall;
        ++i;
        p.drawLine(i, m - tall, i, m + tall);
    }

    p.end();

    label->setPixmap(QPixmap::fromImage(img).transformed(QTransform().rotate(90 * arrDir)));
}
