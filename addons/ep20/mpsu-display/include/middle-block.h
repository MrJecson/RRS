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

#ifndef MIDDLEBLOCK_H
#define MIDDLEBLOCK_H


#include <QMap>

#include <QWidget>
#include "a-consts.h"
#include "structures-display.h" // FIXME

struct refs_t;

class SoftButtonsBlock;
class ConditionLineBlock;
class StatusBarBlock;
class StatusBarBlockBottom;
class AbstractScreen;

class ScreenConnectionError;
class ScreenMain;
class ScreenDiagnostics;
class ScreenPowerCircuit;
class ScreenPneumatics;
class ScreenDiagnostic;
class ScreenLog;

#include "display-shared-structures.h"

/*!
 * \class MiddleBlock
 * \brief Класс центрального виджета
 */
class MiddleBlock : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param geo
     */
    MiddleBlock(const QString &config_dir, const QString &configFileName, QRect geo, QWidget* parent = Q_NULLPTR); // FIXME - убрать geo из конструктора
    /// Деструктор
    ~MiddleBlock();

    /// Вернуть флаг сброса манометра ТМ/ПМ
    bool getResetManometerTMPM();

    /// Вернуть флаг сброса манометра ТЦ1/ТЦ2
    bool getResetManometerTC12();


    void setAllData(display_data_t &allData);

public slots:
    /// Принимаем данные из главного окна
    void receiveAllData(QByteArray allArr);

    /// Обработка нажатия кнопки
    void receiveButtonPressed(Local::ButtonId id);

    /// Обработка разрыва связи с сервером
    void onTcpDisconnectedFromServer();

    /// Обработка восстановления связи с сервером
    void onTcpConnectedToServer();    

private:
    // Цвет экрана при выключении
    QString colorHexName_; ///< Цвет экрана при выключении

    // Флаг включенности экрана
    bool screenIsEnabled_;  ///< Флаг включенности экрана

    // Блок программируемых клавиш (нижняя строка)
    SoftButtonsBlock*   softButtonsBlock_; ///< Блок программируемых клавиш
    SoftButtonsBlock*   softButtonsBlockTop_; ///< Блок программируемых клавиш

    // Блок информационной строки (нижняя строка)
    //ConditionLineBlock* conditionLineBlock_; ///< Блок информационной строки

    // Блок строки состояния (верхняя строка)
    StatusBarBlock* statusBarBlock_; ///< Блок строки состояния

    //
    StatusBarBlockBottom* statusBarBlockBottom_;


    // ! *** *** *** *** *** Объявление всех экранов *** *** *** *** *** ! //
    QList<AbstractScreen*>  listScreens_;       ///< Список всех экранов
    ScreenMain*             scrnMain_;          ///< Основной экран
    ScreenDiagnostics*      scrnDiagnostics_;   ///< Экран диагностики
    ScreenPowerCircuit*     scrnPowerCircuit_;  ///< Экран силовой схемы
    ScreenPneumatics*       scrnPneumatics_;    ///< Экран пневматики
    ScreenDiagnostic*       scrnDiagnostic_;    ///< Экран диагностики
    ScreenLog*              scrnLog_;           ///< Экран вывода лога

    QMap<QString, AbstractScreen*> mapScreens_;     ///< Список всех экранов
    // ! *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ! //

    // Указатель на текущий экран
    AbstractScreen* currentScreen_; ///< Указатель на текущий экран

//    enum ScreenTree
//    {
//        SC_MAIN,
//        SC_BRAKES
//    };

//    // Текущая ветка экранов
//    ScreenTree currentTree_;

    // Текущая "голова" дерева экранов
    AbstractScreen* currentTreeHead_;

    ///
    ScreenConnectionError* scrnConnectionError_;

    /// Определяем какой экран будет показан после запуска
    AbstractScreen* loadTreeHeadFromCfg(const QString &configFileName);

    QString config_dir;

    /// Обрабатываем нажание на кнопки с цифрами
    void digitButton_(int num);

    ///
    void mapNewScreen(QString scrnName, AbstractScreen* nScrn);


// ПАРАМЕТРЫ БЛОКА ПРОГРАММИРУЕМЫХ КЛАВИШ *************************************
    /// Геометрия
    const QRect  SOFT_BLOCK_GEO_ = QRect(1, 547, 798, 40);
    const QRect  SOFT_BLOCK_TOP_GEO_ = QRect(1, 1, 798, 40);

    /// Цвет
    const QColor SOFT_BLOCK_COLOR_ = QColor(5, 20, 50);

    /// Размер программируемых кнопок
    const QSize  SOFT_BUTTONS_SIZE_ = QSize(80, 40);


// ПАРАМЕТРЫ ИНФОРМАЦИОННОГО БЛОКА КЛАВИШ *************************************
    /// Геометрия информациооного блока
    const QRect CONDITION_LINE_GEO_ = QRect(1, 508, 798, 40);

    /// Цвет
    const QColor CONDITION_LINE_COLOR_ = QColor(5, 20, 50);

    /// Размер картинок
    const QSize CONDITION_IMAGES_SIZE_ = QSize(85, 40);


// ПАРАМЕТРЫ БЛОКА СТАТУС БАРА ************************************************
    /// Геометрия строки сотояния
    const QRect STATUS_BAR_GEO_ = QRect(1, 1, 798, 40);

    /// Цвет фона строки состояния
    const QColor STATUS_BAR_COLOR_ = QColor(5, 20, 50);


// ПАРАМЕТРЫ БЛОКА СТАТУСНОЙ СТРОКИ КАДРА *************************************
    /// Геометрия строки сотояния
    const QRect STATUS_BAR_BOTTOM_GEO_ = QRect(1, 494, 798, 53);

    /// Цвет фона строки состояния
    const QColor STATUS_BAR_BOTTOM_COLOR_ = QColor(5, 20, 50);


// ПАРАМЕТРЫ ВСЕХ ЭКРАНОВ *****************************************************
    ///Геометрия экранов
    const QRect SCRNS_GEO_ = QRect(1, 40, 798, 454);


};
#endif // MIDDLEBLOCK_H
