#include "chs2t.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::keyProcess()
{
    if (getKeyState(KEY_9))
    {
        if (isShift())
            EDTSwitch.set();
        else
            EDTSwitch.reset();
    }

    if (getKeyState(KEY_V))
    {
        if (isShift())
            eptSwitch.set();
        else
            eptSwitch.reset();
    }
}
