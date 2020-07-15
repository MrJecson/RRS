//-----------------------------------------------------------------------------
//
//      Абстрактный класс элементов индикации/управления
//      (c) РГУПС, ВЖД 17/04/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Абстрактный класс панелей управления/индикации
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 17/04/2017
 */

#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H


#include <QLabel>
#include "display-shared-data.h"
//#include "structures-display.h"

class AbstractElementDrawEngine;

/*!
 * \class AbstractElement
 * \brief Базовый класс различных элементов управления/индикации
 */
class AbstractElement : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param state - включен/выключен
     * \param type - Состояние элемента
     */
    AbstractElement(QString name, bool state, Elements::IconType type,
                    QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~AbstractElement();

    /// Вернуть название эелемента
    QString name();

    /// Установить информацию
    void setInfo(QString screenName, int columnNumber);

    /// Активация мигания элемента
    void activateBlink();

    /// Деактивация мигания
    void deactivateBlink();

    /// Проверка на мигание
    bool isActive();

    /// Вернуть тип элемента (itNORMAL - itDISCONNECT)
    Elements::IconType type();

    /// Вернуть состояние (вкл/выкл)
    bool state();

    /// Установить заданное состояние вручную (вручную через экран)
    virtual void setRefStateManual(bool refSt);

    /// Установить заданное состояние системно (от сервера)
    void setRefStateSystem(bool refSt);

    /// Вернуть заданное состояние
    bool refState();

    /// Задать характеристики элемента
    void updateElement(bool rfSt, bool st, uchar tp);

    /// Задать состояние блокировки элемента
    void updateBlocking(bool rfBlk, bool curBlk);

    /// Вернуть указатель на текущее состояние
    bool* curState_ptr();

    /// Вернуть указатель на заданое состояние
    bool* refState_ptr();

    /// Вернуть указатель на текущую блокировку
    bool* curBlock_ptr();

    /// Вурнеть указатель на заданную блокировку
    bool* refBlock_ptr();

    /// Установить заданную блокировку вручную
    virtual void setRefBlockedManually(bool blocked);

    /// Установить заданную блокировку системой
    void setRefBlockedBySystem(bool rfBlk);

    /// Переключить заданную блокировку
    void toggleRefBlock();

    /// Вернуть статут текущей блокировки
    bool isBlocked() const;

    /// Вернуть статус любой блокировки
    bool isAnyBlockedNew() const;

    /// Вернуть не нарушена ли связь с элементом
    bool isConnected();

    /// Установить метод отрисовки
    void setElementDrawEngine(AbstractElementDrawEngine* engine);

    /// Сброс всех состояний при разрыве связи
    void resetOnDisconnect();


public slots:
    /// Обработка таймера мигания
    void onTimerBlink();


private:
    QString     name_;      ///< Имя элемента

    QString     screen_;    ///< Имя экрана владельца

    QString     column_;    ///< Имя контролирующего столбца

    int         boxX_;      ///< Положение бокса по X

    int         boxY_;      ///< Положение бокса по Y

    int         boxW_;      ///< Ширина бокса

    int         boxH_;      ///< Высота бокса

    Elements::IconType    type_;    ///< Тип (норма, сообщ., сбой и т.д.)

    bool        state_;             ///< Состояние вкл/выкл (вкл/выкл)

    bool        refState_;          ///< Заданное состояние (вкл/выкл)

    bool        blockedBySystem_;   ///< Заблокирован системой

    bool        blockedManually_;   ///< Заблокирован вручную

    bool        curBlocked_; ///< Текущая блокировка

    bool        refBlocked_; ///< Заданная блокировка

    QTimer*     timerBlink_;        ///< Таймер мигания

    int         timerBlinkInterval_; ///< Интервал мигания

    int         responseWaitingConstant_; ///< Время ответа от сервера

    int         currentWaiting_; ///< Счетчик ожидания

    bool        blink_;             ///< Флаг инверсии при мигании

    int         untouchableTimeConstant_; ///< Константа "неприкосновенности"

    int         untouchableCounter_; ///< Счесчик "непрокосновенности"

    QLabel*     canvas_;    ///< Верхний виджет для отрисовки элемента

    bool        firstUpdate_; ///< Флаг первого обновления элемента

    /// Включение/выключение элемента
    void setState_(bool state);

    /// Установка состояния элемента
    void setType_(Elements::IconType type);

    /// Метод обработки ожидания ответа от сервера
    void waitForResponseFromServer_();

    /// Сбросить счетчик ожидания ответа от сервера
    void resetResponseWaiting_();

    /// Сделать элемент "неприкосновенным" на заданное время
    void setUntouchable_();

    /// Жестко задать текущее состояние блокировки
    void setCurBlocked_(bool blocked);


protected:
    /// Метод отрисовки элемента
    AbstractElementDrawEngine* drawEngine_;

    /// Флаг ручной установки состояния
    bool manual_;

    /// Флаг ручной установки блокировки
    bool manualBlock_;

    // Необходимо только для внутреннего использования в ElementSelector!
    /// Принудительно изменить значение заданного состояния
    void setRefStateForced_(bool refSt);

    /// Принудительно изменить заданную блокировку
    void setRefBlockedForced_(bool rfBlk);

    /// Вернуть положение бокса по X
    int boxX();

    /// Вернуть положение бокса по Y
    int boxY();

    /// Вернуть ширину бокса
    int boxW();

    /// Вернуть высоту бокса
    int boxH();

    /// Установить положение бокса
    void setBoxPos(int x, int y);

    /// Усановить размер бокса
    void setBoxSize(int w, int h);

    /// Метод отрисовки жёлтого треугольника блокировки
    void drawTriangle_(QPainter &p, bool back = false);

    /// Метод отрисовки элемента целиком
    virtual void drawElement_() = 0;

    /// Метод отрисовки самого значка (чекбокса) элемента
    QImage drawBox();

    /// Отрисовка элемента при отсутствии соединения
    void drawDisconnected(QPainter &p);

    /// Отрисовка базовой части бокса
    void drawBase(QPainter &p);

    /// Отрисовка крестика выбора
    void drawCross(QPainter &p);

    friend class AbstractElementDrawEngine;
    friend class ElementIndicatorDrawEngine;
    friend class ElementSelectorDrawEngine;

private slots:
    /// Событие скрытия элемента
    void hideEvent(QHideEvent *e);

};

#endif // ABSTRACTELEMENT_H
