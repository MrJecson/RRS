#ifndef SHARED_LAUNCHER_STRUCTURES_H
#define SHARED_LAUNCHER_STRUCTURES_H

#include "small-bitset.h"
#include "shared-sounds-structures.h"
#include <string.h>


#pragma pack(push, 1)

struct launcher_settings_t
{
    sounds_level_volume_t sound_levels;

    launcher_settings_t()
        : sound_levels{}
    {

    }

};

#pragma pack(pop)



#pragma pack(push, 1)

struct launcher_bypass_panel_t
{
    bits_t<15> dblSwitches;
    qint8 triSwitches[4];

    launcher_bypass_panel_t()
        : dblSwitches{}
        , triSwitches{}
    {
        dblSwitches.setAll();
        dblSwitches.setBit(dblSwitches.getBitsCount() - 1, false);
        std::fill(triSwitches, triSwitches + 4, 1);
    }

};

#pragma pack(pop)



#pragma pack(push, 1)

struct launcher_data_t
{
    bool terminate;

    launcher_settings_t settings;

    launcher_bypass_panel_t bypass_panel;

    launcher_data_t()
        : terminate(false)
        , settings{}
        , bypass_panel{}
    {

    }

};

#pragma pack(pop)

#endif // SHARED_LAUNCHER_STRUCTURES_H
