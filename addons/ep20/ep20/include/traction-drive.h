#ifndef TRACTIONDRIVE_H
#define TRACTIONDRIVE_H

#include    "device.h"

struct set_reverse_position {

    int reverse_position;
};

struct set_traction_force {

    int traction_force;
};

//------------------------------------------------------------------------------
// Тяговый двигатель
//------------------------------------------------------------------------------
class TractionDrive : public Device
{

public:

    TractionDrive(QObject *parent = Q_NULLPTR);

    ~TractionDrive();



    /// Получить крутящий момент
    double getTorque(size_t i);

private:

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
