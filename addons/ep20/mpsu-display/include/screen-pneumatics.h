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

#ifndef SCREENPNEUMATICS_H
#define SCREENPNEUMATICS_H


#include "abstract-screen.h"
#include "display-shared-structures.h"


/*!
 * \class ScreenPneumatics
 * \brief Класс кадра пневматики
 */
class ScreenPneumatics : public AbstractScreen
{
public:
    ScreenPneumatics(QString scrName, QRect scrGeo, QWidget* parent = Q_NULLPTR);


public slots:
//    /// Обработка нажатия кнопок
//    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновление данных экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    //
    QLabel* labMotorCompressor1_;
    QLabel* labMotorCompressor2_;

    //
    QLabel* labUR_;
    QLabel* labDD_;
    QLabel* labDD1_BTO_;
    QLabel* labDD2_BTO_;
    QLabel* labDD3_BTO_;
    QLabel* labDD4_BTO_;
    QLabel* labDD5_BTO_;
    QLabel* labDD6_BTO_;
    QLabel* labDD1_BIO_;
    QLabel* labDD2_BIO_;
    QLabel* labDD3_BIO_;
    QLabel* labDD4_BIO_;
    QLabel* labDD5_BIO_;


// ПРЕФИКС ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ *******************************************
    /// Префикс нажатых клавиш
    const QString PNEUMATICS_SCREEN_IMG_PREFIX_ = ":/screen-imgs/images/screen-imgs/";



    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

    //
    void createLabelPressure_(QLabel* &lab, QPoint pos);

    //
    void createMotorCompressor_(QLabel* &lab, QPoint pos);

    QString getMotorCompressorImgName_(int motorCompressorState);
};

#endif // SCREENPNEUMATICS_H
