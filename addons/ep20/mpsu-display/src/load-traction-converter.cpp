//-----------------------------------------------------------------------------
//
//      Нагрузка тягового преобразователя (ТП)
//      (c) РГУПС, ВЖД 21/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Нагрузка тягового преобразователя (ТП)
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date 21/08/2019
 */

#include "load-traction-converter.h"

//#include "display-shared-structures.h"

#include <QPainter>

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
LoadTractionConverter::LoadTractionConverter(QSize _size, QWidget *parent)
    : QLabel(parent)
    , numPant_old_(1)
{
    this->resize(_size);

    this->setStyleSheet("border: 1px solid black");

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    createGVBV_head_();
    createPantTexts_();
    createTC_texts_();
    createMotorVals_();
}



//-----------------------------------------------------------------------------
//  Установить данные, нарисовать
//-----------------------------------------------------------------------------
void LoadTractionConverter::setValues(load_traction_converter_t data)
{
    draw_(data);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void LoadTractionConverter::createGVBV_head_()
{
    labGVBVHead = new QLabel("ГВ(БВ)", this);
    labGVBVHead->resize(100, 25);
    labGVBVHead->setStyleSheet("border: none;"
                               "color: white;"
                               "font: 11pt Arial;"
                               "font-weight: 600;");
    labGVBVHead->setAlignment(Qt::AlignHCenter);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void LoadTractionConverter::createPantTexts_()
{
    for (int i = 0; i < 2; ++i)
    {
        //
        labPantHead[i] = new QLabel("", this);
        labPantHead[i]->resize(100, 25);
        labPantHead[i]->setStyleSheet("border: none;"
                                      "color: white;"
                                      "font: 11pt Arial;"
                                      "font-weight: 600;");
        labPantHead[i]->setAlignment(Qt::AlignHCenter);


        //
        labPantBottomText[i] = new QLabel("", this);
        labPantBottomText[i]->setStyleSheet("border: none;"
                                            "color: #4d6cf8;"
                                            "font: 7pt Arial;"
                                            "font-weight: 100;");
        labPantBottomText[i]->setAlignment(Qt::AlignHCenter);
    }
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void LoadTractionConverter::createTC_texts_()
{

    for (int i = 0; i < 3; ++i)
    {
        labTC_text[i] = new QLabel("ТПр" + QString::number(i + 1), this);
        labTC_text[i]->resize(110, 25);
        labTC_text[i]->setAlignment(Qt::AlignHCenter);
    }
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void LoadTractionConverter::createMotorVals_()
{
    for (int i = 0; i < 6; ++i)
    {
        labMotorVal[i] = new QLabel("0", this);
        labMotorVal[i]->resize(60, 25);
        labMotorVal[i]->setStyleSheet("border: none;"
                                      "color: white;"
                                      "font: 16pt Arial;"
                                      "font-weight: 600;");
        labMotorVal[i]->setAlignment(Qt::AlignHCenter);
    }
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void LoadTractionConverter::draw_(load_traction_converter_t data)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);


    paint.setPen(QPen(QColor(Qt::white), 3));

    int numPant = 0;
    switch (data.currentType)
    {
    case CurrentTypeEnum::AC:
        numPant = 1;
        break;
    case CurrentTypeEnum::DC:
        numPant = 2;
        break;
    case CurrentTypeEnum::notDetermined:
        numPant = numPant_old_;
        break;

    default:
        numPant = numPant_old_;
    }
    numPant_old_ = numPant;

    QString strPantNum("");
    strPantNum = "ХА" + QString::number(numPant);
    drawPantograph_(&paint, 0, QPoint(95, 29), strPantNum, data.pantograph[0].ready, data.pantograph[0].active);
    paint.drawLine(128, 45, 217, 45);
    drawGVBV_(&paint, QPoint(this->width()/2, 33), data.stateGVBV);
    paint.drawLine(263, 45, 349, 45);
    strPantNum = "ХА" + QString::number(numPant + 2);
    drawPantograph_(&paint, 1, QPoint(350, 29), strPantNum, data.pantograph[1].ready, data.pantograph[1].active);

    paint.drawLine(img_.width()/2, 68, img_.width()/2, 73);
    paint.drawLine(86, 72, 389, 72);

    drawTC_(&paint, 0, 30, data.stateTC[0], &data.stateMotor[0], &data.motorVal[0]);
    drawTC_(&paint, 1, 185, data.stateTC[1], &data.stateMotor[2], &data.motorVal[2]);
    drawTC_(&paint, 2, 335, data.stateTC[2], &data.stateMotor[4], &data.motorVal[4]);


    paint.end();

    this->setPixmap(pix);

}



//-----------------------------------------------------------------------------
//  Нарисовать ГВБВ
//-----------------------------------------------------------------------------
void LoadTractionConverter::drawGVBV_(QPainter *p, QPoint pos, bool connect)
{
    int x = pos.x();
    int y = pos.y();
    int w = 24;

    //
    labGVBVHead->move(x - labGVBVHead->width()/2, y - 29);


    p->setBrush(Qt::transparent);

    p->setPen(QPen(QColor(Qt::white), 3, Qt::DashLine));
    p->drawRect(x - w/2 - 10, y - 8, w + 20, w + 16);

    p->setPen(QPen(QColor(Qt::white), 3));
    p->drawRect(x - w/2, y, w, w);

    if (connect)
    {
        p->drawLine(x, y + 1, x, y + w - 2);
    }
    else
    {
        p->drawLine(x, y + 1, x, y + 6);
        p->drawLine(x + 1, y + 8, x + 6, y + 13);
        p->drawLine(x, y + w - 6, x, y + w - 1);
    }

}



//-----------------------------------------------------------------------------
//  Нарисовать пантограф
//-----------------------------------------------------------------------------
void LoadTractionConverter::drawPantograph_(QPainter *p, int numPant, QPoint pos,
                                            QString head, bool isReady, bool isActiv)
{
    int x = pos.x();
    int y = pos.y();
    int w = 32;

    //
    labPantHead[numPant]->move(x - labPantHead[numPant]->width()/2 + w/2, y - 24);
    labPantHead[numPant]->setText(head);


    if (isReady)
    {
        p->setBrush(QColor("#9195fb"));

        if (isActiv)
            p->setBrush(Qt::green);
    }
    else
        p->setBrush(Qt::transparent);

    //
    p->setPen(QPen(QColor(Qt::white), 3));
    p->drawRect(x, y, w, w);
    //
    p->setPen(QPen(QColor(Qt::white), 3));
    if (isReady && isActiv)
    {
        p->drawLine(x + 8, y + 8, x + w - 8, y + 8);
        p->drawLine(x + w/2, y + 9, x + 13, y + 18);
        p->drawLine(x + 13, y + 18, x + w/2 + 1, y + 24);
    }
    else
    {
        p->drawLine(x + 8, y + 11, x + w - 8, y + 11);
        p->drawLine(x + w/2, y + 12, x + 8, y + 19);
        p->drawLine(x + 8, y + 19, x + w/2, y + 21);
    }


    //
    labPantBottomText[numPant]->resize(w*3, 15);
    labPantBottomText[numPant]->move(x - w + 1, y + w - 1);
    labPantBottomText[numPant]->setText((isReady && !isActiv) ? ("Готов к работе") : (""));
}



//-----------------------------------------------------------------------------
//  Нарисовать тяговый преобразователь (ТП)
//-----------------------------------------------------------------------------
void LoadTractionConverter::drawTC_(QPainter *p, int numTC, int posX,
                                    int stateWork, bool motorStateWork[2], int motorVal[2])
{
    QString backgroundColor("");
    switch (stateWork)
    {
    case stateWorkTC::notConnectChanel:
        backgroundColor = "white";
        break;
    case stateWorkTC::chanelOutage:
        backgroundColor = "red";
        break;
    case stateWorkTC::block:
        backgroundColor = "yellow";
        break;
    case stateWorkTC::norm:
        backgroundColor = "none";
        break;

    default:
        backgroundColor = "none";
    }


    labTC_text[numTC]->move(posX, 78);
    labTC_text[numTC]->setStyleSheet("border: 3px solid white;"
                                     "background: " + backgroundColor + ";"
                                     "color: white;"
                                     "font: 12pt Arial;"
                                     "font-weight: 500;");

    // черточки сверху ТПр[i]
    p->setPen(QPen(QColor(Qt::white), 3));
    p->drawLine(posX + labTC_text[numTC]->width()/2,
                labTC_text[numTC]->y() - 5,
                posX + labTC_text[numTC]->width()/2,
                labTC_text[numTC]->y());

    //p->setPen(QPen(QColor(Qt::white), 3));
    //paint.setBrush(Qt::yellow);
    QPoint pointMotorL = QPoint(labTC_text[numTC]->x() + 20,
                                labTC_text[numTC]->y() + labTC_text[numTC]->height());
    QPoint pointMotorR = QPoint(labTC_text[numTC]->x() + labTC_text[numTC]->width() - 20 - 2,
                                labTC_text[numTC]->y() + labTC_text[numTC]->height());
    drawMotor_(p, numTC*2, pointMotorL, motorStateWork[0], motorVal[0]);
    drawMotor_(p, numTC*2+1, pointMotorR, motorStateWork[1], motorVal[1]);


}



//-----------------------------------------------------------------------------
//  Нарисовать мотор
//-----------------------------------------------------------------------------
void LoadTractionConverter::drawMotor_(QPainter *p, int numMotor, QPoint pos, bool state, int val)
{
    int x = pos.x();
    int y = pos.y();
    int l = 6;
    int w = 12;
    int h = 38;
    p->setPen(QPen(QColor(Qt::white), 3));
    p->setBrush(Qt::transparent);
    p->drawLine(x, y, x, y + l);
    p->drawRect(x - w/2, y + l + 1, w, h);
    y += l + h + 2;
    p->drawLine(x, y,
                x, y + 4);
    y += 5;
    p->drawLine(x - w, y,
                x + w, y);


    //
    p->setPen(QPen( Qt::white,
                    w*2 + 3,
                    Qt::SolidLine,
                    Qt::RoundCap ));
    p->drawPoint(x, pos.y() + l + 1 + h/2);

    //
    if (state)
    {
        p->setPen(QPen( Qt::green,
                        w*2 - 3,
                        Qt::SolidLine,
                        Qt::RoundCap ));
        p->drawPoint(x, pos.y() + l + 1 + h/2);
    }


    labMotorVal[numMotor]->move(x - labMotorVal[numMotor]->width()/2 + 1, y + 2);
    labMotorVal[numMotor]->setText(QString::number(val));
}
