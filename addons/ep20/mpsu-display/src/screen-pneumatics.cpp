//-----------------------------------------------------------------------------
//
//      Класс "Пневматика (КТО)"
//      (c) РГУПС, ВЖД 13/09/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Пневматика (КТО)"
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 13/09/2019
 */

#include "screen-pneumatics.h"

#include <QLabel>


//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
ScreenPneumatics::ScreenPneumatics(QString scrName, QRect scrGeo, QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
{
    //
    this->setVisible(false);

    buttonsNames_ = QStringList{"Главный\nкадр", "Авто-\nведение", "Диагнос-\nтика",
                                "Архив", "КТО", "Положение\nкранов", "Тест 130\nкрана",
                                "ПКЛ1", "ПКЛ2", ""};

    buttonsNamesTop_ = QStringList{"Отмена", "", "", "", "", "", "", "",
                                   "Откл.\nкопр. 1", "Откл.\nкомпр. 2"};

    buttonNamesHead_ = "Пневматика(КТО)";
    buttonNamesHeadNum_ = 1;
    buttonNamesHeadCount_ = 7;

    buttonSelectedIdx_ = 4;

    //
    this->createAllChildren_();
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPneumatics::updateScreen(screen_data_t *data)
{
    screen_pneumatics_t* spt = static_cast<screen_pneumatics_t*>(data);

    //
    labUR_->setText(QString::number(spt->UR, 'f', 3));
    labDD_->setText(QString::number(spt->DD, 'f', 2));
    labDD1_BTO_->setText(QString::number(spt->DD1_BTO, 'f', 2));
    labDD2_BTO_->setText(QString::number(spt->DD2_BTO, 'f', 2));
    labDD3_BTO_->setText(QString::number(spt->DD3_BTO, 'f', 2));
    labDD4_BTO_->setText(QString::number(spt->DD4_BTO, 'f', 2));
    labDD5_BTO_->setText(QString::number(spt->DD5_BTO, 'f', 2));
    labDD6_BTO_->setText(QString::number(spt->DD6_BTO, 'f', 2));
    labDD1_BIO_->setText(QString::number(spt->DD1_BIO, 'f', 2));
    labDD2_BIO_->setText(QString::number(spt->DD2_BIO, 'f', 2));
    labDD3_BIO_->setText(QString::number(spt->DD3_BIO, 'f', 2));
    labDD4_BIO_->setText(QString::number(spt->DD4_BIO, 'f', 2));
    labDD5_BIO_->setText(QString::number(spt->DD5_BIO, 'f', 2));

    // мотор-компрессоры
    labMotorCompressor1_->setPixmap(getMotorCompressorImgName_(spt->motorCompressor1));
    labMotorCompressor2_->setPixmap(getMotorCompressorImgName_(spt->motorCompressor2));
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPneumatics::createAllChildren_()
{
    QPixmap pixmap(PNEUMATICS_SCREEN_IMG_PREFIX_ + "pneumatics.png");

    //
    QLabel* labImg = new QLabel(this);
    labImg->resize(this->size());
    labImg->setStyleSheet("border: 1px solid black;"
                          "border-top: 2px solid black;"
                          "color: white;");
    labImg->setPixmap(pixmap);

    //
    createLabelPressure_(labUR_, QPoint(588, 205));
    labUR_->resize(60, 37);
    createLabelPressure_(labDD_, QPoint(172, 40));
    createLabelPressure_(labDD1_BTO_, QPoint(301, 85));
    createLabelPressure_(labDD2_BTO_, QPoint(245, 254));
    createLabelPressure_(labDD3_BTO_, QPoint(527, 109));
    createLabelPressure_(labDD4_BTO_, QPoint(177, 192));
    createLabelPressure_(labDD5_BTO_, QPoint(702, 224));
    createLabelPressure_(labDD6_BTO_, QPoint(489, 240));
    createLabelPressure_(labDD1_BIO_, QPoint(14, 353));
    createLabelPressure_(labDD2_BIO_, QPoint(105, 353));
    createLabelPressure_(labDD3_BIO_, QPoint(379, 351));
    createLabelPressure_(labDD4_BIO_, QPoint(490, 351));
    createLabelPressure_(labDD5_BIO_, QPoint(606, 351));

    // мотор-компрессоры
    createMotorCompressor_(labMotorCompressor1_, QPoint(645, 10));
    createMotorCompressor_(labMotorCompressor2_, QPoint(725, 10));
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPneumatics::createLabelPressure_(QLabel *&lab, QPoint pos)
{
    lab = new QLabel("0.00", this);
    lab->resize(55, 37);
    lab->move(pos);
    lab->setFont(QFont("Arial", 16));
    lab->setStyleSheet("border: 2px solid white;"
                       //"background: red;"
                       "font-style: italic;"
                       "color: white;");
    lab->setAlignment(Qt::AlignCenter);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenPneumatics::createMotorCompressor_(QLabel *&lab, QPoint pos)
{
    lab = new QLabel(this);
    lab->resize(62, 40);
    lab->move(pos);
    lab->setAlignment(Qt::AlignHCenter);
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
QString ScreenPneumatics::getMotorCompressorImgName_(int motorCompressorState)
{
    QString foo("");
    switch (motorCompressorState)
    {
    case MotorCompressorEnum::isolated:
        foo = "isolted";
        break;
    case MotorCompressorEnum::on:
        foo = "on";
        break;
    case MotorCompressorEnum::off:
        foo = "off";
        break;
    }

    return PNEUMATICS_SCREEN_IMG_PREFIX_ + "motor-compressor-" + foo + ".png";
}
