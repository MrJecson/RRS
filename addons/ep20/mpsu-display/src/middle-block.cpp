//-----------------------------------------------------------------------------
//
//      Класс центрального блока
//      (c) РГУПС, ВЖД 03/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс центрального блока
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 03/03/2017
 */
#include "middle-block.h"
//#include "display-shared-structures.h"
#include "structures-display.h"
#include "CfgReader.h"

#include "simple-plot-old.h"
#include "soft-buttons-block.h"
#include "condition-line-block.h"
#include "status-bar-block.h"
#include "status-bar-block-bottom.h"
#include "screen-connection-error.h"
#include "screen-main.h"
#include "screen-diagnostics.h"
#include "screen-power-circuit.h"
#include "screen-pneumatics.h"
#include "screen-diagnostic.h"
#include "screen-log.h"


const QStringList vehicles1 = {"00301", "00302", "00303", "00304", "00305"};
const QStringList vehicles2 = {"07001", "07002", "07003", "07004", "07005"};


//-----------------------------------------------------------------------------
// КОНСТРУКТОР
//-----------------------------------------------------------------------------
MiddleBlock::MiddleBlock(const QString &config_dir, const QString &configFileName, QRect geo, QWidget *parent)
    : QWidget(parent)
    , screenIsEnabled_(true)
    //, currentTree_(SC_MAIN)
    , currentTreeHead_(Q_NULLPTR)
{
    CfgReader cfg;
    this->setGeometry(geo);
    this->setMinimumSize(geo.size());
    this->setMaximumSize(geo.size());
    this->setAutoFillBackground(true);
    if (cfg.load(config_dir + "display-core.xml"))
    {
        cfg.getString("MainWindow", "OffScreenColor", colorHexName_);
        this->setPalette(QPalette(QColor(colorHexName_)));
    }
    else
    {
        this->setPalette(QPalette(QColor(100,100,100)));
    }



// СОЗДАЁМ И НАСТРАИВАЕМ "ОСНОВНОЙ ЭКРАН"
    scrnMain_ = new ScreenMain(config_dir, "основной экран",
                               SCRNS_GEO_,
                               this);

    scrnDiagnostics_ = new ScreenDiagnostics("диагностика",
                                             SCRNS_GEO_,
                                             this);

    scrnPowerCircuit_ = new ScreenPowerCircuit("Силовая схема",
                                               SCRNS_GEO_,
                                               this);

    scrnPneumatics_ = new ScreenPneumatics("Пневматика (КТО)",
                                           SCRNS_GEO_,
                                           this);


// СОЗДАЕМ И НАСТРАИВАЕМ "ДИАГНОСТИКА ТРЕНАЖЁРА"
    scrnDiagnostic_ = new ScreenDiagnostic("Диагностика тренажёра",
                                           SCRNS_GEO_,
                                           this);

    scrnLog_ = new ScreenLog("Экран вывода лог-файла",
                             SCRNS_GEO_,
                             this);



    // Создаём блок программируемых клавиш (верхняя строка)
//    softButtonsBlockTop_ = new SoftButtonsBlock(QColor(Qt::red)/*SOFT_BLOCK_COLOR_*/,
//                                                SOFT_BLOCK_TOP_GEO_,
//                                                this);

    // Создаём блок строки состояния (верхняя строка)
    statusBarBlock_ = new StatusBarBlock(STATUS_BAR_COLOR_,
                                         STATUS_BAR_GEO_,
                                         this);

    // Создаём блок статусной строки кадра (нижняя строка)
    statusBarBlockBottom_ = new StatusBarBlockBottom(STATUS_BAR_BOTTOM_COLOR_,
                                                     STATUS_BAR_BOTTOM_GEO_,
                                                     this);

//    // Создаём блок информационной строки (нижняя строка)
//    conditionLineBlock_ = new ConditionLineBlock(CONDITION_LINE_COLOR_,
//                                                 CONDITION_LINE_GEO_,
//                                                 this);

    // Создаём блок программируемых клавиш (нижняя строка)
    softButtonsBlock_ = new SoftButtonsBlock(SOFT_BLOCK_COLOR_,
                                             SOFT_BLOCK_GEO_,
                                             this);



    //
    mapNewScreen("ScreenMain",          scrnMain_);
    mapNewScreen("ScreenDiagnostics",   scrnDiagnostics_);
    mapNewScreen("ScreenPowerCircuit",  scrnPowerCircuit_);
    mapNewScreen("ScreenPneumatics",    scrnPneumatics_);
    mapNewScreen("DiagnosticScreen",    scrnDiagnostic_);
    mapNewScreen("ScreenLog",           scrnLog_);

    // Устанавливаем текущий экран
    currentScreen_ = loadTreeHeadFromCfg(configFileName);
    currentScreen_ = mapScreens_.value("ScreenMain", Q_NULLPTR);        // zБогос - удалить!
    currentTreeHead_ = currentScreen_;

    softButtonsBlock_->setButtonsNames(currentScreen_->getButtonsNames(),
                                       currentScreen_->getButtonSelectedIdx());
    currentScreen_->setVisible(true);


// Добавляем для каждого экрана указатели на доступные экраны
    // Главное дерево экранов
    scrnMain_->setScreens({ {Local::biDIGIT3, scrnDiagnostics_},
                            {Local::biDIGIT0, scrnDiagnostic_} });

    scrnDiagnostics_->setScreens({ {Local::biF1, scrnPneumatics_},
                                   {Local::biF3, scrnPowerCircuit_},
                                   {Local::biDIGIT1, scrnMain_} });

    scrnPowerCircuit_->setScreens({ {Local::biOTM, scrnDiagnostics_} });

    scrnPneumatics_->setScreens({ {Local::biOTM, scrnDiagnostics_} });

    scrnDiagnostic_->setScreens({ {Local::biDIGIT2, scrnLog_},
                                  {Local::biDIGIT0, scrnMain_} });

    scrnLog_->setScreens({ {Local::biDIGIT1, scrnDiagnostic_},
                           {Local::biDIGIT0, scrnMain_} });


    // Экран нарушения связи
    scrnConnectionError_ = new ScreenConnectionError(this);
    scrnConnectionError_->disable(); // zБогос - удалить!!


    // ---------------------
    // --- удалить!! -----
    display_data_t all_data;

    screen_main_t* sm = &all_data.screen_main;

    sm->sCurSpeed = 60;
    sm->sCurSpeedLimit = 120;
    sm->sNextSpeedLimit = 100;
    sm->sSetpointSpeed = 80;
    sm->sTrainPos = 125678.7;

    sm->scaleSetTraction = 75;
    sm->scaleActualTraction = 50;

    sm->controlVoltage = 2;

    sm->outputI = 0.2;
    sm->outputU = 3;

    sm->ltct.stateGVBV = false;
    sm->ltct.currentType = CurrentTypeEnum::AC;
    sm->ltct.pantograph[0].num = PantographNumEnum::forward;
    sm->ltct.pantograph[0].ready = true;
    sm->ltct.pantograph[0].active = false;
    sm->ltct.pantograph[1].num = PantographNumEnum::backward;
    sm->ltct.pantograph[1].ready = false;
    sm->ltct.pantograph[1].active = false;
    sm->ltct.stateTC[0] = stateWorkTC::norm;
    sm->ltct.stateTC[1] = stateWorkTC::chanelOutage;
    sm->ltct.stateTC[2] = stateWorkTC::norm;
    sm->ltct.stateMotor[0] = true;
    sm->ltct.stateMotor[1] = true;
    sm->ltct.stateMotor[2] = true;
    sm->ltct.stateMotor[3] = false;
    sm->ltct.stateMotor[4] = true;
    sm->ltct.stateMotor[5] = false;
    sm->ltct.motorVal[0] = 1;
    sm->ltct.motorVal[1] = 1;
    sm->ltct.motorVal[2] = 1;
    sm->ltct.motorVal[3] = 2;
    sm->ltct.motorVal[4] = 2;
    sm->ltct.motorVal[5] = 2;

    sm->numSwitch = NumIndicatorSwitchPosEnum::release;

    sm->motorCompressor1 = MotorCompressorEnum::isolated;
    sm->motorCompressor2 = MotorCompressorEnum::on;

    sm->pressureAST = 0.5;

    scrnMain_->updateScreen(sm);


    // ---------



    screen_diagnostics_t* sdt = &all_data.screen_diagnostics;

    sdt->pantograph[0].ready = true;
    sdt->pantograph[0].active = false;
    sdt->pantograph[1].ready = false;
    sdt->pantograph[1].active = false;
    sdt->pantograph[2].ready = true;
    sdt->pantograph[2].active = true;
    sdt->pantograph[3].ready = false;
    sdt->pantograph[3].active = false;

    sdt->deviceBTR[0] = ColorDeviceEnum::gray;
    sdt->deviceBTR[1] = ColorDeviceEnum::gray;
    sdt->deviceBTR[2] = ColorDeviceEnum::gray;
    sdt->deviceBTR[3] = ColorDeviceEnum::gray;
    sdt->deviceBTR[4] = ColorDeviceEnum::gray;
    sdt->deviceBTR[5] = ColorDeviceEnum::gray;
    sdt->deviceCab1 = ColorDeviceEnum::green;
    sdt->deviceCab2 = ColorDeviceEnum::gray;
    sdt->deviceBUGS = ColorDeviceEnum::red;
    sdt->deviceTPr1 = ColorDeviceEnum::gray;
    sdt->deviceTPr2 = ColorDeviceEnum::gray;
    sdt->deviceTPr3 = ColorDeviceEnum::gray;
    sdt->deviceBUE = ColorDeviceEnum::green;
    sdt->deviceBARS = ColorDeviceEnum::red;
    sdt->deviceMK1 = ColorDeviceEnum::gray;
    sdt->deviceMK2 = ColorDeviceEnum::gray;
    sdt->deviceBD = ColorDeviceEnum::gray;
    sdt->deviceAB = ColorDeviceEnum::gray;
    sdt->deviceVPr = ColorDeviceEnum::gray;
    sdt->deviceIPCU = ColorDeviceEnum::red;
    sdt->deviceTTr = ColorDeviceEnum::gray;
    sdt->deviceKTO = ColorDeviceEnum::red;

    sdt->fanMV11.state = FanStateEnum::fsOn;
    sdt->fanMV11.speed = 5;
    sdt->fanMV12.state = FanStateEnum::fsOff;
    sdt->fanMV12.speed = 0;
    sdt->fanMV13.state = FanStateEnum::fsOn;
    sdt->fanMV13.speed = 10;
    sdt->fanMV14.state = FanStateEnum::fsOff;
    sdt->fanMV14.speed = 0;
    sdt->fanMV15.state = FanStateEnum::fsOn;
    sdt->fanMV15.speed = 15;
    sdt->fanMV16.state = FanStateEnum::fsOff;
    sdt->fanMV16.speed = 0;

    sdt->fanMV21.state = FanStateEnum::fsDefect;
    sdt->fanMV21.speed = 0;
    sdt->fanMV22.state = FanStateEnum::fsOff;
    sdt->fanMV22.speed = 0;
    sdt->fanMV23.state = FanStateEnum::fsOff;
    sdt->fanMV23.speed = 0;

    sdt->fanMV31.state = FanStateEnum::fsDefect;
    sdt->fanMV31.speed = 0;
    sdt->fanMV32.state = FanStateEnum::fsOn;
    sdt->fanMV32.speed = 5;

    scrnDiagnostics_->updateScreen(sdt);



    // ---------


    screen_power_circuit_t* spc = &all_data.screen_power_circuit;

    spc->I = 0.1;
    spc->U = 0.2;
    spc->pantograph[0].ready = true;
    spc->pantograph[0].active = false;
    spc->pantograph[1].ready = false;
    spc->pantograph[1].active = false;
    spc->pantograph[2].ready = true;
    spc->pantograph[2].active = true;
    spc->pantograph[3].ready = false;
    spc->pantograph[3].active = false;
    spc->roofKeyQS1 = DisconnectorEnum::closed;
    spc->roofKeyQS2 = DisconnectorEnum::closed;
    spc->prt = DisconnectorEnum::closed;
    spc->depo = DisconnectorEnum::open;
    spc->GV = KeyStateEnum::ks_closed;
    spc->BV = KeyStateEnum::ks_open;
    spc->groundingGV = true;

    scrnPowerCircuit_->updateScreen(spc);


    // ---------


    screen_pneumatics_t* spt = &all_data.screen_pneumatics;

    spt->UR = 0.0;
    spt->DD = 0.0;
    spt->DD1_BTO = 0.0;
    spt->DD2_BTO = 0.0;
    spt->DD3_BTO = 0.0;
    spt->DD4_BTO = 0.0;
    spt->DD5_BTO = 0.0;
    spt->DD6_BTO = 0.0;
    spt->DD1_BIO = 0.0;
    spt->DD2_BIO = 0.0;
    spt->DD3_BIO = 0.0;
    spt->DD4_BIO = 0.0;
    spt->DD5_BIO = 0.0;

    spt->motorCompressor1 = MotorCompressorEnum::off;
    spt->motorCompressor2 = MotorCompressorEnum::off;

    scrnPneumatics_->updateScreen(spt);


    // ---------


    status_bar_bottom_data_t* sbbd = &all_data.status_bar_bottom;
    sbbd->fanAngle = 0;
    sbbd->AST = true;
    sbbd->TC = false;
    strcpy(sbbd->curModelData, "01.02.03");
    strcpy(sbbd->curModelTime, "04.05.06");

    statusBarBlockBottom_->updateData(sbbd);
    // --- удалить!! -----
    // ---------------------
}



//-----------------------------------------------------------------------------
// ДЕСТРУКТОР
//-----------------------------------------------------------------------------
MiddleBlock::~MiddleBlock()
{

}



//-----------------------------------------------------------------------------
// Вернуть флаг сброса манометра ТМ/ПМ
//-----------------------------------------------------------------------------
bool MiddleBlock::getResetManometerTMPM()
{
    return scrnDiagnostic_->getResetManometerTMPM();
}



//-----------------------------------------------------------------------------
// Вернуть флаг сброса манометра ТЦ1/ТЦ2
//-----------------------------------------------------------------------------
bool MiddleBlock::getResetManometerTC12()
{
    return scrnDiagnostic_->getResetManometerTC12();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void MiddleBlock::setAllData(display_data_t &all_data)
{
    AbstractScreen::setPowerType(all_data.powerType);

    statusBarBlock_->updateStatusBar(&all_data.status_bar);

    //conditionLineBlock_->updateLine(&all_data.condition_line);

    // -------------------------------------------------------

    scrnMain_->updateScreen(&all_data.screen_main);

    scrnDiagnostics_->updateScreen(&all_data.screen_diagnostics);

    scrnPowerCircuit_->updateScreen(&all_data.screen_power_circuit);

    scrnPneumatics_->updateScreen(&all_data.screen_pneumatics);

    scrnDiagnostic_->updateScreen(&all_data.diagnostic);

    scrnLog_->updateScreen(Q_NULLPTR);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void MiddleBlock::receiveAllData(QByteArray allArr)
{
    display_data_t all_data;
    all_data.fromByteArray(allArr);

    AbstractScreen::setPowerType(all_data.powerType);

    statusBarBlock_->updateStatusBar(&all_data.status_bar);

    //conditionLineBlock_->updateLine(&all_data.condition_line);

    // -------------------------------------------------------

    scrnMain_->updateScreen(&all_data.screen_main);

    scrnDiagnostics_->updateScreen(&all_data.screen_diagnostics);

    scrnPowerCircuit_->updateScreen(&all_data.screen_power_circuit);

    scrnPneumatics_->updateScreen(&all_data.screen_pneumatics);

    scrnDiagnostic_->updateScreen(&all_data.diagnostic);

    scrnLog_->updateScreen(Q_NULLPTR);
}



//-----------------------------------------------------------------------------
// Обработка нажатия кнопки
//-----------------------------------------------------------------------------
void MiddleBlock::receiveButtonPressed(Local::ButtonId id)
{
    /*if (id == Local::biCOPY) // zБогос. удалить
    {
        currentScreen_->hide();
        switch (currentTree_)
        {
        case SC_MAIN:
            //currentScreen_ = scrnBrakesStatus_;   // zzzzzzzzzzz
            currentTree_ = SC_BRAKES;
            break;

        default:
            currentScreen_ = scrnMain_;
            currentTree_ = SC_MAIN;
            break;
        }
        currentTreeHead_ = currentScreen_;
        currentScreen_->show();
        statusBarBlock_->recieveScreenName(currentScreen_->getScreenName());
        softButtonsBlock_->setButtonsNames(currentScreen_->getButtonsNames());
    }
    else */if (screenIsEnabled_ && !scrnConnectionError_->isEnabled())
    {
        // bool stolen = false;
        currentScreen_->receiveOtherButton(id/*, bool &stolen*/);
        // stolen - флаг того, что нажатие было перехвачено и не должно
        // передаваться в метод digitButton_()

        //if (/*!stolen &&*/ id < 10)
        {
            digitButton_(static_cast<int>(id));
        }

        softButtonsBlock_->setButtonsNames(currentScreen_->getButtonsNames(),
                                           currentScreen_->getButtonSelectedIdx());

        softButtonsBlockTop_->setButtonsNames(currentScreen_->getButtonsNamesTop(),
                                              -1,
                                              currentScreen_->getButtonsNamesHead(),
                                              currentScreen_->getButtonsNamesHeadNum(),
                                              currentScreen_->getButtonsNamesHeadCount());
    }
}



//-----------------------------------------------------------------------------
// Обработка разрыва связи с сервером
//-----------------------------------------------------------------------------
void MiddleBlock::onTcpDisconnectedFromServer()
{
    foreach (AbstractScreen* scr, listScreens_)
    {
        scr->resetOnDisconnect();
    }

    currentScreen_->doOnComeOut();

    currentScreen_->hide();

    currentScreen_ = currentTreeHead_;

    currentScreen_->show();

    softButtonsBlock_->setButtonsNames(currentScreen_->getButtonsNames());

    scrnConnectionError_->enable();
}



//-----------------------------------------------------------------------------
// Обработка восстановления связи с сервером
//-----------------------------------------------------------------------------
void MiddleBlock::onTcpConnectedToServer()
{
    scrnLog_->prepareLogScreen();

    scrnConnectionError_->disable();
}



//-----------------------------------------------------------------------------
// Определяем какой экран будет показан после запуска
//-----------------------------------------------------------------------------
AbstractScreen* MiddleBlock::loadTreeHeadFromCfg(const QString &configFileName)
{
    CfgReader cfg;
    AbstractScreen* defScreen = mapScreens_.value("ScreenMain", Q_NULLPTR);

    if (cfg.load(configFileName))
    {
        QString treeName("main");
        cfg.getString("Interface", "tree", treeName);
//        if (treeName == "brakes")
//        {
//            //defScreen = scrnBrakesStatus_;    //zzzzzzzzzzzz
//            currentTree_ = SC_BRAKES;
//        }
    }

    return defScreen;
}



//-----------------------------------------------------------------------------
// Обрабатываем нажание на кнопку с цифрой
//-----------------------------------------------------------------------------
void MiddleBlock::digitButton_(int num)
{
    if (currentScreen_->goToScreen(num, currentScreen_))
    {
        softButtonsBlock_->setButtonsNames(currentScreen_->getButtonsNames());

        //
        if (currentScreen_->getScreenName() == "основной экран")
            statusBarBlock_->setVisible(true);
        else
            statusBarBlock_->setVisible(false);
    }
}



//-----------------------------------------------------------------------------
// Добавить новый экран в списки
//-----------------------------------------------------------------------------
void MiddleBlock::mapNewScreen(QString scrnName, AbstractScreen *nScrn)
{

    mapScreens_.insert(scrnName, nScrn);

    listScreens_ << nScrn;
}
