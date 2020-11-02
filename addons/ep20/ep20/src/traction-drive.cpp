#include    "traction-drive.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
TractionDrive::TractionDrive(QObject *parent)
    : trac_moment_Max(0),
      trac_power_Max(0),
      trac_omega_Nominal(0),
      reducer_coeff(0),
      recup_moment_Max(0),
      recup_power_Max(0),
      recup_omega_Nominal(0),
      wheel_omega(0),
      m_trac_ref(0),
      K_i(1),
      T_i(1.5),
      volt_trac_conv(0),
      U_nom(2200.0),
      plug(0),
      variable_x(0),
      motor_max_torque(116.7e3)
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

double TractionDrive::setVoltTracConv(double volt)
{
    this->volt_trac_conv = volt;
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
    if (volt_trac_conv > U_nom)
    {
        plug = 1;

//        double M_edt_ref = 0;
//        double F_brakes_ref = hs_p(trac_drive.traction_force) * getBrakingForceLimit(wheel_omega * reducer_coeff);

//        motor_max_torque = getTracTorqueLimit(wheel_omega * reducer_coeff);

        double M_edt_ref = 0;

        m_trac_ref = pf(trac_drive.traction_force) * getTracTorqueLimit(wheel_omega * reducer_coeff);

        variable_x = m_trac_ref * plug;

        torque[0] = torque[1] = Y[0] * reducer_coeff;
    }
    //    torque[0] = torque[1] = M_trac_ref * reducer_coeff;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionDrive::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    dYdt[0] = (K_i * variable_x - Y[0])/T_i;
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
        return trac_power_Max * 1000.0 / omg;
    }
}

double TractionDrive::getBrakingForceLimit(double omega_recup)
{
    double omg_recup = qAbs(omega_recup);

    if (omg_recup <= recup_omega_Nominal)
        return recup_moment_Max * sign(omega_recup);
    else
    {
        return recup_power_Max * 1000.0 * sign(omega_recup) / omg_recup;
    }
}
