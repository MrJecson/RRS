#include    "mpsu-display.h"

#include    "ep20-signals.h"

#include    "CfgReader.h"
#include    <QVBoxLayout>

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

    all_data.screen_main.sCurSpeed = static_cast<double>(input_signals[MPSU_CURRENT_SPEED]);
    all_data.screen_main.sCurSpeedLimit = static_cast<int>(input_signals[MPSU_CURRENT_SPEED_LIMIT]);
    all_data.screen_main.sNextSpeedLimit = static_cast<int>(input_signals[MPSU_NEXT_SPEED_LIMIT]);

    all_data.screen_main.pressureTM = static_cast<double>(input_signals[MPSU_TM]);
    all_data.screen_main.pressureUR = static_cast<double>(input_signals[MPSU_UR]);
    all_data.screen_main.pressurePM = static_cast<double>(input_signals[MPSU_PM]);
    all_data.screen_main.pressureTC = static_cast<double>(input_signals[MPSU_TC]);
    all_data.screen_main.pressureVR = static_cast<double>(input_signals[MPSU_VR]);
    //all_data.screen_main.pressureAST;
    all_data.screen_main.TC1 = static_cast<int>(input_signals[MPSU_TC1]);
    all_data.screen_main.TC2 = static_cast<int>(input_signals[MPSU_TC2]);
    all_data.screen_main.TC3 = static_cast<int>(input_signals[MPSU_TC3]);
    //all_data.screen_main.I;
    all_data.screen_main.U = static_cast<double>(input_signals[MPSU_U]);
    //all_data.screen_main.P;
    //all_data.screen_main.ltct;
    //all_data.screen_main.forces;
    //all_data.screen_main.outputI;
    //all_data.screen_main.outputU;
    //all_data.screen_main.numSwitch;

    all_data.screen_main.refForces[0] = input_signals[MPSU_refForces];


    //all_data.screen_main.sTrainPos;
    //all_data.screen_main.reversorDir;
    //all_data.screen_main.controlVoltage;
    //all_data.screen_main.sSetpointSpeed;

    all_data.screen_main.motorCompressor1 = input_signals[MPSU_motorCompressor1];
    all_data.screen_main.motorCompressor2 = input_signals[MPSU_motorCompressor2];

    //all_data.screen_main.scaleSetTraction;
    //all_data.screen_main.scaleActualTraction;


    middleBlock_->setAllData(all_data);
}

GET_DISPLAY(MpsuDisplay)
