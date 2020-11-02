//-----------------------------------------------------------------------------
//
//      Статусная строка кадра
//      (c) РГУПС, ВЖД 6/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Статусная строка кадра
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 6/09/2019
 */

#include "status-bar-block-bottom.h"

#include "fan-imitation.h"


//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
StatusBarBlockBottom::StatusBarBlockBottom(QColor backrg, QRect geo, QWidget *parent)
    : AbstractBlock(geo, parent)
{
    this->setPalette(QPalette(backrg));

    this->createAllChildren_();


}



//-----------------------------------------------------------------------------
//  Обновление данных экрана
//-----------------------------------------------------------------------------
void StatusBarBlockBottom::updateData(status_bar_bottom_data_t *data)
{
    // "вентилятор"
    fanImitation_->setAngle(data->fanAngle);

    // АСТ
    labAST_->setStyleSheet("border: 1px solid black;"
                           "color: " + QString((data->AST) ? ("green") : ("red")) + ";");

    // ТЦ
    labTC_->setStyleSheet("border: 1px solid black;"
                          "color: " + QString((data->TC) ? ("green") : ("red")) + ";");

    // Текущая дата
    labCurData_->setText(data->curModelData);
    // Текущее время
    labCurTime_->setText(data->curModelTime);

}




//-----------------------------------------------------------------------------
//  Создать все дочерние виджеты
//-----------------------------------------------------------------------------
void StatusBarBlockBottom::createAllChildren_()
{
    //
    lab___ = new QLabel(this);
    lab___->resize(505, this->height());
    lab___->move(-1, 0);
    lab___->setStyleSheet("border: 1px solid black;");

    //
    lab2___ = new QLabel(this);
    lab2___->resize(40, this->height());
    lab2___->move(lab___->x() + lab___->width(), 0);
    lab2___->setStyleSheet("border: 1px solid black;");

    // Вентилятор
    fanImitation_ = new FanImitation(QSize(70, this->height()), this);
    fanImitation_->move(lab2___->x() + lab2___->width(), 0);

    // АСТ
    labAST_ = new QLabel("А\nС\nТ", this);
    labAST_->resize(30, this->height());
    labAST_->move(fanImitation_->x() + fanImitation_->width(), 0);
    labAST_->setFont(QFont("Arial", 10, QFont::Medium));
    labAST_->setStyleSheet("border: 1px solid black;"
                           "color: red;");
    labAST_->setAlignment(Qt::AlignCenter);

    // ТЦ
    labTC_ = new QLabel("ТЦ", this);
    labTC_->resize(50, this->height());
    labTC_->move(labAST_->x() + labAST_->width(), 0);
    labTC_->setFont(QFont("Arial", 14, QFont::Medium));
    labTC_->setStyleSheet("border: 1px solid black;"
                          "color: red;");
    labTC_->setAlignment(Qt::AlignCenter);


    // Текущие дата и время
    createDataTime_(QSize(105, this->height()),
                    QPoint(labTC_->x() + labTC_->width(), 0));
}



//-----------------------------------------------------------------------------
//  Создать и расположить виджеты даты и времени
//-----------------------------------------------------------------------------
void StatusBarBlockBottom::createDataTime_(QSize size, QPoint pos)
{
    QLabel* fooLabel = new QLabel(this);
    fooLabel->resize(size);
    fooLabel->move(pos);
    fooLabel->setStyleSheet("border: 1px solid black;"
                            "color: white;"
                            "font: 8pt Arial;"
                            "font-weight: 500;");

    // Текущая дата
    QLabel* fooLabelCurData = new QLabel("Дата:", fooLabel);
    fooLabelCurData->resize(90, 20);
    fooLabelCurData->move(5, 6);
    fooLabelCurData->setStyleSheet("border: none");
    fooLabelCurData->setAlignment(Qt::AlignLeft);

    labCurData_ = new QLabel("00.00.00", fooLabelCurData);
    labCurData_->resize(fooLabelCurData->size());
    labCurData_->setAlignment(Qt::AlignRight);


    // Текущее время
    QLabel* fooLabelCurTime = new QLabel("Время:", fooLabel);
    fooLabelCurTime->resize(90, 20);
    fooLabelCurTime->move(5, fooLabel->height() - fooLabelCurTime->height());
    fooLabelCurTime->setStyleSheet("border: none");
    fooLabelCurTime->setAlignment(Qt::AlignLeft);

    labCurTime_ = new QLabel("00:00:00", fooLabelCurTime);
    labCurTime_->resize(fooLabelCurTime->size());
    labCurTime_->setAlignment(Qt::AlignRight);
}
