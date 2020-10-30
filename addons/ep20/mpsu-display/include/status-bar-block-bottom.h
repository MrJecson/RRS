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

#ifndef STATUSBARBLOCKBOTTOM_H
#define STATUSBARBLOCKBOTTOM_H

#include <QTimer>

#include "abstract-block.h"
#include "display-shared-structures.h"

class FanImitation;


/*!
 * \class StatusBarBlockBottom
 * \brief Статусная строка кадра
 */
class StatusBarBlockBottom : public AbstractBlock
{
public:
    /// Конструктор
    StatusBarBlockBottom(QColor backrg, QRect geo, QWidget* parent = Q_NULLPTR);


public slots:
    /// Установить данные статусной строки кадра
    void updateData(status_bar_bottom_data_t* data);




private:

    QTimer  *activeIntervalTimer_;


    // Переопределенный чистый виртуальный метод
    /// Метод создания дочерних виджетов
    void createAllChildren_() Q_DECL_OVERRIDE;

    //
    QLabel* lab___;
    QLabel* lab2___;
    //
    FanImitation* fanImitation_;
    //
    QLabel* labAST_;
    //
    QLabel* labTC_;
    //
    QLabel* labCurData_;
    QLabel* labCurTime_;


    void createDataTime_(QSize size, QPoint pos);

};

#endif // STATUSBARBLOCKBOTTOM_H
