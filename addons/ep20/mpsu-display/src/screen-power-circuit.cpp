//-----------------------------------------------------------------------------
//
//      Класс "Силовая схема"
//      (c) РГУПС, ВЖД 9/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Силовая схема"
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 9/09/2019
 */

#include "screen-power-circuit.h"

#include <QLabel>


//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
ScreenPowerCircuit::ScreenPowerCircuit(QString scrName, QRect scrGeo, QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
{
    //
    this->setVisible(false);

    buttonsNames_ = QStringList{"Главный\nкадр", "Авто-\nведение", "Диагнос-\nтика",
                                "Архив", "Цепи\nотопления", "", "", "",
                                "", "Управ-\nление QS"};

    buttonsNamesTop_ = QStringList{"Отмена", "", "", "", "", "", "", "", "", ""};

    buttonNamesHead_ = "Силовая схема";
    buttonNamesHeadNum_ = 1;
    buttonNamesHeadCount_ = 9;

    //
    this->createAllChildren_();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::updateScreen(screen_data_t *data)
{
    screen_power_circuit_t* spct = static_cast<screen_power_circuit_t*>(data);

    //
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    paint.setPen(QPen(QColor(Qt::white), 2));


    // ХА1, ХА2
    drawPant_(&paint, QPoint(108, 37), spct->pantograph[0]);
    drawPant_(&paint, QPoint(218, 37), spct->pantograph[1]);
    paint.drawLine(158, 58, 218, 58);

    // SQ1
    paint.drawLine(188, 58, 188, 70);
    drawDisconnector_(&paint, QPoint(170, 70), spct->roofKeyQS1);
    paint.drawLine(188, 101, 188, 112);

    // ХА3, ХА4
    drawPant_(&paint, QPoint(340, 37), spct->pantograph[2]);
    drawPant_(&paint, QPoint(450, 37), spct->pantograph[3]);
    paint.drawLine(390, 58, 450, 58);

    // SQ2
    paint.drawLine(420, 58, 420, 70);
    drawDisconnector_(&paint, QPoint(402, 70), spct->roofKeyQS2);
    paint.drawLine(420, 101, 420, 112);

    // ГВ
    drawKey_(&paint, QPoint(88, 141), spct->GV);
    drawGroundIndicator_(&paint, QPoint(96, 198), spct->groundingGV);

    // БВ
    drawKey_(&paint, QPoint(337, 141), spct->BV);

    // ПРТ
    drawPRT_(&paint, QPoint(450, 141), spct->prt);

    // Q11 (индикатор состояний переключателя депо 380В)
    drawDisconnector_(&paint, QPoint(545, 364), spct->depo);


    //
    paint.setPen(QPen(Qt::yellow, 2));
    // желтая линия на участке QS1 - БВ
    if ((spct->BV == KeyStateEnum::ks_closed) || (spct->BV == KeyStateEnum::ks_readyClosed))
    {
        paint.drawLine(385, 161, 529, 161);
        paint.drawLine(529, 161, 529, 113);
        paint.drawLine(529, 113, 188, 113);
        paint.drawLine(188, 113, 188, 103);
    }

    // желтая линия на участке QS2 - ГВ
    if ((spct->GV == KeyStateEnum::ks_closed) || (spct->GV == KeyStateEnum::ks_readyClosed))
    {
        paint.drawLine(86, 161, 45, 161);
        paint.drawLine(45, 161, 45, 113);
        paint.drawLine(45, 113, 420, 113);
        paint.drawLine(420, 113, 420, 103);
    }

    // значения силы тока и напряжения сети
    labelI_->setText(QString::number(spct->I, 'f', 1) + " А");
    labelU_->setText(QString::number(spct->U, 'f', 1) + " КВ");



    paint.end();

    labelBorder_->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::createAllChildren_()
{
    QPixmap pixmap(POWER_CIRCUIT_SCREEN_IMG_PREFIX_ + "power-circuit.png");

    //
    QLabel* labImg = new QLabel(this);
    labImg->resize(this->size());
    labImg->setPixmap(pixmap);

    //
    labelBorder_ = new QLabel(this);
    labelBorder_->resize(this->size());
    labelBorder_->setStyleSheet("border: 1px solid black;"
                                "border-top: 2px solid black;"
                                "color: white;");

    //
    drawRightPart_();

    //
    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawRightPart_()
{
    int labTextW = 200;
    int labValW = 150;
    //
    QLabel* labI = new QLabel("Сила тока контактной\nсети", this);
    labI->resize(labTextW, 50);
    labI->move(this->width() - labTextW - 5, 10);
    labI->setFont(QFont("Arial", 13));
    labI->setAlignment(Qt::AlignCenter);

    labelI_ = new QLabel(this);
    labelI_->resize(labValW, 35);
    labelI_->move(this->width() - labValW - 30, 60);
    labelI_->setFont(QFont("Arial", 20));
    labelI_->setStyleSheet("border: 1px solid white;"
                           "color: white;");
    labelI_->setAlignment(Qt::AlignCenter);


    //
    QLabel* labU = new QLabel("Напряжение\nконтактной сети", this);
    labU->resize(labTextW, 50);
    labU->move(this->width() - labTextW - 5, 110);
    labU->setFont(QFont("Arial", 13));
    labU->setAlignment(Qt::AlignCenter);

    labelU_ = new QLabel(this);
    labelU_->resize(labValW, 35);
    labelU_->move(this->width() - labValW - 30, 160);
    labelU_->setFont(QFont("Arial", 20));
    labelU_->setStyleSheet("border: 1px solid white;"
                           "color: white;");
    labelU_->setAlignment(Qt::AlignCenter);


    //
    QLabel* labKeyState = new QLabel("Состояние ключа\nZ1-DJ", this);
    labKeyState->resize(labTextW, 50);
    labKeyState->move(this->width() - labTextW - 5, 210);
    labKeyState->setFont(QFont("Arial", 13));
    labKeyState->setAlignment(Qt::AlignCenter);

    labelKeyState_ = new QLabel("рабочее", this);
    labelKeyState_->resize(labValW, 35);
    labelKeyState_->move(this->width() - labValW - 30, 260);
    labelKeyState_->setFont(QFont("Arial", 13));
    labelKeyState_->setStyleSheet("border: 1px solid white;"
                                  "color: green;");
    labelKeyState_->setAlignment(Qt::AlignCenter);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawPant_(QPainter *p, QPoint pos, pantograph_t pant)
{
    int x = pos.x();
    int y = pos.y();
    int w = 48;
    int h = 43;

    if (pant.ready)
    {
        p->setBrush(QColor("#9195fb"));

        if (pant.active)
            p->setBrush(Qt::green);
    }
    else
        p->setBrush(Qt::transparent);

    //
    p->setPen(QPen(QColor(Qt::white), 2));
    p->drawRect(x, y, w, h);
    //
    x += 10;
    w -= 20;
    //
    p->setPen(QPen(QColor(Qt::white), 2));
    if (pant.ready && pant.active)
    {
        y += 10;
        p->drawLine(x, y, x + w, y);
        y += 1;
        p->drawLine(x + w/2 - 1, y, x + 6, y + 12);
        p->drawLine(x + 6, y + 12, x + w/2 + 1, y + 23);
    }
    else
    {
        y += 15;
        p->drawLine(x, y, x + w, y);
        y += 1;
        p->drawLine(x + w/2, y, x + 2, y + 9);
        p->drawLine(x + 2, y + 9, x + w/2 - 1, y + 12);
    }
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawDisconnector_(QPainter *p, QPoint pos, DisconnectorEnum state)
{
    int x = pos.x();
    int y = pos.y();
    int w = 40;
    int h = 35;
    w = 36;
    h = 31;

    bool isClosed = false;
    bool isOpen = false;

    switch (state)
    {
    case DisconnectorEnum::open:
        p->setBrush(Qt::transparent);
        isOpen = true;
        break;
    case DisconnectorEnum::closed:
        p->setBrush(Qt::green);
        isClosed = true;
        break;
    case DisconnectorEnum::undefined:
        p->setBrush(Qt::red);
        break;
    }

    p->drawRect(x, y, w, h);
    p->drawLine(x + w/2, y, x + w/2, y + h/3 - 2);
    if (isClosed)
        p->drawLine(x + w/2, y + h/3 - 1, x + w/2, y + h*2/3 + 2);
    if (isOpen)
        p->drawLine(x + w/2, y + h/3 - 1, x + w*3/4, y + h*2/3 - 3);
    p->drawLine(x + w/2, y + h*2/3 + 3, x + w/2, y + h);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawKey_(QPainter *p, QPoint pos, KeyStateEnum state)
{
    int x = pos.x();
    int y = pos.y();
    int w = 46;
    int h = 41;

    bool isClosed = false;

    switch (state)
    {
    case KeyStateEnum::ks_open:
        p->setBrush(Qt::transparent);
        break;
    case KeyStateEnum::ks_closed:
        p->setBrush(Qt::green);
        isClosed = true;
        break;
    case KeyStateEnum::ks_readyClosed:
        p->setBrush(QColor("#9195fb"));
        break;
    case KeyStateEnum::ks_fail:
        p->setBrush(Qt::red);
        break;
    }

    p->drawRect(x, y, w, h);
    p->drawLine(x, y + h/2, x + w/3 - 2, y + h/2);
    if (isClosed)
        p->drawLine(x + w/3 - 1, y + h/2, x + w*2/3 + 2, y + h/2);
    else
        p->drawLine(x + w/3 - 1, y + h/2, x + w*2/3 - 4, y + h/5);
    p->drawLine(x + w*2/3 + 3, y + h/2, x + w, y + h/2);

}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawPRT_(QPainter *p, QPoint pos, DisconnectorEnum state)
{
    int x = pos.x();
    int y = pos.y();
    int w = 46;
    int h = 41;

    bool isClosed = false;
    bool isOpen = false;

    switch (state)
    {
    case DisconnectorEnum::open:
        p->setBrush(Qt::transparent);
        isOpen = true;
        break;
    case DisconnectorEnum::closed:
        p->setBrush(Qt::green);
        isClosed = true;
        break;
    case DisconnectorEnum::undefined:
        p->setBrush(Qt::red);
        break;
    }

    p->drawRect(x, y, w, h);

    p->drawLine(x, y + h/2, x + w/3 - 2, y + h/2);

    if (isClosed)
        p->drawLine(x + w/3 - 1, y + h/2, x + w*2/3 - 4, y + h*4/5);

    if (isOpen)
        p->drawLine(x + w/3 - 1, y + h/2, x + w*2/3 + 2, y + h/2);

    p->drawLine(x + w*2/3 + 3, y + h/2, x + w, y + h/2);

    p->drawLine(x + w*2/3 - 4, y + h*4/5, x + w*2/3 - 4, y + h);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPowerCircuit::drawGroundIndicator_(QPainter *p, QPoint pos, bool isClosed)
{
    int x = pos.x();
    int y = pos.y();
    int w = 30;
    int h = 30;

    if (isClosed)
        p->setBrush(Qt::green);

    p->drawRect(x, y, w, h);
    p->drawLine(x + w/2, y, x + w/2, y + h/3 - 2);
    if (isClosed)
        p->drawLine(x + w/2, y + h/3 - 1, x + w/2, y + h*2/3 + 2);
    else
        p->drawLine(x + w/5, y + h/3 + 3, x + w/2, y + h*2/3 + 2);
    p->drawLine(x + w/2, y + h*2/3 + 3, x + w/2, y + h);
}

