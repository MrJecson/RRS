#include    "vehicle.h"

#include    "CfgReader.h"
#include    "physics.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Vehicle::Vehicle(QObject *parent) : QObject(parent)
  , idx(0)
  , empty_mass(24000.0)
  , payload_mass(68000.0)
  , payload_coeff(0.0)
  , full_mass(empty_mass + payload_mass * payload_coeff)
  , length(14.7)
  , num_axis(4)
  , J_axis(2.0)
  , wheel_diameter(0.95)
  , R1(0.0)
  , R2(0.0)
  , s(5)
  , b0(0.0)
  , b1(0.0)
  , b2(0.0)
  , b3(0.0)
  , q0(24.0)
  , inc(0.0)
  , curv(0.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Vehicle::~Vehicle()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setIndex(int idx)
{
    this->idx = idx;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setInclination(double inc)
{
    this->inc = inc;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setCurvature(double curv)
{
    this->curv = curv;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setForwardForce(double R1)
{
    this->R1 = R1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setBackwardForce(double R2)
{
    this->R2 = R2;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setActiveCommonForce(int idx, double value)
{
    if (static_cast<size_t>(idx) < Q_a.size())
        Q_a[idx] = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setReactiveCommonForce(int idx, double value)
{
    if (static_cast<size_t>(idx) < Q_r.size())
        Q_r[idx] = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::setPayloadCoeff(double payload_coeff)
{
    this->payload_coeff = Physics::cut(payload_coeff, 0.0, 1.0);
    full_mass = empty_mass + payload_mass * this->payload_coeff;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::step(double t, double dt)
{
    (void) t;
    (void) dt;

    // This code may be overrided in child class
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::loadConfig(QString cfg_path)
{
    (void) cfg_path;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Vehicle::loadConfiguration(QString cfg_path)
{
    loadConfig(cfg_path);
}
