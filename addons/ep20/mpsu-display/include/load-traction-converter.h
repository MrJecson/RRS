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

#ifndef LOADTRACTIONCONVERTER_H
#define LOADTRACTIONCONVERTER_H

#include <QLabel>

#include "display-shared-structures.h"


/*!
 * \class LoadTractionConverter
 * \brief Нагрузка тягового преобразователя (ТП)
 */
class LoadTractionConverter : public QLabel
{
public:
    /// Конструктор
    LoadTractionConverter(QSize _size, QWidget* parent = Q_NULLPTR);

    /// Установить данные, нарисовать
    void setValues(load_traction_converter_t data);

private:
    QImage img_;

    int numPant_old_;


    QLabel* labGVBVHead;
    QLabel* labPantHead[2];
    QLabel* labPantBottomText[2];
    QLabel* labTC_text[3];
    QLabel* labMotorVal[6];

    void createGVBV_head_();
    void createPantTexts_();
    void createTC_texts_();
    void createMotorVals_();


    void draw_(load_traction_converter_t data);


    void drawGVBV_(QPainter* p, QPoint pos, bool connect);
    void drawPantograph_(QPainter* p, int numPant, QPoint pos, QString head, bool isReady, bool isActiv);
    void drawTC_(QPainter* p, int numTC, int posX, int stateWork, bool motorStateWork[2], int motorVal[2]);
    void drawMotor_(QPainter* p, int numMotor, QPoint pos, bool state, int val);

};

#endif // LOADTRACTIONCONVERTER_H
