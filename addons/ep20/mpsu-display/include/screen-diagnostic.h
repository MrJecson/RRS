//-----------------------------------------------------------------------------
//
//      Класс "Диагностика тренажёра"
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Диагностика тренажёра"
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#ifndef SCREENDIAGNOSTIC_H
#define SCREENDIAGNOSTIC_H

#include "abstract-screen.h"

class SimpleTabControl;

/*!
 * \class ScreenDiagnostic
 * \brief Класс экрана диангостики тренажёра
 */
class ScreenDiagnostic Q_DECL_FINAL : public AbstractScreen
{

public:
    /// Конструктор
    ScreenDiagnostic(QString scrName, QRect scrGeo,
                     QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~ScreenDiagnostic();

    /// Получить флаг сброса манометра ТМ/ПМ
    bool getResetManometerTMPM();

    /// Получить флаг сброса манометра ТЦ1/ТЦ2
    bool getResetManometerTC12();


public slots:
    /// Обработка нажатия кнопки
    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновить данные экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    // Простой табконтрол
    SimpleTabControl* tabControl_; ///< Простой табконтрол

    // Надпись модельного времени
    QLabel* labelModelTime_; ///< Надпись модельного времени

    // Флаги сброса манометров
    quint8 resetManometerTMPM_; ///< Флаг сброса манометра ТМ/ПМ
    quint8 resetManometerTC12_; ///< Флаг сброса манометра ТЦ1/ТЦ2

    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

};

#endif // SCREENDIAGNOSTIC_H
