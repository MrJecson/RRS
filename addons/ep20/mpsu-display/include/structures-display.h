//-----------------------------------------------------------------------------
//
//      Объявление различных структур для передачи значений
//      (c) РГУПС, ВЖД 07/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Объявление различных структур для передачи значений
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 07/04/2017
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <qcompilerdetection.h>
#include "sapsan-shared-data.h"
#include "qglobal.h"
//#include "display-shared-data.h"


/*!
 * \brief refs_t struct - структура массивов указателей состояния элементов
 * управления в соответстующих экранах
 */
struct refs_t
{
    ///
    const bool** AC_CurBlocks; // delete
    ///
    const bool** AC_ReqBlocks; // delete

    ///
    const bool** DC_CurBlocks; // delete
    ///
    const bool** DC_ReqBlocks; // delete

    ///
    const bool** conv_CurBlocks; // delete
    ///
    const bool** conv_ReqBlocks; // delete

    ///
    const bool** primary_CurBlocks;
    ///
    const bool** primary_ReqBlocks;

    ///
    const bool** secondary_CurBlocks;
    ///
    const bool** secondary_ReqBlocks;

    ///
    quint8 curPowerType;
    quint8 reqPowerType;

    ///
    SpeedRegulatorData::SpeedRegulatorMode refSpeedRegMode;

    refs_t()
        : AC_CurBlocks(Q_NULLPTR) // delete
        , AC_ReqBlocks(Q_NULLPTR) // delete
        , DC_CurBlocks(Q_NULLPTR) // delete
        , DC_ReqBlocks(Q_NULLPTR) // delete
        , conv_CurBlocks(Q_NULLPTR) // delete
        , conv_ReqBlocks(Q_NULLPTR) // delete

        , primary_CurBlocks(Q_NULLPTR)
        , primary_ReqBlocks(Q_NULLPTR)

        , secondary_CurBlocks(Q_NULLPTR)
        , secondary_ReqBlocks(Q_NULLPTR)

        , curPowerType(PowerSystemData::PT_DC)
        , reqPowerType(PowerSystemData::PT_DC)
        , refSpeedRegMode(SpeedRegulatorData::SRM_NA)
    {

    }
};

struct power_types_t
{
    PowerSystemData::PowerType curPowerType;
    PowerSystemData::PowerType reqPowerType;
};

#endif // STRUCTURES_H

