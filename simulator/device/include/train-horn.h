#ifndef     TRAIN_HORN_H
#define     TRAIN_HORN_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class DEVICE_EXPORT TrainHorn : public Device
{
public:

    TrainHorn(QObject *parent = Q_NULLPTR);

    virtual ~TrainHorn();

    bool isSvistok() const { return is_svistok; }

    bool isTifon() const { return is_tifon; }

protected:

    bool is_svistok;

    bool is_tifon;

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);

    void stepKeysControl(double t, double dt);
};

#endif // TRAIN_HORN_H
