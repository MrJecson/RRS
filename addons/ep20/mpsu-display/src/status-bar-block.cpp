//-----------------------------------------------------------------------------
//
//      Класс верхней строки состояния окна
//      (c) РГУПС, ВЖД 30/03/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс верхней строки состояния окна
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 30/03/2017
 */

#include "status-bar-block.h"

#include <QLabel>


constexpr int LABEL_HGT = 40;


//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
StatusBarBlock::StatusBarBlock(QColor backrg, QRect geo, QWidget *parent) :
    AbstractBlock(geo, parent)
{
    this->setPalette(QPalette(backrg));
    // Создаём все надписи
    createAllChildren_();
}



//-----------------------------------------------------------------------------
//  ДЕСТРУКТОР
//-----------------------------------------------------------------------------
StatusBarBlock::~StatusBarBlock()
{

}



//-----------------------------------------------------------------------------
//  Установить номер активной кабины
//-----------------------------------------------------------------------------
void StatusBarBlock::setCabin(CabinNumEnum num)
{
    QString str("");
    switch (num)
    {
    case CabinNumEnum::first:
        str = "1";
        break;
    case CabinNumEnum::last:
        str = "2";
        break;
    }

    labCabin_->setText("Каб. " + str);
}

//-----------------------------------------------------------------------------
//  Установить направление движения
//-----------------------------------------------------------------------------
void StatusBarBlock::setDirectionTravel(DirectionTravelEnum dir)
{
    QString str("");
    switch (dir)
    {
    case DirectionTravelEnum::forwardDT:
        str = "Вперёд";
        break;
    case DirectionTravelEnum::backwardDT:
        str = "Назад";
        break;
    }

    labDirectionTravel_->setText(str);
}

//-----------------------------------------------------------------------------
//  Установить режим управления
//-----------------------------------------------------------------------------
void StatusBarBlock::setControlMode(ControlModeEnum controlMode)
{
    QString str("");
    switch (controlMode)
    {
    case ControlModeEnum::manualControl:
        str = "Ручное управление";
        break;
    case ControlModeEnum::automaticControl:
        str = "Автоматическое управление";
        break;
    }

    labControlMode_->setText(str);
}

//-----------------------------------------------------------------------------
//  Установить индикацию задания режима тяги или ЭТ
//-----------------------------------------------------------------------------
void StatusBarBlock::setTractionModeIndication(TractionModeIndicationEnum mode)
{
    QString str("");
    switch (mode)
    {
    case TractionModeIndicationEnum::traction:
        str = "Тяга";
        break;
    case TractionModeIndicationEnum::recuperation:
        str = "Рекуперация";
        break;
    case TractionModeIndicationEnum::reostat:
        str = "Реостат";
        break;
    case TractionModeIndicationEnum::disassembled:
        str = "Разобрана";
        break;
    }

    labTractionModeIndication_->setText(str);
}

//-----------------------------------------------------------------------------
//  Установить тип основного тормоза
//-----------------------------------------------------------------------------
void StatusBarBlock::setTypeBrake(TypeBrakeEnum brakeType)
{
    QString str("");
    switch (brakeType)
    {
    case TypeBrakeEnum::PT:
        str = "ПТ";
        break;
    case TypeBrakeEnum::EPT:
        str = "ЭПТ";
        break;
    }

    labTypeBrake_->setText(str);
}

//-----------------------------------------------------------------------------
//  Установить род тока
//-----------------------------------------------------------------------------
void StatusBarBlock::setCurrentType(CurrentTypeEnum currentType)
{
    QString str("");
    switch (currentType)
    {
    case CurrentTypeEnum::AC:
        str = "~";
        break;
    case CurrentTypeEnum::DC:
        str = "=";
        break;
    case CurrentTypeEnum::notDetermined:
        str = "";
        break;
    }

    labCurrentType_->setText(str);
}

//-----------------------------------------------------------------------------
//  Установить напряжение контактной сети
//-----------------------------------------------------------------------------
void StatusBarBlock::setContactVoltage(double val)
{
    labContactVoltage_->setText(QString::number(val, 'f', 1) + " КВ");
}



//-----------------------------------------------------------------------------
// (слот) Установить значения строки состояния
//-----------------------------------------------------------------------------
void StatusBarBlock::updateStatusBar(status_bar_data_t* data)
{
    setCabin(data->cabinNum);
    setDirectionTravel(data->directionTravel);
    setControlMode(data->controlMode);
    setTractionModeIndication(data->tractionModeIndication);
    setTypeBrake(data->typeBrake);
    setCurrentType(data->currentType);
    setContactVoltage(data->contactVoltage);
}



//-----------------------------------------------------------------------------
// Переопределение чистого виртуального метода
//-----------------------------------------------------------------------------
void StatusBarBlock::createAllChildren_()
{
    createLabel_(labCabin_, "Каб. 1", Qt::AlignCenter,
                 QSize(100, LABEL_HGT));

    createLabel_(labDirectionTravel_, "Вперёд", Qt::AlignCenter,
                 QSize(120, LABEL_HGT));

    createLabel_(labControlMode_, "Ручное управление", Qt::AlignCenter,
                 QSize(240, LABEL_HGT));

    createLabel_(labTractionModeIndication_, "Разобрана", Qt::AlignCenter,
                 QSize(150, LABEL_HGT));

    createLabel_(labTypeBrake_, "ПТ", Qt::AlignCenter,
                 QSize(50, LABEL_HGT));

    createLabel_(labCurrentType_, "", Qt::AlignCenter,
                 QSize(50, LABEL_HGT));

    createLabel_(labContactVoltage_, "0.0 КВ", Qt::AlignCenter,
                 QSize(100, LABEL_HGT));

    // Упорядочиваем все надписи
    autoChildrenPos_(-1);
}



//-----------------------------------------------------------------------------
// // Метод, создающий QLabel'ы по входным параметрам
//-----------------------------------------------------------------------------
void StatusBarBlock::createLabel_(QLabel* &lab, QString text,
                                  Qt::AlignmentFlag align, QSize labSize, int _lPad)
{
    // Создаём лэйбл
    lab = new QLabel(this);
    lab->setText(text);
    lab->setFont(QFont("Arial", 14, QFont::DemiBold));
    lab->resize(labSize);
    lab->setAlignment(align);
    // Генерируем CSS текст по входным параметрам
    QString foo("font-family: \'Arial\';"
                "border-left: 1px solid #c8c8c8;"
                "border-bottom: 1px solid #c8c8c8;"
                "border-right: 1px solid #c8c8c8;"
                "padding-left: " + QString::number(_lPad) +"px;"
                "color: white;"
                "background-color: #051432;");

    // Устанавливаем стиль
    lab->setStyleSheet(foo);
    //lab->setStyleSheet("border: 1px solid white");
    QPoint p = lab->pos();

}


