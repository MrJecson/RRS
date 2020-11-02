//-----------------------------------------------------------------------------
//
//      Класс верхней строки состояния окна
//      (c) РГУПС, ВЖД 30/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс верхней строки состояния окна
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 30/03/2017
 */

#ifndef STATUSBARBLOCK_H
#define STATUSBARBLOCK_H


#include "abstract-block.h"

#include "display-shared-structures.h"

class QLabel;

/*!
 * \class SimplePlot
 * \brief Класс реализует верхнюю строку состояния дисплея
 */
class StatusBarBlock : public AbstractBlock
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param backrg - цвет фона
     * \param geo - геометрия
     */
    StatusBarBlock(QColor backrg, QRect geo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~StatusBarBlock();


    /// Установить номер активной кабины
    void setCabin(CabinNumEnum num);
    /// Установить направление движения
    void setDirectionTravel(DirectionTravelEnum dir);
    /// Установить режим управления
    void setControlMode(ControlModeEnum controlMode);
    /// Установить индикацию задания режима тяги или ЭТ
    void setTractionModeIndication(TractionModeIndicationEnum mode);
    /// Установить тип основного тормоза
    void setTypeBrake(TypeBrakeEnum brakeType);
    /// Установить род тока
    void setCurrentType(CurrentTypeEnum currentType);
    /// Установить напряжение контактной сети
    void setContactVoltage(double val);


public slots:
    /// Установить значения строки состояния
    void updateStatusBar(status_bar_data_t* data);


private:
    // Переопределенный чистый виртуальный метод
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;


    /// Номер активной кабины (виджет)
    QLabel* labCabin_;
    /// Направление движения (виджет)
    QLabel* labDirectionTravel_;
    /// Режим управления (виджет)
    QLabel* labControlMode_;
    /// Индикация задания режима тяги или ЭТ (виджет)
    QLabel* labTractionModeIndication_;
    /// Тип основного тормоза (виджет)
    QLabel* labTypeBrake_;
    /// Род тока (виджет)
    QLabel* labCurrentType_;
    /// Напряжение контактной сети (виджет)
    QLabel* labContactVoltage_;


    /// Метод, создающий QLabel'ы по входным параметрам
    void createLabel_(QLabel* &lab, QString text,
                      Qt::AlignmentFlag align,
                      QSize labSize, int _lPad = 0);


};

#endif // STATUSBARBLOCK_H
