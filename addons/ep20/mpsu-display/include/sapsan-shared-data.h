#ifndef SAPSAN_SHARED_DATA_H
#define SAPSAN_SHARED_DATA_H


#include "stddef.h"
#include "small-bitset.h"


enum
{
    // Число осей на тележке
    AXIS_PER_TROLLEY = 2,
    // Число тележек вагоне
    TROLLEYS_PER_VEHICLE = 2,

    // Число тяговых вагонов поезда
    TRAC_VEHICLES_NUM = 4,
    // Число обычных вагонов
    FREE_VEHICLES_NUM = 6,
    //
    TOTAL_VEHICLES_NUM = TRAC_VEHICLES_NUM + FREE_VEHICLES_NUM, // 4 + 6 = 10

    // Число осей на вагоне
    AXIS_PER_VEHICLE = AXIS_PER_TROLLEY*TROLLEYS_PER_VEHICLE, // 2 * 2 = 4
    // Число осей на тяговом вагоне
    AXIS_PER_TRAC_VEHICLE = AXIS_PER_VEHICLE, // 4
    // Число осей на обычном вагоне
    AXIS_PER_FREE_VEHICLE = AXIS_PER_VEHICLE, // 4

    // Число тяговых осей всего поезда
    TRAC_AXIS_PER_TRAIN = AXIS_PER_TRAC_VEHICLE*TRAC_VEHICLES_NUM, // 4 * 4 = 16
    // Число свободных осей всего поезда
    FREE_AXIS_PER_TRAIN = AXIS_PER_FREE_VEHICLE*FREE_VEHICLES_NUM, // 4 * 6 = 24
    //
    AXIS_PER_TRAIN = TRAC_AXIS_PER_TRAIN + FREE_AXIS_PER_TRAIN, // 16 + 24 = 40
};


// Количество секций силовой схемы
constexpr int SECTIONS_NUM = 2;


// Количество токоприёмников переменного тока на одной секции
constexpr int AC_PANTS_NUM = 1;

// Количество главных выключателей на одной секции
constexpr int MAIN_SWITCH_NUM = 1;

// Количество крышевых разъединителей на одной секции
constexpr int ROOF_KEY_NUM = 1;

// Количество устройств одной секции силовой схемы переменного тока
constexpr int AC_DEVICES_NUM = AC_PANTS_NUM + MAIN_SWITCH_NUM + ROOF_KEY_NUM;


// Количество токоприёмников постоянного тока на одной секции
constexpr int DC_PANTS_NUM = 2;

// Количество быстродействующих выключателей на одной секции
constexpr int FAST_SWITCH_NUM = 1;

// Количество устройств одной секции силовой схемы постоянного тока
constexpr int DC_DEVICES_NUM = DC_PANTS_NUM + FAST_SWITCH_NUM;


// Количество тяговых преобразователей на одной секции
constexpr int CONV_TRAC_NUM = 2;

// Количество импульсных инверторов на одной секции
constexpr int INVERTERS_PER_SEC = 2;

//
constexpr int INVERTERS_NUM = INVERTERS_PER_SEC * SECTIONS_NUM;

//
constexpr int MOTORS_PER_INVERTER = 4;

// Количество преобразователей собственных нужд на одной секции
constexpr int SNC_NUM = 3;

// Количество устройств в одной секции поезда
constexpr size_t SEC_DEV_NUM = DC_PANTS_NUM + AC_PANTS_NUM +
                               MAIN_SWITCH_NUM + FAST_SWITCH_NUM +
                               ROOF_KEY_NUM + CONV_TRAC_NUM + SNC_NUM;

// структура команд блокировки для одной секции
//typedef bits_t<SEC_DEV_NUM> section_cmd_t_old;

typedef bits_t<SEC_DEV_NUM> section_set_t;


// Минимальное значение напряжения переменного тока
constexpr double AC_MIN = 19.0;

// Максимальное значение напряжения переменного тока
constexpr double AC_MAX = 29.0;

// Минимальное значение напряжения постоянного тока
constexpr double DC_MIN = 2.1;

// Максимальное значение напряжения постоянного тока
constexpr double DC_MAX = 4.0;


//
constexpr int MOTORS_PER_VEH = 4;

//
constexpr int MOTOR_VEH_PER_SEC = 2;

//
constexpr int MOTORS_NUM = MOTORS_PER_VEH * MOTOR_VEH_PER_SEC * SECTIONS_NUM;


namespace PowerSystemData
{
    /*!
     * \brief Перечислитель типов тока
     */
    enum PowerType
    {
        PT_NA,  ///< Неопределённый род тока
        PT_AC,  ///< Переменный ток
        PT_DC   ///< Постоянный ток
    };


    /*!
     * \brief Перечислитель битов команд одной секции
     */
    enum CmdBits
    {
        CB_DC_PAN1,     ///< Токопр. постоянного тока 1
        CB_DC_PAN2,     ///< Токопр. постоянного тока 2
        CB_AC_PAN,      ///< Токопр. переменного тока
        CB_FAST_SW,     ///< Быстродейсвтующий выключатель
        CB_MAIN_SW,     ///< Главный выключатель
        CB_ROOF_KEY,    ///< Крышевой разъединитель
        CB_TR_CON1,     ///< Тяговый преобразователь 1
        CB_TR_CON2,     ///< Тяговый преобразователь 2
        CB_SNC,         ///< Преобразователь собственных нужд
        CB_D_SNC1,      ///< Первый ПСН сдвоенного контейнера
        CB_D_SNC2       ///< Второй ПСН сдвоенного контейнера
    };


    /// Количество впомогательных бит
    constexpr int EXTRA_BITS_NUM = 6;

    /// Вспомогательные биты команд
    typedef bits_t<EXTRA_BITS_NUM> extra_bits_t;

    /*!
     * \brief Перечислитель команд в битовом поле "extra"
     */
    enum ExtraBits
    {
        EB_DC_SYS,      ///< Бит переключения на систему постоянного тока
        EB_AC_SYS,      ///< Бит переключения на систему переменного тока
        EB_AUDIT,       ///< Бит включения/выключения аудита
        EB_RESET_TMPM,  ///< Бит сброса манометра ТМ, ПМ
        EB_RESET_TC12,  ///< Бит сброса манометра ТЦ1, ТЦ2
        EB_STOP_MODEL   ///< Бит остановки моделирования
    };

}

namespace SpeedRegulatorData
{

    enum SpeedRegulatorMode
    {
        SRM_NA    = 0x0,
        SRM_OFF   = 0x1,
        SRM_2KMH  = 0x2,
        SRM_5KMH  = 0x4,
        SRM_10KMH = 0x8,
        SRM_25KMH = 0x10,
        SRM_APPLY = 0x20
    };

    template <typename T>
    SpeedRegulatorMode srm_cast(T _val)
    {
        static_assert(std::is_integral<T>::value, "type isn't integral");
        return static_cast<SpeedRegulatorMode>(_val);
    }

}

#endif // SAPSAN_SHARED_DATA_H
