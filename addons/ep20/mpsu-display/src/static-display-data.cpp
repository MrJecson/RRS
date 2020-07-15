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

#include "static-display-data.h"

//
QString StaticData::LOG_PATH("../logs/start.log");

//
bool StaticData::HIDE_CURSOR(false);

//
int StaticData::REQUEST_INTERVAL(100);

//
int StaticData::UNTOCHABLE_TIME(500);

//
int StaticData::CH_SYS_IMMUNE_TIME(500);

//
int StaticData::AUDIT_IMMUNE_TIME(500);
