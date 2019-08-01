//------------------------------------------------------------------------------
//
//      Двухсистемный пассажирский электровоз с асинхронным тяговым приводом ЭП20.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Роман Бирюков (РомычРЖДУЗ)
//
//      Дата: 12/05/2019
//
//------------------------------------------------------------------------------
#ifndef     EP20_H
#define     EP20_H

#include    "vehicle-api.h"
#include    "pantograph.h"

/*!
 * \class
 * \brief Основной класс, описывающий весь тепловоз
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class EP20 : public Vehicle
{
public:

    /// Конструктор
    EP20();

    /// Деструктор
    ~EP20();

private:

    /// Нумеротор токоприемников (АС - переменный, DC - постоянный)
    enum
    {
        NUM_PANTOGRAPHS = 4,
        PANT_AC1 = 0,
        PANT_DC1 = 1,
        PANT_AC2 = 2,
        PANT_DC2 = 3
    };

    /// Массив токоприемников
    std::array<Pantograph *, NUM_PANTOGRAPHS> pantograph;

    /// Инициализация
    void initialization();

    /// Инициализация высоковольтной схемы
    void initHighVoltageScheme();

    /// Шаг моделирования всех систем локомотива в целом
    void step(double t, double dt);

    /// Шаг моделирования высоковольтной схемы
    void stepHighVoltageScheme(double t, double dt);

    /// Загрузка данных из конфигурационных файлов
    void loadConfig(QString cfg_path);

    void keyProcess();
};

#endif // EP20_H

