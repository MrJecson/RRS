#ifndef SHAREDSOUNDSSTRUCTURES_H
#define SHAREDSOUNDSSTRUCTURES_H

/*!
 * \struct sounds_level_volume_t
 * \brief Структура громкостей звуков
 */
#pragma pack(push, 1)
struct sounds_level_volume_t
{
    int svisok;
    int tifon;
    int dbitelnost;
    int brake_system;
    int traction_drive;
    int idle;


    sounds_level_volume_t()
        : svisok(40)
        , tifon(40)
        , dbitelnost(40)
        , brake_system(40)
        , traction_drive(40)
        , idle(40)
    {

    }

};
#pragma pack(pop)

#endif // SHAREDSOUNDSSTRUCTURES_H
