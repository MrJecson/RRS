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

#ifndef SCENTRALELEMENTS_H
#define SCENTRALELEMENTS_H

#include <QLabel>

/*!
 * \class SCentralElements
 * \brief Центральные элементы (динамические)
 */
class SCentralElements : QLabel
{
public:
    /// Конструктор
    SCentralElements(const QString &config_dir, QWidget* parent = Q_NULLPTR);

    void drawCenterCircle(QString color);

    /// Установить значение текущей скорости
    void setCurSpeed(int speedValue);
    /// Установить значение ограничения скорости
    void setLimitSpeed(int speedValue);
    // Установить заданное значение скорости
    void setSetpointSpeed(int setpointValue);
    //
    void setPosTrain(double val);

//    void setVisibleCurSpeed(bool flag);
    QLabel* getCurSpeed();


private:
    double w_2_;
    double h_2_;

    QImage img_;

    QLabel* labelTextCurSpeed_;     ///< виджет для знач. текущей скорости
    QLabel* labelTextLimitSpeed_;   ///< виджет для знач. ограничения скорости
    QLabel* labelTextSetpointSpeed_;
    QLabel* labelTextCurPosTrain_; ///< виджет для знач. текущей координаты

    // --- cfg параметры --- //
    int textFont_;  ///< размер шрифта

    /// значение текущей скорости на центральном круге
    QString curSpeed_textColor_;    ///< цвет текста

    /// значение ограничения под центральным кругом
    QString limitSpeed_textColor_;  ///< цвет текста
    int limitSpeed_textMargin_;     ///< смещение текста по оси OY
    // --------------------- //

    /// Нарисовать виджет текста
    void drawText_(QLabel *label, int dy, QString color, int fontSize = 0);
    /// Установить текст
    QString setText_(int speedValue);


    /// Чтение конфигураций
    bool loadCfg_(QString cfg_path);

};

#endif // SCENTRALELEMENTS_H
