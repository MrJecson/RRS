#include    "traction-drive.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
TractionDrive::TractionDrive(QObject *parent)
    : trac_moment_Max(0),
      trac_power_Max(0),
      trac_omega_Nominal(0),
      reducer_coeff(0)
{
    std::fill(torque.begin(), torque.end(), 0);
}

//------------------------------------------------------------------------------
// Деструктор
//------------------------------------------------------------------------------
TractionDrive::~TractionDrive()
{

}

void TractionDrive::setWheelOmega(double omega)
{
    this->wheel_omega = omega;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionDrive::setTractionDriveData(const traction_drive_t &trac_drive)
{
    this->trac_drive = trac_drive;
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionDrive::preStep(state_vector_t &Y, double t)
{
    double M_trac_ref = hs_p(trac_drive.traction_force) * getTracTorqueLimit(wheel_omega * reducer_coeff);

    double M_edt_ref = 0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionDrive::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionDrive::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "trac_moment_Max", trac_moment_Max);
    cfg.getDouble(secName, "trac_power_Max", trac_power_Max);
    cfg.getDouble(secName, "trac_omega_Nominal", trac_omega_Nominal);
    cfg.getDouble(secName, "reducer", reducer_coeff);

    cfg.getDouble(secName, "recup_moment_Max", recup_moment_Max);
    cfg.getDouble(secName, "recup_power_Max", recup_power_Max);
    cfg.getDouble(secName, "recup_omega_Nominal", recup_omega_Nominal);
}

double TractionDrive::getTracTorqueLimit(double omega)
{
    double omg = qAbs(omega);

    if (omg <= trac_omega_Nominal)
        return trac_moment_Max;
    else
    {
        return trac_power_Max / omg;
    }
}

