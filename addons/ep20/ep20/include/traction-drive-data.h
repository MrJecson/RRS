#ifndef TRACTIONDRIVEDATA_H
#define TRACTIONDRIVEDATA_H

//------------------------------------------------------------------------------
// Нумератор Тяговых Приводов!
//------------------------------------------------------------------------------
enum
{
    NUM_TRACTION_DRIVE = 3,
    TRACTION_DRIVE_1 = 0,
    TRACTION_DRIVE_2 = 1,
    TRACTION_DRIVE_3 = 2
};

//------------------------------------------------------------------------------
// Структура данных Тягового Привода
//------------------------------------------------------------------------------
struct traction_drive_t {

    /// Положение реверса
    int reverse_position;

    /// Сила тяги
    double traction_force;

    traction_drive_t()
        : reverse_position(0)
        , traction_force(0.0)
    {

    }
};

#endif // TRACTIONDRIVEDATA_H
