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

#ifndef SCREENPOWERCIRCUIT_H
#define SCREENPOWERCIRCUIT_H


#include "abstract-screen.h"

#include "display-shared-structures.h"

#include <QPainter>


/*!
 * \class ScreenPowerCircuit
 * \brief Класс кадра силовой схемы
 */
class ScreenPowerCircuit : public AbstractScreen
{
public:
    ScreenPowerCircuit(QString scrName, QRect scrGeo, QWidget* parent = Q_NULLPTR);


public slots:
//    /// Обработка нажатия кнопок
//    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновление данных экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    QImage img_;

    QLabel* labelBorder_;

    QLabel* labelI_;
    QLabel* labelU_;
    QLabel* labelKeyState_;



// ПРЕФИКС ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ *******************************************
    /// Префикс нажатых клавиш
    const QString POWER_CIRCUIT_SCREEN_IMG_PREFIX_ = ":/screen-imgs/images/screen-imgs/";


    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

    //  правая часть экрана
    void drawRightPart_();

    //  пантограф
    void drawPant_(QPainter *p, QPoint pos, pantograph_t pant);
    //  переключатель
    void drawDisconnector_(QPainter *p, QPoint pos, DisconnectorEnum state);
    //  ключ
    void drawKey_(QPainter *p, QPoint pos, KeyStateEnum state);
    //  ПРТ
    void drawPRT_(QPainter *p, QPoint pos, DisconnectorEnum state);
    //  индикатор заземления
    void drawGroundIndicator_(QPainter *p, QPoint pos, bool isClosed);


};

#endif // SCREENPOWERCIRCUIT_H
