//------------------------------------------------------------------------------
//
//      Магистральный пассажирский электровоз переменного тока ЧС4т.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Николай Авилкин (avilkin.nick)
//
//      Дата: 16/06/2019
//
//------------------------------------------------------------------------------

#include "auto-transformer.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AutoTransformer::AutoTransformer(QObject* parent) : Device(parent)
//  , nPoz()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTransformer::setUin(double Uin)
{
    this->Uin = Uin;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double AutoTransformer::getUout()
{
    return Uout;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTransformer::ode_system(const state_vector_t& Y, state_vector_t& dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTransformer::load_config(CfgReader& cfg)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTransformer::preStep(state_vector_t& Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTransformer::stepKeysControl(double t, double dt)
{
    Uout = Uin / 32.0 * nPoz;
}
