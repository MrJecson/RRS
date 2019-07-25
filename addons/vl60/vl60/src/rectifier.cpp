#include    "rectifier.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Rectifier::Rectifier(QObject *parent) : Device(parent)
  , coeff(1.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Rectifier::~Rectifier()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Rectifier::setU_in(double value)
{
    U_in = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Rectifier::getU_out() const
{
    return U_out;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Rectifier::preStep(state_vector_t &Y, double t)
{
    U_out = coeff * U_in;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Rectifier::ode_system(const state_vector_t &Y,
                           state_vector_t &dYdt,
                           double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Rectifier::load_config(CfgReader &cfg)
{
    cfg.getDouble("Device", "Coeff", coeff);
}
