#include    "msut.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MSUT::MSUT(QObject *parent) : Device(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MSUT::~MSUT()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MSUT::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MSUT::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MSUT::load_config(CfgReader &cfg)
{

}
