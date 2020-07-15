//-----------------------------------------------------------------------------
//
//      Абстрактный класс экранов
//      (c) РГУПС, ВЖД 11/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс экранов
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/04/2017
 */

#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H


#include <QWidget>

#include "a-consts.h"
#include "sapsan-shared-data.h"
//#include "display-shared-data.h"

class ElementIndicator;
class QLabel;

struct screen_data_t;

/*!
 * \class AbstractScreen
 * \brief Базовый класс для всех экранов управления
 */
class AbstractScreen : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param scrName - имя экрана для вывода в строке состояния
     * \param scrGeo - геометрия экрана
     */
    AbstractScreen(QString scrName, QRect scrGeo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~AbstractScreen();

    typedef QPair<int, AbstractScreen*> ScreenPair ;

    /// Вернуть имя экрана
    QString getScreenName();

    /// Установить возможность перехода на данный экран
    void setAvailableToGo(bool available);

    /// Вернуть возможность перехода на данных экран
    bool isAvailableToGo();

    /// Переход на экран по номеру клавиши
    bool goToScreen(int num, AbstractScreen* &currScr);

    /// Добавление экрана в список доступных
    AbstractScreen* setScreen(int ind, AbstractScreen* scr);

    /// Установить экраны в список доступных
    void setScreens(QVector<ScreenPair> _vec);

    /// Вернуть имена кнопок для блока программируемых кнопок
    virtual const QStringList getButtonsNames();
    virtual const QStringList getButtonsNamesTop();
    virtual const QString getButtonsNamesHead();
    virtual int getButtonsNamesHeadNum();
    virtual int getButtonsNamesHeadCount();
    virtual int getButtonSelectedIdx();

    /// Установить индикатор по индексу
    void setIndicator(int index, ElementIndicator* element);

    /// Установить род тока
    static void setPowerType(PowerSystemData::PowerType _pt);

    /// Вернуть род тока
    static PowerSystemData::PowerType getPowerType();

    /// Сброс экрана и всех подконтрольных элементов при разрыве соединения
    virtual void resetOnDisconnect();

    /// Действия при переходе на этот экран
    virtual void doOnComeIn();

    /// Действия при переходе с этого экрана
    virtual void doOnComeOut();


signals:
    ///
    void sendButtonsNames(const QStringList &_list);


public slots:
    /// Обработка не цифровых кнопок
    virtual void receiveOtherButton(Local::ButtonId id);

    /// Обновить данные на экране
    virtual void updateScreen(screen_data_t* data) = 0;


protected:
    /// Список надписей
    QList<QLabel*> listLabels_;

    /// Список элементов индикации
    QList<ElementIndicator*> listIndicators_;

    ///
    static PowerSystemData::PowerType powerType_;

    /// Заполнить список индикаторов нулевыми указателями
    void initIndicators_(int number);

    /// Метод создания и настройки дочерних виджетов
    virtual void createAllChildren_() = 0;

    ///
    QStringList buttonsNames_;
    QStringList buttonsNamesTop_;
    QString buttonNamesHead_;
    int buttonNamesHeadNum_;
    int buttonNamesHeadCount_;
    int buttonSelectedIdx_;


private:
    /// Флаг доступности перехода на данный экран
    bool availableToGo_;

    const QString SCREEN_NAME_; ///< Название экрана

    /// Список ссылок на доступные экраны
    QList<AbstractScreen*> listScreens_;
};


#endif // ABSTRACTSCREEN_H
