#ifndef SHARED_LAUNCHER_DATA_H
#define SHARED_LAUNCHER_DATA_H

namespace LauncherData
{

    /*!
     * \enum BypassBits
     * \brief Перечислитель двухпозиционных переключателей
     */
    enum BypassBits
    {
        BB_FAST_EPT_VALVE,
        BB_EB_FRAME,
        BB_RELEASE_FRAME,
        BB_PASS_EB_FRAME,
        BB_SPB_FRAME,
        BB_TROLLEY_FRAME,
        BB_FIRE_FRAME,
        BB_CLUB,
        BB_EOFF_FRAME,
        BB_TOWING,
        BB_END_SWITCH,
        BB_EPT,
        BB_ACCIDENT_MOVE,
        BB_TRAIN_RADIO,
        BB_DIRECT_BATTERY,
        ___BB_COUNT
    };


    /*!
     * \enum BypassBits
     * \brief Перечислитель трехпозиционных переключателей
     */
    enum BypassInts
    {
        BI_DISPLAYS,
        BI_CCU,
        BI_LIGHT,
        BI_BATTERY,
        ___BI_COUNT
    };

}

#endif // SHARED_LAUNCHER_DATA_H
