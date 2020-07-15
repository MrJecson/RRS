#ifndef SAPSAN_SHARED_STRUCTURES_H
#define SAPSAN_SHARED_STRUCTURES_H

#include "sapsan-shared-data.h"
#include "directives.h"


struct debug_section_t
{
    double bus_psn_fwd;

    double sw_psn_fwd;

    double sw_psn_bwd;

    double cha_out;

    double bus_cha_fwd;

    double sw_bat_fwd;

    double sw_bat_bwd;

    double bus_bat_fwd;

    bool i_inv;
};

// DELETE
struct debug_data_t
{
    debug_section_t pri;
    debug_section_t sec;
};

struct bogos_debug_t
{
    double p_n_1;
    double p_n_2;
    double p_gr;
    double dp;
    bool h;

};

// ---------------------------------------------------------------------------
//
//      Структура электрического тока
//
// ---------------------------------------------------------------------------
/*!
 * \struct power_t
 * \brief Структура электрического тока
 */
struct power_t
{
    PowerSystemData::PowerType type;    ///< Род тока
    double value;                       ///< Напряжение

    /// Конструктор по умолчанию
    power_t()
        : type(PowerSystemData::PT_NA)
        , value(0.0)
    {

    }

    /// Конструктор для использования
    power_t(PowerSystemData::PowerType pt, double val)
        : type(pt)
        , value(val)
    {

    }

    bool operator<(const power_t &other) const
    {
        return value < other.value;
    }
};


/*!
 * \struct section_block_t
 * \brief Структура команд блокировки/деблокировки от дисплеев
 */
struct section_block_t
{
    section_set_t blocks;
    section_set_t deblocks;

    void operator |=(section_block_t &other)
    {
        blocks |= other.blocks;
        deblocks |= other.deblocks;
    }
};


/*!
 * \struct status_feedback_t
 * \brief Структура состояний устройств силовой схемы
 */
struct status_feedback_t
{
    section_set_t states;
    section_set_t curBlocks;
    section_set_t reqBlocks;
};

#endif // SAPSAN_SHARED_STRUCTURES_H
