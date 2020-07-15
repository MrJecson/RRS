//22/01/2018
#ifndef EVS2_SHARED_STRUCTURES_H
#define EVS2_SHARED_STRUCTURES_H

#include "small-bitset.h"

#include "sapsan-shared-data.h"
#include "sapsan-shared-structures.h"


#pragma pack(push, 1)
struct commands_from_clients_t
{
    /*!
     * \name Флаги состояний и блокировки устройств секций
     * бит 0  - Токопр. постоянного тока 1
     * бит 1  - Токопр. постоянного тока 2
     * бит 2  - Токопр. переменного тока
     * бит 3  - Быстродейсвтующий выключатель
     * бит 4  - Главный выключатель
     * бит 5  - Крышевой разъединитель
     * бит 6  - Тяговый преобразователь 1
     * бит 7  - Тяговый преобразователь 2
     * бит 8  - ПСН
     * бит 9  - Первый ПСН сдвоенного контейнера
     * бит 10 - Второй ПСН сдвоенного контейнера
     */
    ///@{
    section_block_t primary;
    section_block_t secondary;
    ///@}


    /*!
     * \name Дополнительные команды
     * бит 0 - Переключиться на систему постоянного тока
     * бит 1 - Переключиться на сисетму переменного тока
     * бит 2 - Режим "Аудит"
     * бит 3 - Сброс манометра ТМ/ПМ
     * бит 4 - Сброс манометра ТЦ1/ТЦ2
     * бит 5 - Флаг отключения модели
     */
    ///@{
    PowerSystemData::extra_bits_t extra;
    ///@}

    ///
    SpeedRegulatorData::SpeedRegulatorMode refSpeedRegMode;


    commands_from_clients_t()
        : refSpeedRegMode(SpeedRegulatorData::SRM_NA)
    {

    }


    void operator|=(commands_from_clients_t &other)
    {
        using namespace SpeedRegulatorData;

        primary |= other.primary;
        secondary |= other.secondary;

        extra |= other.extra;

        refSpeedRegMode = srm_cast(refSpeedRegMode | other.refSpeedRegMode);
    }

};
#pragma pack(pop)


#endif // EVS2_SHARED_STRUCTURES_H
