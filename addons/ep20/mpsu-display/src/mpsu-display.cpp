#include    "mpsu-display.h"

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

}

GET_DISPLAY(MpsuDisplay)
