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

#ifndef SCREENDIAGNOSTICS_H
#define SCREENDIAGNOSTICS_H


#include "abstract-screen.h"

#include "display-shared-structures.h"

#include <QPainter>

class FanImitation2;


/*!
 * \class ScreenDiagnostics
 * \brief Класс кадра диагностики
 */
class ScreenDiagnostics : public AbstractScreen
{
public:
    /// Конструктор
    ScreenDiagnostics(QString scrName, QRect scrGeo, QWidget* parent = Q_NULLPTR);


public slots:
//    /// Обработка нажатия кнопок
//    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновление данных экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    QImage img_;

    QLabel* labelBorder_;

    // устройства
    QLabel* labelBTR_[6];
    QLabel* labelCab1_;
    QLabel* labelCab2_;
    QLabel* labelBUGS_;
    QLabel* labelTPr1_;
    QLabel* labelTPr2_;
    QLabel* labelTPr3_;
    QLabel* labelBUE_;
    QLabel* labelBARS_;
    QLabel* labelMK1_;
    QLabel* labelMK2_;
    QLabel* labelBD_;
    QLabel* labelAB_;
    QLabel* labelVPr_;
    QLabel* labelIPCU_;
    QLabel* labelTTr_;
    QLabel* labelKTO_;

    FanImitation2* fanMV11_;
    FanImitation2* fanMV12_;
    FanImitation2* fanMV13_;
    FanImitation2* fanMV14_;
    FanImitation2* fanMV15_;
    FanImitation2* fanMV16_;

    FanImitation2* fanMV21_;
    FanImitation2* fanMV22_;
    FanImitation2* fanMV23_;

    FanImitation2* fanMV31_;
    FanImitation2* fanMV32_;



// ПРЕФИКС ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ *******************************************
    /// Префикс нажатых клавиш
    const QString DIAGNOSTICS_SCREEN_IMG_PREFIX_ = ":/screen-imgs/images/screen-imgs/";


    //  пантограф
    void drawPant_(QPainter *p, QPoint pos, pantograph_t pant);

    // Создание устройств
    void createDevice_(QLabel* &lab, QString name, QSize size, QPoint pos);
    // Изменить фоновый цвет устройства
    void updateDeviceBackgroundColor_(QLabel* lab, int color);


    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

};

#endif // SCREENDIAGNOSTICS_H
