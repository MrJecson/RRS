#ifndef TRACTIONDRIVE_H
#define TRACTIONDRIVE_H

#include    "device.h"
#include    "traction-drive-data.h"

//------------------------------------------------------------------------------
// Тяговый двигатель
//------------------------------------------------------------------------------
class TractionDrive : public Device
{

public:

    TractionDrive(QObject *parent = Q_NULLPTR);

    ~TractionDrive();

    /// Установить положение реверса
    void setRevPos(const traction_drive_t &rev_pos);

    /// Установить силу тяги
    void setTracForce(const traction_drive_t &trac_force);

    /// Получить крутящий момент
    double getTorque(size_t i);

private:

    /// Входные данные тягового привода
    traction_drive_t trac_drive;

    /// Момент максимальный
    double  moment_Max;

    /// Мощность максимальная
    double  power_Max;

    /// Омега номинальная
    double  omega_Nominal;

    /// Редуктор
    double  reducer;

    /// Массив крутящих моментов
    std::array<double, 2> torque;

    /// Предварительный шаг
    void preStep(state_vector_t &Y, double t);

    /// Вычисление напряжения
    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    /// Загрузка конфига
    void load_config(CfgReader &cfg);
};

#endif // TRACTIONDRIVE_H
