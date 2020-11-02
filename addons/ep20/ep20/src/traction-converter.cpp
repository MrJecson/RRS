#include    "traction-converter.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
TractionConverter::TractionConverter(QObject *parent) : Device (parent)
  ,Udc_in(0)
  ,K4QS(1.808)
{
    std::fill(Ut.begin(), Ut.end(), 0);
    std::fill(U4QS.begin(), U4QS.end(), 0);
    std::fill(Udc.begin(), Udc.end(), 0);
    std::fill(U4.begin(), U4.end(), 0);
}

//------------------------------------------------------------------------------
// Деструктор
//------------------------------------------------------------------------------
TractionConverter::~TractionConverter()
{

}

//------------------------------------------------------------------------------
// Установить напряжение с тяговых обмоток
//------------------------------------------------------------------------------
void TractionConverter::setUt(double Ut, size_t i)
{
    if (i < this->Ut.size())
        this->Ut[i] = Ut;
}

//------------------------------------------------------------------------------
// Установить напряжение постоянного тока
//------------------------------------------------------------------------------
void TractionConverter::setUdcIn(double Udc_in)
{
    this->Udc_in = Udc_in;
}

//------------------------------------------------------------------------------
// Получить напряжение ПСН
//------------------------------------------------------------------------------
double TractionConverter::getU4(size_t i)
{
    if (i < U4.size())
        return U4[i];
    else
        return 0;
}

double TractionConverter::getVoltState() const
{
    if (Udc_in != 0)
        return voltage == true;
    else
        return voltage == false;
}



//------------------------------------------------------------------------------
// Предварительные шаги
//------------------------------------------------------------------------------
void TractionConverter::preStep(state_vector_t &Y, double t)
{

    for (size_t i = 0; i < U4QS.size(); ++i)
    {
        U4QS[i] = K4QS * Ut[i];
        Udc[i] = max(U4QS[i], Udc_in);
        U4[i] = Udc[i];   
    }


}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionConverter::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void TractionConverter::load_config(CfgReader &cfg)
{

}
