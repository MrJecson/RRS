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

    /// Установить угловую скорость
    void setWheelOmega(double omega);

    /// Установить данные для тягового привода
    void setTractionDriveData(const traction_drive_t &trac_drive);

    /// Установить напряжение с Тягового Преобразователя
    double setVoltTracConv(double volt);

    /// Получить крутящий момент
    double getTorque(size_t i);


private:

    /// Входные данные тягового привода
    traction_drive_t trac_drive;

    /// Момент максимальный (тяговая характеристика)
    double  trac_moment_Max;
    /// Мощность максимальная (тяговая характеристика)
    double  trac_power_Max;
    /// Омега номинальная (тяговая характеристика)
    double  trac_omega_Nominal;
    /// Редуктор (тяговая характеристика)
    double  reducer_coeff;

    /// Момент максимальный (рекуперативная характеристика)
    double recup_moment_Max;
    /// Мощность максимальная (рекуперативная характеристика)
    double recup_power_Max;
    /// Омега номинальная (рекуперативная характеристика)
    double recup_omega_Nominal;

    /// Угловая скорость
    double wheel_omega;

    /// Массив крутящих моментов
    std::array<double, 2> torque;

    /// Момент тяги (Относительный)
    double m_trac_ref;

    ///
    int K_i;

    ///
    double T_i;

    ///
    double volt_trac_conv;

    /// Предварительный шаг
    void preStep(state_vector_t &Y, double t);

    /// Вычисление напряжения
    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    /// Загрузка конфига
    void load_config(CfgReader &cfg);

    /// Вычисление максимального тягового момента
    double getTracTorqueLimit(double omega);

    /// Вычисление максимального тормозного усилия
    double getBrakingForceLimit(double omega_recup);

};

#endif // TRACTIONDRIVE_H
