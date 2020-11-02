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

#include "soft-buttons-block.h"


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
SoftButtonsBlock::SoftButtonsBlock(QColor backgr, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent), // Передаём базовому классу
    statusArray_{-1, -1, -1, -1, -1, -1, -1, -1, -1}
{
    // Устанавливаем цвет фона
    this->setPalette(backgr);

    // Вызываем метод создания всех кнопок
    createAllChildren_();

    labHead_ = new QLabel(this);
    labHead_->setFont(QFont("Arial", 24, QFont::Medium));
    labHead_->setStyleSheet("border: 1px solid black;"
                            "background: #051432;"
                            "color: white;");
    labHead_->setAlignment(Qt::AlignCenter);
    labHead_->setVisible(false);
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
SoftButtonsBlock::~SoftButtonsBlock()
{

}




//-----------------------------------------------------------------------------
// ПЕРЕОПРЕДЕЛЕНИЕ ЧИСТОГО ВИРТУАЛЬНОГО МЕТОДА ИЗ АБСТРАКТНОГО КЛАССА!
//-----------------------------------------------------------------------------
void SoftButtonsBlock::createAllChildren_()
{
    // Собираем полное имя картинок для загрузки
    QString fooName = BUTTONS_PREFIX_ + "none.png";

    // Названия кнопок в ресурсах берем из массива в файле "consts.h"
    for (int i = 0; i < allCells_.count(); i++)
    {
        // Создаем все кнопки в цикле       // Префикс ресурса
        listButtons_.append(new ImageWidget(fooName, CHILD_SIZE_, this));
        //listButtonsTop_.append(new ImageWidget(fooName, CHILD_SIZE_, this));
    }

    // Вызываем метод АБСТРАКТНОГО класса, выравниваем виджеты.
    autoChildrenPos_(-1);
}


#include <exception>

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void SoftButtonsBlock::setButtonsNames(const QStringList &_list, int idxCurScreen,
                                       QString head, int numCell, int countCell)
{
    using namespace std;


    auto sen = qobject_cast<QWidget*>(sender());

    // Указатель "sender()" может иметь значение "0x0" при прямом вызове слота.
    // Эти действия необходимы для предотвращения смены текста кнопок экраном,
    // скрытым в данный момент.
    if (sen && !sen->isVisible())
        return;

    for (int i = 0, n = min(_list.count(), listButtons_.count()); i < n; ++i)
    {
        ImageWidget::text_opts opts;
        //opts.paddingTop = 0;
        opts.colorText = (i == idxCurScreen) ? Qt::black : Qt::white;

        listButtons_[i]->setText(_list[i], opts);
    }

    labHead_->setVisible(false);

    // перекрытие дополнительным label listButtons для имитирования заголовка
    if ((head != "") && (numCell != -1) && (countCell != -1))
    {
        labHead_->setText(head);
        labHead_->resize((listButtons_[0]->width() - 1)*countCell, this->height());
        labHead_->move(listButtons_[numCell]->x(), 0);
        labHead_->setVisible(true);
    }
}





//void SoftButtonsBlock::setButtonsNamesTop(const QStringList &_list)
//{
//    using namespace std;


//    auto sen = qobject_cast<QWidget*>(sender());

//    // Указатель "sender()" может иметь значение "0x0" при прямом вызове слота.
//    // Эти действия необходимы для предотвращения смены текста кнопок экраном,
//    // скрытым в данный момент.
//    if (sen && !sen->isVisible())
//        return;

//    for (int i = 0, n = min(_list.count(), listButtonsTop_.count()); i < n; ++i)
//    {
//        ImageWidget::text_opts opts;
//        //opts.paddingTop = 0;
//        listButtonsTop_[i]->setText(_list[i], opts);
//    }
//}
