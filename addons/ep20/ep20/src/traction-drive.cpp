#include    "traction-drive.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
TractionDrive::TractionDrive(QObject *parent)
    : moment_Max(0),
      power_Max(0),
      omega_Nominal(0),
      reducer(0)
{
    std::fill(torque.begin(), torque.end(), 0);
}

//------------------------------------------------------------------------------
// Деструктор
//------------------------------------------------------------------------------
TractionDrive::~TractionDrive()
{

}

//------------------------------------------------------------------------------
// Получить крутящий момент
//------------------------------------------------------------------------------
double TractionDrive::getTorque(size_t i)
{
    if (i < torque.size())
        return torque[i];
    else
        return 0;
}

void TractionDrive::preStep(state_vector_t &Y, double t)
{

}

void TractionDrive::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

void TractionDrive::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "moment_Max", moment_Max);
    cfg.getDouble(secName, "power_Max", power_Max);
    cfg.getDouble(secName, "omega_Nominal", omega_Nominal);
    cfg.getDouble(secName, "reducer", reducer);
}

