//-----------------------------------------------------------------------------
//
//      Класс "Диагностика тренажёра"
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Диагностика тренажёра"
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#include "screen-diagnostic.h"

#include "simple-tab-control.h"
#include "simple-tab.h"

#include <QLabel>

#include "display-shared-structures.h"
//#include "structures-display.h"


namespace
{
    constexpr quint8 RESET_LIFETIME = 6;

    const QStringList tabNames{"traction_controller", "brake_controller",
                               "panel_g", "panel_i", "panel_j_in",
                               "panel_j_out", "panel_k", "panel_l", "panel_m",
                               "light_blok", "manometer_tpm",
                               "manometer_tc12"};

    auto nextName = []()
    {
        static int index = 0;
        return index < tabNames.count()? tabNames[index++] : QString("");
    };
}


//-----------------------------------------------------------------------------
// Конструктор
//-----------------------------------------------------------------------------
ScreenDiagnostic::ScreenDiagnostic(QString scrName, QRect scrGeo,
                                   QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
    , tabControl_(Q_NULLPTR)
    , labelModelTime_(Q_NULLPTR)
    , resetManometerTMPM_(0)
    , resetManometerTC12_(0)
{
    this->setVisible(false);
    this->setPalette({Qt::black});

    buttonsNames_[1] = "Вывод\nлога";
    buttonsNames_[9] = "Основн.\nэкран";

    createAllChildren_();
}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
ScreenDiagnostic::~ScreenDiagnostic()
{

}



//-----------------------------------------------------------------------------
// Получить флаг сброса манометра ТМ/ПМ
//-----------------------------------------------------------------------------
bool ScreenDiagnostic::getResetManometerTMPM()
{
    if (resetManometerTMPM_ > 0)
    {
        --resetManometerTMPM_;
        return true;
    }

    return false;
}



//-----------------------------------------------------------------------------
// Получить флаг сброса манометра ТЦ1/ТЦ2
//-----------------------------------------------------------------------------
bool ScreenDiagnostic::getResetManometerTC12()
{
    if (resetManometerTC12_ > 0)
    {
        --resetManometerTC12_;
        return true;
    }

    return false;
}



//-----------------------------------------------------------------------------
// Обработка нажатия кнопки
//-----------------------------------------------------------------------------
void ScreenDiagnostic::receiveOtherButton(Local::ButtonId id)
{
    switch (id)
    {

    case Local::biLEFT:
        tabControl_->goPrevTab();
        break;

    case Local::biRIGHT:
        tabControl_->goNextTab();
        break;

    case Local::biCORRECTION:
        if (tabControl_->getCurrentTabName() == "Манометр ТМ/ПМ")
            resetManometerTMPM_ = RESET_LIFETIME;
        else if (tabControl_->getCurrentTabName() == "Манометр ТЦ1/ТЦ2")
            resetManometerTC12_ = RESET_LIFETIME;
        break;

    default:
        break;
    }
}



//-----------------------------------------------------------------------------
// Обновить данные экрана
//-----------------------------------------------------------------------------
void ScreenDiagnostic::updateScreen(screen_data_t *data)
{
    diagnostic_screen_t* ds = static_cast<diagnostic_screen_t*>(data);

    tabControl_->updateTab(tabNames[0],  &ds->traction_controller);
    tabControl_->updateTab(tabNames[1],  &ds->brake_controller);
    tabControl_->updateTab(tabNames[2],  &ds->panel_g);
    tabControl_->updateTab(tabNames[3],  &ds->panel_i);
    tabControl_->updateTab(tabNames[4],  &ds->panel_j_in);
    tabControl_->updateTab(tabNames[5],  &ds->panel_j_out);
    tabControl_->updateTab(tabNames[6],  &ds->panel_k);
    tabControl_->updateTab(tabNames[7],  &ds->panel_l);
    tabControl_->updateTab(tabNames[8],  &ds->panel_m);
    tabControl_->updateTab(tabNames[9],  &ds->traffic_light);
    tabControl_->updateTab(tabNames[10], &ds->manometer_tpm);
    tabControl_->updateTab(tabNames[11], &ds->manometer_tc12);

    labelModelTime_->setText("Модельное время: " +
                             QString::number(ds->modelTime, 'f', 2));
    labelModelTime_->adjustSize();
}



//-----------------------------------------------------------------------------
// Создать все дочерние виджеты
//-----------------------------------------------------------------------------
void ScreenDiagnostic::createAllChildren_()
{
    tabControl_ = new SimpleTabControl(this);

    SimpleTab* tab = Q_NULLPTR;


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Контроллер тяги/торможения", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Положение в процентах:", SimpleTab::ftFIELD_INT},
                    {"Число импульсов энкодера:", SimpleTab::ftFIELD_INT},
                    {"Экстренное торможение:", SimpleTab::ftBOX},
                    {"Пропорциональное торможение:", SimpleTab::ftBOX},
                    {"Нулевая позиция:", SimpleTab::ftBOX},
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Пневм. тормозной кран", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Позиция крана:", SimpleTab::ftFIELD_UINT},
                    {"Число импульсов энкодера:", SimpleTab::ftFIELD_UINT},
                    {"Позиция отпуска:", SimpleTab::ftBOX},
                    {"Экстренное торможение:", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель G", this);

    tab->addElementsList({
                    {"Связь по modbus: ", SimpleTab::ftBOX},
                    {"Готов: ", SimpleTab::ftBOX},
                    {"Расцепка: ", SimpleTab::ftBOX},
                    {"Буферные фонари 1: ", SimpleTab::ftBOX},
                    {"Буферные фонари 2: ", SimpleTab::ftBOX},
                    {"Нейтральная вставка: ", SimpleTab::ftBOX},
                    {"Отключение батареи: ", SimpleTab::ftBOX},
                    {"Выбор кабины: ", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель I", this);

    tab->addElementsList({
                    {"Связь по modbus: ", SimpleTab::ftBOX},
                    {"Готов: ", SimpleTab::ftBOX},
                    {"Рукоятка бдительности: ", SimpleTab::ftBOX},
                    {"Свисток: ", SimpleTab::ftBOX},
                    {"Тифон: ", SimpleTab::ftBOX},
                    {"Ответ пассажиру: ", SimpleTab::ftBOX},
                    {"Принять/завершить вызов: ", SimpleTab::ftBOX},
                    {"Оповещение: ", SimpleTab::ftBOX},
                    {"Межкабинная связь: ", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель J входы", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Отпустить стояночный тормоз:", SimpleTab::ftBOX},
                    {"Зажать стояночный тормоз:", SimpleTab::ftBOX},
                    {"Разблокировать двери справа:", SimpleTab::ftBOX},
                    {"Разблокировать двери слева:", SimpleTab::ftBOX},
                    {"Закрыть двери:", SimpleTab::ftBOX},
                    {"Высокая платформа:", SimpleTab::ftBOX},
                    {"Низкая платформа:", SimpleTab::ftBOX},
                    {"Обогрев ниши машиниста:", SimpleTab::ftBOX},
                    {"Обогрев ниши помощника:", SimpleTab::ftBOX},
                    {"Аварийное откл. клим. установки:", SimpleTab::ftBOX},
                    {"Экстренная остановка поезда:", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель J выходы", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //
    tab = new SimpleTab("Панель K", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Поднять токоприёмник:", SimpleTab::ftBOX},
                    {"Опустить токоприёмник:", SimpleTab::ftBOX},
                    {"Влючить ГВ/БВ:", SimpleTab::ftBOX},
                    {"Отключить ГВ/БВ:", SimpleTab::ftBOX},
                    {"Реверсор вперёд:", SimpleTab::ftBOX},
                    {"Реверсор назад:", SimpleTab::ftBOX},
                    {"Снятие блокировки движения", SimpleTab::ftBOX},
                    {"Направление реверсора:", SimpleTab::ftFIELD_INT},
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель L", this);

    tab->addElementsList({
                    {"Связь по modbus: ", SimpleTab::ftBOX},
                    {"Готов: ", SimpleTab::ftBOX},
                    {"Очистка торм. диска: ", SimpleTab::ftBOX},
                    {"Шунтирование экстр. торм.: ", SimpleTab::ftBOX},
                    {"Проверка индикаторов: ", SimpleTab::ftBOX},
                    {"Осв. кабины тускл: ", SimpleTab::ftBOX},
                    {"Осв. кабины ярко: ", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Панель M", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Свисток:", SimpleTab::ftBOX},
                    {"Тифон:", SimpleTab::ftBOX},
                    {"Прожектор тускло:", SimpleTab::ftBOX},
                    {"Прожектор ярко:", SimpleTab::ftBOX},
                    {"Кнопка бдительности:", SimpleTab::ftBOX},
                    {"Очиститель стекла: ",SimpleTab::ftBOX},
                    {"Скорость1 очистителя: ",SimpleTab::ftBOX},
                    {"Скорость3 очистителя: ",SimpleTab::ftBOX},
                    {"Режим1 очистителя: ",SimpleTab::ftBOX},
                    {"Режим3 очистителя: ",SimpleTab::ftBOX},
                    {"Обогрев стекла: ",SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Локомотивный светофор БЛОК", this);

    tab->addElementsList({
                    {"Связь по modbus: ", SimpleTab::ftBOX},
                    {"Готов: ", SimpleTab::ftBOX}
                         });

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Манометр ТМ/ПМ", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Число шагов ШД ТМ:", SimpleTab::ftFIELD_UINT},
                    {"Число шагов ШД ПМ:", SimpleTab::ftFIELD_UINT}
                         });

    tab->addFooter("Нажмите кнопку \"C\" для сброса манометра.");

    tabControl_->addTab(std::move(tab), nextName());


    //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    tab = new SimpleTab("Манометр ТЦ1/ТЦ2", this);

    tab->addElementsList({
                    {"Связь по modbus:", SimpleTab::ftBOX},
                    {"Готов:", SimpleTab::ftBOX},
                    {"Число шагов ШД ТЦ1:", SimpleTab::ftFIELD_UINT},
                    {"Число шагов ШД ТЦ2:", SimpleTab::ftFIELD_UINT}
                         });

    tab->addFooter("Нажмите кнопку \"C\" для сброса манометра.");

    tabControl_->addTab(std::move(tab), nextName());


    labelModelTime_ = new QLabel("Модельное время: 0.00", this);
    labelModelTime_->adjustSize();
    labelModelTime_->move((this->width() - labelModelTime_->width())/2, 27);
}
