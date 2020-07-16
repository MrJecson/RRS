//-----------------------------------------------------------------------------
//
//      Экран сбоя связи
//      (c) РГУПС, ВЖД 11/07/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Экран сбоя связи
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/07/2017
 */

#ifndef SCREENCONNECTIONERROR_H
#define SCREENCONNECTIONERROR_H


class MiddleBlock;
class QLabel;


/*!
 * \class ScreenConnectionError
 * \brief Класс экрана "Нарушение связи"
 */
class ScreenConnectionError
{
public:
    /*!
     * \brief Конструктор
     * \param scSize - размер "экрана"
     * \param parent - родитель
     */
    ScreenConnectionError(MiddleBlock* parent);

    /// Деструктор
    ~ScreenConnectionError();

    /// Показать "экран"
    void enable();

    /// Скрыть "экран"
    void disable();

    /// Сделать видимым/невидимым (при вкл/выкл дисплее)
    void setVisible(bool visible);

    /// Вернуть статус включённости
    bool isEnabled() const;


private:
    /// Виджет экрана
    QLabel* labelError_;

    /// Флаг включенности
    bool enabled_;

    /// Флаг видимости
    bool visible_;

    /// Метод отрисовки "экрана"
    void drawErrorScreen_();

};

#endif // SCREENCONNECTIONERROR_H
