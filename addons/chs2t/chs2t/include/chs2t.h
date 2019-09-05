//------------------------------------------------------------------------------
//
//      Магистральный пассажирский электровоз постоянного тока ЧС2т.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Николай Авилкин (avilkin.nick)
//
//      Дата: 21/08/2019
//
//------------------------------------------------------------------------------
#ifndef     CHS2T_H
#define     CHS2T_H

#include    "vehicle-api.h"
#include    "pantograph.h"
#include    "protective-device.h"
#include    "km-21kr2.h"
#include    "stepswitch.h"
#include    "pusk-rez.h"
#include    "engine.h"
#include    "registrator.h"
#include    "overload-relay.h"
#include    "dc-motor-compressor.h"
#include    "pressure-regulator.h"

enum
{
    NUM_PANTOGRAPHS = 2
};

/*!
 * \class
 * \brief Основной класс, описывающий весь электровоз
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class CHS2T : public Vehicle
{
public:

    /// Конструктор
    CHS2T();

    /// Деструктор
    ~CHS2T();

private:

    QString     vehicle_path;
    QString     pantograph_config;
    QString     gv_config;
    QString     puskrez_config;

    enum
    {
        NUM_PANTOGRAPHS = 2,
        WIRE_VOLTAGE = 3000
    };

    /// Механизм киловольтметра ТЭД
//    Oscillator  *gauge_KV_motors;

    /// Тяговый электродвигатель
    Engine *motor;

    /// Токоприемники
    std::array<Pantograph *, NUM_PANTOGRAPHS>    pantographs;

    /// Быстрый выключатель
    ProtectiveDevice *bistV;

    /// Пусковой резистор
    PuskRez *puskRez;

    /// Регистратор
    Registrator *reg;

    /// Контроллер машиниста
    Km21KR2 *km21KR2;

    /// Переключатель ступеней
    StepSwitch *stepSwitch;

    double tracForce_kN;

    /// Возврат защиты
    bool bv_return;

    /// Реле перегрузки ТЭД
    OverloadRelay *overload_relay;

    Reservoir *mainReservoir;

    PressureRegulator *pressReg;

    DCMotorCompressor *motor_compressor;

    Trigger     mk_tumbler;

    BrakeCrane *brakeCrane;

    /// Общая инициализация локомотива
    void initialization();

    /// Инициализация схемы управления тягой
    void initTractionControl();

    /// Шаг моделирования всех систем локомотива в целом
    void step(double t, double dt);

    /// Загрузка данных из конфигурационных файлов
    void loadConfig(QString cfg_path);

    void keyProcess();

    void registrate(double t, double dt);

    bool getHoldingCoilState() const;
};

#endif // CHS2T
