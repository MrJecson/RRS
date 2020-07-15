//-----------------------------------------------------------------------------
//
//      Центральные элементы (динамические)
//      (c) РГУПС, ВЖД ../10/2017
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 * \file
 * \brief Центральные элементы (динамические)
 * \copyright РГУПС, ВЖД
 * \author Даглдиян Б.Д.
 * \date ../10/2017
 */

#include "SCentralElements.h"

#include "CfgReader.h"

#include <QPainter>
#include <QtCore/qmath.h>

//const	QString		SCENTRALELEMENTS_CFG = "../cfg/display/SCentralElements.xml";

//-----------------------------------------------------------------------------
//  Конструктор
//-----------------------------------------------------------------------------
SCentralElements::SCentralElements(const QString &config_dir, QWidget *parent) : QLabel(parent)
{
    this->resize(parent->size());
    w_2_ = this->width()/2.0;
    h_2_ = this->height()/2.0;
    this->setStyleSheet("border: none");

    loadCfg_(config_dir);

    labelTextCurSpeed_ = new QLabel("", this);
    drawText_(labelTextCurSpeed_, 0, curSpeed_textColor_);
    labelTextLimitSpeed_ = new QLabel("", this);
    drawText_(labelTextLimitSpeed_, limitSpeed_textMargin_, limitSpeed_textColor_);
    labelTextSetpointSpeed_ = new QLabel("", this);
    drawText_(labelTextSetpointSpeed_, 40, "#0000ff");
    labelTextCurPosTrain_ = new QLabel("00000000.0 км", this);
    drawText_(labelTextCurPosTrain_, 105, "#ffffff", 16);

    // "по дефолту"
    setCurSpeed(0);


    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
}

//-----------------------------------------------------------------------------
//  Установить значение текущей скорости
//-----------------------------------------------------------------------------
void SCentralElements::setCurSpeed(int speedValue)
{
    labelTextCurSpeed_->setText(setText_(speedValue));
}

//-----------------------------------------------------------------------------
//  Установить значение ограничения скорости
//-----------------------------------------------------------------------------
void SCentralElements::setLimitSpeed(int speedValue)
{
    labelTextLimitSpeed_->setText(setText_(speedValue));
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void SCentralElements::setSetpointSpeed(int setpointValue)
{
    if (setpointValue == 0)
        labelTextSetpointSpeed_->setText("");
    else
        labelTextSetpointSpeed_->setText(setText_(setpointValue));
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void SCentralElements::setPosTrain(double val)
{
    int val_i = static_cast<int>(val);

    QString res("");
    for (int i = 0, n = 8; i < n; ++i)
    {
        res += QString::number((val_i % static_cast<int>(pow(10, n-i))) / static_cast<int>(pow(10, n-i-1)));
    }
    QString resOstatok(QString::number(static_cast<int>(round((val - val_i)*10))));

    //
    labelTextCurPosTrain_->setText(res + "." + resOstatok + " км");
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
QLabel* SCentralElements::getCurSpeed()
{
    return labelTextCurSpeed_;
}

//-----------------------------------------------------------------------------
//  Нарисовать виджет текста
//-----------------------------------------------------------------------------
void SCentralElements::drawText_(QLabel *label, int dy, QString color, int fontSize)
{
    label->setFont(QFont("Arial", (fontSize == 0) ? (textFont_) : (fontSize)));
    label->setStyleSheet("color: " + color);
    label->setGeometry( w_2_ - 100,
                        h_2_ - 100 + dy,
                        200,
                        200 );
    label->setAlignment(Qt::AlignCenter);
}

//-----------------------------------------------------------------------------
//  Установить текст
//-----------------------------------------------------------------------------
QString SCentralElements::setText_(int speedValue)
{
//    return  QString::number(speedValue/100) +
//            QString::number((speedValue % 100)/10) +
//            QString::number(speedValue % 10) ;
    return QString::number(speedValue);
}

//-----------------------------------------------------------------------------
// Нарисовать центральный круг
//-----------------------------------------------------------------------------
void SCentralElements::drawCenterCircle(QString color)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    paint.setPen(QPen( QColor(color),
                       50,
                       Qt::SolidLine,
                       Qt::RoundCap ));
    paint.drawPoint( this->width()/2,
                     this->height()/2 );

    paint.end();
    this->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//  Чтение конфигураций
//-----------------------------------------------------------------------------
bool SCentralElements::loadCfg_(QString cfg_path)
{
    CfgReader cfg;

    if (cfg.load(cfg_path))
    {
        QString sectionName = "SCentralElements";

        // размер шрифта значений
        if (!cfg.getInt(sectionName, "textFont", textFont_))
            textFont_ = 36;

        // цвет значения текущей скорости
        if (!cfg.getString(sectionName, "curSpeed_textColor", curSpeed_textColor_))
            curSpeed_textColor_ = "#ffffff";

        // цвет значения ограничения скорости
        if (!cfg.getString(sectionName, "limitSpeed_textColor", limitSpeed_textColor_))
            limitSpeed_textColor_ = "#ff0000";
        // смещение текста по оси OY
        if (!cfg.getInt(sectionName, "limitSpeed_textMargin", limitSpeed_textMargin_))
            limitSpeed_textMargin_ = 80;

    }
    else
    {
        // Параметры по умолчанию.

        textFont_ = 36; // размер шрифта значений

        curSpeed_textColor_ = "#ffffff"; // цвет значения текущей скорости

        limitSpeed_textColor_ = "#ff0000";  // цвет значения ограничения скорости
        limitSpeed_textMargin_ = 80;        // смещение текста по оси OY

    }

    return true;
}


