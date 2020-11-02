//-----------------------------------------------------------------------------
//
//      Класс статических данных проекта "Дисплей"
//      (c) РГУПС, ВЖД 16/11/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс экрана вывода лога
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 16/11/2017
 */

#ifndef STATICDISPLAYDATA_H
#define STATICDISPLAYDATA_H

#include <QString>

/*!
 * \class StaticData
 * \brief Класс статических данных проекта "Дисплей"
 */
struct StaticData
{
    //
    static QString LOG_PATH;

    //
    static bool HIDE_CURSOR;

    //
    static int REQUEST_INTERVAL;

    //
    static int UNTOCHABLE_TIME;

    //
    static int CH_SYS_IMMUNE_TIME;

    //
    static int AUDIT_IMMUNE_TIME;

};

#endif // STATICDISPLAYDATA_H
