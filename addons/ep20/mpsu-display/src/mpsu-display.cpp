#include    "mpsu-display.h"

#include    "ep20-signals.h"

#include    "CfgReader.h"
#include    <QVBoxLayout>
#include "display-shared-structures.h"

MpsuDisplay::MpsuDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f),
      MIDDLE_BLOCK_GEO(QPoint(0, 0), QSize(800, 588))//,
      //TOP_BLOCK_GEO(QPoint(112, 0), QSize(800, 90)),
      //LEFT_BLOCK_GEO(QPoint(0, 0), QSize(112, 768)),
      //RIGHT_BLOCK_GEO(QPoint(912, 0), QSize(112, 768)),
      //BOTTOM_BLOCK_GEO(QPoint(112, 678), QSize(800, 90))
{

    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(820, 605); // 800, 588
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));

    this->setLayout(new QVBoxLayout);
    this-> setFocusPolicy(Qt::FocusPolicy::NoFocus);
}

MpsuDisplay::~MpsuDisplay()
{

}

void MpsuDisplay::init()
{
    initMainWindow();

    initMiddleBlock();

    //initTopBlock();

    AbstractDisplay::init();
}

void MpsuDisplay::initMainWindow()
{
    CfgReader cfg;

    int     sizeWindow_X = 1024;
    int     sizeWindow_Y = 768;
    bool    hideCursor = true;
    int     timeInterval = 100;


   if (cfg.load(config_dir + getConfPath("main.xml")))
    {
        QString sectionName = "Main";
        cfg.getInt(sectionName, "sizeWindow_X", sizeWindow_X);
        cfg.getInt(sectionName, "sizeWindow_Y", sizeWindow_Y);
        cfg.getBool(sectionName, "hideCursor", hideCursor);
        cfg.getInt(sectionName, "timeInterval", timeInterval);
    }



    this->setCursor( hideCursor ? Qt::BlankCursor : Qt::ArrowCursor);


    //this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(sizeWindow_X, sizeWindow_Y);
    //this->setAutoFillBackground(true);
    //this->setPalette(QPalette(QColor(0, 0, 0)));

    updateTimer = new QTimer;
    connect(updateTimer, &QTimer::timeout, this, &MpsuDisplay::slotUpdateTimer, Qt::QueuedConnection);
    updateTimer->setInterval(timeInterval);
    updateTimer->start();
}

void MpsuDisplay::initMiddleBlock()
{
    middleBlock_ = new MiddleBlock(config_dir + getConfPath(""),
                                   config_dir + getConfPath("display1.xml"), MIDDLE_BLOCK_GEO, this);
    this->layout()->addWidget(middleBlock_);
}

void MpsuDisplay::initTopBlock()
{

}

void MpsuDisplay::slotUpdateTimer()
{
    display_data_t all_data;

    //Спидометр
    all_data.screen_main.sCurSpeed = static_cast<double>(input_signals[MPSU_CURRENT_SPEED]);
    all_data.screen_main.sCurSpeedLimit = static_cast<int>(input_signals[MPSU_CURRENT_SPEED_LIMIT]);
    all_data.screen_main.sNextSpeedLimit = static_cast<int>(input_signals[MPSU_NEXT_SPEED_LIMIT]);
    //Треугольник
    all_data.screen_main.sSetpointSpeed = input_signals[MPSU_sSeptoinSpeed];


    all_data.screen_main.pressureTM = static_cast<double>(input_signals[MPSU_TM]);
    all_data.screen_main.pressureUR = static_cast<double>(input_signals[MPSU_UR]);
    all_data.screen_main.pressurePM = static_cast<double>(input_signals[MPSU_PM]);
    all_data.screen_main.pressureTC = static_cast<double>(input_signals[MPSU_TC]);
    all_data.screen_main.pressureVR = static_cast<double>(input_signals[MPSU_VR]);


      //давление в КТО
    all_data.screen_main.pressureAST = static_cast<double>(input_signals[MPSU_AST]);


    all_data.screen_main.TC1 = static_cast<int>(input_signals[MPSU_TC1] * 100);
    all_data.screen_main.TC2 = static_cast<int>(input_signals[MPSU_TC2] * 100);
    all_data.screen_main.TC3 = static_cast<int>(input_signals[MPSU_TC3] * 100);


    //???
//    all_data.screen_main.I = static_cast<double>(input_signals[MPSU_I]);


    //????
   // all_data.screen_main.U = static_cast<double>(input_signals[MPSU_U]);


    //напряжение контактной сети
    all_data.status_bar.contactVoltage = static_cast<double>(input_signals[MPSU_CONTACT_VOLTAGE]);

    //род тока
    all_data.status_bar.currentType = static_cast<CurrentTypeEnum>(input_signals[MPSU_CURRENT_TYPE]);


    //??? уровень давления в АСТ
//    all_data.screen_main.P = static_cast<double>(input_signals[MPSU_P]);


    //нагрузка ТПр
    for (int i = 0; i < 2; ++i)
    {
    all_data.screen_main.ltct.pantograph[i].num = PantographNumEnum::forward;
    all_data.screen_main.ltct.pantograph[i].ready = static_cast<bool>(input_signals[MPSU_ltct]);
    all_data.screen_main.ltct.pantograph[i].active = static_cast<bool>(input_signals[MPSU_ltct]);

    all_data.screen_main.ltct.pantograph[i].num = PantographNumEnum::backward;
    all_data.screen_main.ltct.pantograph[i].ready = static_cast<bool>(input_signals[MPSU_ltct]);
    all_data.screen_main.ltct.pantograph[i].active = static_cast<bool>(input_signals[MPSU_ltct]);
}


    // I и U в состоянии ЭПТ
    all_data.screen_main.outputI = static_cast<double>(input_signals[MPSU_outputI]);
    all_data.screen_main.outputU = static_cast<int>(input_signals[MPSU_outputU]);


        // Сигнал СОПТ!
//    all_data.screen_main.numSwitch = static_cast<NumIndicatorSwitchPosEnum>(input_signals[MPSU_numSwitch]);



    //Пробег электровоза
   all_data.screen_main.sTrainPos = static_cast<double>(input_signals[MPSU_sTrinPos]);


   //????
   // all_data.screen_main.reversorDir = input_signals[MPSU_reversorDir];

    // Напряжение U цу (индикация напряжения в цепи управления и АБ;) Оранжевый квадратик
    all_data.screen_main.controlVoltage = input_signals[MPSU_controlVoltage];



    //индикатор состояния мотор-компрессора
    all_data.screen_main.motorCompressor1 = static_cast<MotorCompressorEnum>(input_signals[MPSU_motorCompressor1]);
    all_data.screen_main.motorCompressor2 = static_cast<MotorCompressorEnum>(input_signals[MPSU_motorCompressor2]);


    // Уровни тяги!
    all_data.screen_main.scaleSetTraction = static_cast<int>(input_signals[MPSU_scaleSetTraction]);
    all_data.screen_main.scaleActualTraction  = static_cast<int>(input_signals[MPSU_scaleActualTraction]);

    //режим управления
    all_data.status_bar.controlMode = static_cast<ControlModeEnum>(input_signals[MPSU_CONTROL_MODE]);

    //направление
    all_data.status_bar.directionTravel = static_cast<DirectionTravelEnum>(input_signals[MPSU_DIRECTION_TRAVEL]);


    //Вентилятор
    all_data.status_bar_bottom.fanAngle = input_signals[MPSU_FAN_ANGLE];

    //???
    //    for (int i = 0; i < 4; ++i)
//        all_data.screen_main.forces[i] = static_cast<qint8>(input_signals[MPSU_forces]);
//    for (int i = 0; i < 4; ++i)
//        all_data.screen_main.refForces[i] = static_cast<qint8>(input_signals[MPSU_refForces]);


    middleBlock_->setAllData(all_data);
}

GET_DISPLAY(MpsuDisplay)
