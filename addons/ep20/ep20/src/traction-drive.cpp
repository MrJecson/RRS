#include    "traction-drive.h"

TractionDrive::TractionDrive(QObject *parent)
{

}

TractionDrive::~TractionDrive()
{

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

