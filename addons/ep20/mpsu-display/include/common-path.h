//------------------------------------------------------------------------------
//
//      Пути, используемые всеми модулями проекта
//      (с) РГУПС, ВЖД 25/01/2018
//      Разработал: Притыкин Д.Е.
//
//------------------------------------------------------------------------------
#ifndef     COMMON_PATH_H
#define     COMMON_PATH_H

/// Путь к конфигам
#define CFG_PATH QString("../cfg/")
/// Путь к логам
#define LOG_PATH QString("../logs/")
/// Путь к сценариям
#define SCN_PATH (CFG_PATH + QString("evs2/scenarios/"))
/// Путь к папке с хешами
#define SECURITY_PATH QString("../.security/")
/// Файл пройденной дистанции 1
#define DISTANCE_TRAVELED_FILE_1 SECURITY_PATH + QString("hashdt1")
/// Файл пройденной дистанции 2
#define DISTANCE_TRAVELED_FILE_2 SECURITY_PATH + QString("hashdt2")

#endif // COMMON_PATH_H
