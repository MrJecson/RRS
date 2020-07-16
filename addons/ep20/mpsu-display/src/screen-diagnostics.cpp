//-----------------------------------------------------------------------------
//
//      Класс "Диагностика"
//      (c) РГУПС, ВЖД 6/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Диагностика"
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 6/09/2019
 */

#include "screen-diagnostics.h"

#include <QLabel>

#include "fan-imitation2.h"


//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
ScreenDiagnostics::ScreenDiagnostics(QString scrName, QRect scrGeo, QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
{
    //
    this->setVisible(false);

    buttonsNames_ = QStringList{"Главный\nкадр", "Авто-\nведение", "Диагнос-\nтика",
                                "Архив", "ТПр", "", "", "",
                                "СОМ", "Тяговый\nтранс."};

    buttonsNamesTop_ = QStringList{"Отмена", "КТО", "Система\nуправ-я",
                                   "Силовая\nсхема", "Термо-\nконтроль", "БУГС",
                                   "ВПр", "ИПЦУ", "БАРС", "Счетчики"};

    buttonSelectedIdx_ = 2;

    this->createAllChildren_();
}



//-----------------------------------------------------------------------------
//  Обновление данных экрана
//-----------------------------------------------------------------------------
void ScreenDiagnostics::updateScreen(screen_data_t *data)
{
    screen_diagnostics_t* sdt = static_cast<screen_diagnostics_t*>(data);

    //
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);



    // ХА1, ХА2
    drawPant_(&paint, QPoint(120, 58), sdt->pantograph[0]);
    drawPant_(&paint, QPoint(202, 58), sdt->pantograph[1]);
    // ХА4, ХА3
    drawPant_(&paint, QPoint(562, 58), sdt->pantograph[3]);
    drawPant_(&paint, QPoint(660, 58), sdt->pantograph[2]);


    // устройства
    updateDeviceBackgroundColor_(labelBTR_[0], sdt->deviceBTR[0]);
    updateDeviceBackgroundColor_(labelBTR_[1], sdt->deviceBTR[1]);
    updateDeviceBackgroundColor_(labelBTR_[2], sdt->deviceBTR[2]);
    updateDeviceBackgroundColor_(labelBTR_[3], sdt->deviceBTR[3]);
    updateDeviceBackgroundColor_(labelBTR_[4], sdt->deviceBTR[4]);
    updateDeviceBackgroundColor_(labelBTR_[5], sdt->deviceBTR[5]);
    updateDeviceBackgroundColor_(labelCab1_, sdt->deviceCab1);
    updateDeviceBackgroundColor_(labelCab2_, sdt->deviceCab2);
    updateDeviceBackgroundColor_(labelBUGS_, sdt->deviceBUGS);
    updateDeviceBackgroundColor_(labelTPr1_, sdt->deviceTPr1);
    updateDeviceBackgroundColor_(labelTPr2_, sdt->deviceTPr2);
    updateDeviceBackgroundColor_(labelTPr3_, sdt->deviceTPr3);
    updateDeviceBackgroundColor_(labelBUE_, sdt->deviceBUE);
    updateDeviceBackgroundColor_(labelBARS_, sdt->deviceBARS);
    updateDeviceBackgroundColor_(labelMK1_, sdt->deviceMK1);
    updateDeviceBackgroundColor_(labelMK2_, sdt->deviceMK2);
    updateDeviceBackgroundColor_(labelBD_, sdt->deviceBD);
    updateDeviceBackgroundColor_(labelAB_, sdt->deviceAB);
    updateDeviceBackgroundColor_(labelVPr_, sdt->deviceVPr);
    updateDeviceBackgroundColor_(labelIPCU_, sdt->deviceIPCU);
    updateDeviceBackgroundColor_(labelTTr_, sdt->deviceTTr);
    updateDeviceBackgroundColor_(labelKTO_, sdt->deviceKTO);


    fanMV11_->setState(sdt->fanMV11.state);
    fanMV11_->setSpeed(sdt->fanMV11.speed);
    fanMV12_->setState(sdt->fanMV12.state);
    fanMV12_->setSpeed(sdt->fanMV12.speed);
    fanMV13_->setState(sdt->fanMV13.state);
    fanMV13_->setSpeed(sdt->fanMV13.speed);
    fanMV14_->setState(sdt->fanMV14.state);
    fanMV14_->setSpeed(sdt->fanMV14.speed);
    fanMV15_->setState(sdt->fanMV15.state);
    fanMV15_->setSpeed(sdt->fanMV15.speed);
    fanMV16_->setState(sdt->fanMV16.state);
    fanMV16_->setSpeed(sdt->fanMV16.speed);

    fanMV21_->setState(sdt->fanMV21.state);
    fanMV21_->setSpeed(sdt->fanMV21.speed);
    fanMV22_->setState(sdt->fanMV22.state);
    fanMV22_->setSpeed(sdt->fanMV22.speed);
    fanMV23_->setState(sdt->fanMV23.state);
    fanMV23_->setSpeed(sdt->fanMV23.speed);

    fanMV31_->setState(sdt->fanMV31.state);
    fanMV31_->setSpeed(sdt->fanMV31.speed);
    fanMV32_->setState(sdt->fanMV32.state);
    fanMV32_->setSpeed(sdt->fanMV32.speed);


    paint.end();

    labelBorder_->setPixmap(pix);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenDiagnostics::drawPant_(QPainter *p, QPoint pos, pantograph_t pant)
{
    int x = pos.x();
    int y = pos.y();
    int w = 48;
    int h = 43;
    w = 29;
    h = 26;

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
    x += 6;
    w -= 12;
    //
    p->setPen(QPen(QColor(Qt::white), 2));
    if (pant.ready && pant.active)
    {
        y += 6;
        p->drawLine(x, y, x + w, y);
        y += 1;
        p->drawLine(x + w/2 - 1, y, x + 4, y + 7);
        p->drawLine(x + 4, y + 7, x + w/2 + 1, y + 14);
    }
    else
    {
        y += 9;
        p->drawLine(x, y, x + w, y);
        y += 1;
        p->drawLine(x + w/2, y, x + 2, y + 5);
        p->drawLine(x + 2, y + 5, x + w/2 - 1, y + 7);
    }
}



//-----------------------------------------------------------------------------
//  Создание устройств
//-----------------------------------------------------------------------------
void ScreenDiagnostics::createDevice_(QLabel *&lab, QString name, QSize size, QPoint pos)
{
    lab = new QLabel(name, this);
    lab->resize(size);
    lab->move(pos);
    lab->setAlignment(Qt::AlignCenter);
}



//-----------------------------------------------------------------------------
//  Изменить фоновый цвет устройства
//-----------------------------------------------------------------------------
void ScreenDiagnostics::updateDeviceBackgroundColor_(QLabel *lab, int color)
{
    QString res("");
    switch (color)
    {
    case ColorDeviceEnum::red:
        res = "red";
        break;
    case ColorDeviceEnum::gray:
        res = "rgba(120,120,120,150)";
        break;

    case ColorDeviceEnum::green:
        res = "green";
        break;

    case ColorDeviceEnum::orange:
        res = "orange";
        break;
    }

    lab->setStyleSheet("background: " + res + ";"
                       "color: white;");
}



//-----------------------------------------------------------------------------
//  Создать все дочерние виджеты
//-----------------------------------------------------------------------------
void ScreenDiagnostics::createAllChildren_()
{
    QPixmap pixmap(DIAGNOSTICS_SCREEN_IMG_PREFIX_ + "diagnostics.png");

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
    createDevice_(labelBTR_[0], "1", QSize(26, 18), QPoint(299, 92));
    createDevice_(labelBTR_[1], "2", QSize(26, 18), QPoint(328, 92));
    createDevice_(labelBTR_[2], "3", QSize(26, 18), QPoint(358, 92));
    createDevice_(labelBTR_[3], "4", QSize(26, 18), QPoint(387, 92));
    createDevice_(labelBTR_[4], "5", QSize(26, 18), QPoint(480, 92));
    createDevice_(labelBTR_[5], "6", QSize(26, 18), QPoint(509, 92));
    createDevice_(labelCab1_, "Оборуд.\nкабины1", QSize(75, 40), QPoint(42, 114));
    createDevice_(labelCab2_, "Оборуд.\nкабины2", QSize(75, 40), QPoint(680, 114));
    createDevice_(labelBUGS_, "БУГС", QSize(50, 30), QPoint(120, 163));
    createDevice_(labelTPr1_, "ТПр1", QSize(92, 68), QPoint(173, 125));
    createDevice_(labelTPr2_, "ТПр2", QSize(91, 67), QPoint(447, 126));
    createDevice_(labelBUE_, "БУЭ", QSize(45, 32), QPoint(386, 124));
    createDevice_(labelBARS_, "БАРС", QSize(45, 32), QPoint(386, 161));
    createDevice_(labelMK1_, "МК1", QSize(40, 40), QPoint(565, 120));
    createDevice_(labelMK2_, "МК2", QSize(40, 40), QPoint(565, 165));
    createDevice_(labelBD_, "", QSize(26, 16), QPoint(280, 223));
    createDevice_(labelAB_, "АБ", QSize(44, 15), QPoint(488, 221));
    createDevice_(labelVPr_, "ВПр", QSize(59, 25), QPoint(299, 319));
    createDevice_(labelTPr3_, "ТПр3", QSize(85, 31), QPoint(299, 371));
    createDevice_(labelIPCU_, "", QSize(18, 11), QPoint(390, 332));
    createDevice_(labelTTr_, "ТТр", QSize(64, 32), QPoint(459, 369));
    createDevice_(labelKTO_, "", QSize(34, 32), QPoint(530, 368));


    //
    fanMV11_ = new FanImitation2(24, 45, 4, this);
    fanMV11_->move(150, 320);

    fanMV12_ = new FanImitation2(24, 45, 4, this);
    fanMV12_->move(187, 367);

    fanMV13_ = new FanImitation2(24, 45, 4, this);
    fanMV13_->move(361, 320);

    fanMV14_ = new FanImitation2(24, 45, 4, this);
    fanMV14_->move(416, 374);

    fanMV15_ = new FanImitation2(24, 45, 4, this);
    fanMV15_->move(571, 320);

    fanMV16_ = new FanImitation2(24, 45, 4, this);
    fanMV16_->move(626, 367);

    //
    fanMV21_ = new FanImitation2(24, 30, 3, this);
    fanMV21_->move(268, 320);

    fanMV22_ = new FanImitation2(24, 30, 3, this);
    fanMV22_->move(267, 370);

    fanMV23_ = new FanImitation2(24, 30, 3, this);
    fanMV23_->move(540, 320);

    //
    fanMV31_ = new FanImitation2(19, 90, 0, this);
    fanMV31_->move(393, 309);

    fanMV32_ = new FanImitation2(19, 90, 0, this);
    fanMV32_->move(393, 388);


    //
    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
}
