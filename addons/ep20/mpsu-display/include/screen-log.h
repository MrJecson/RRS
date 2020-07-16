//-----------------------------------------------------------------------------
//
//      Класс экрана вывода лога
//      (c) РГУПС, ВЖД 27/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс экрана вывода лога
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 27/10/2017
 */

#ifndef SCREENLOG_H
#define SCREENLOG_H


#include "abstract-screen.h"


/*!
 * \class ScreenLog class
 * \brief Класс экрана вывода послденего сеанса лога
 */
class ScreenLog Q_DECL_FINAL : public AbstractScreen
{

public:
    /// Конструктор
    ScreenLog(QString scrName, QRect scrGeo,
              QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~ScreenLog();

    /// Подготовить экран и вывести лог
    void prepareLogScreen();

    /// Сброс экрана при разрыве связи с сервером
    void resetOnDisconnect() Q_DECL_OVERRIDE;


public slots:
    /// Обработка нажатия кнопки
    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновление данных экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    // Список строк последнего лога
    QStringList listLogs_; ///< Список строк последнего лога

    // Номер строки последнего лога
    quint64 lastLogLine_; ///< Номер строки последнего лога

    // Количество строк последнего лога
    quint16 logsCount_; ///< Количество строк последнего лога

    // Количество надписей(строк) экрана лога
    quint16 labelsCount_; ///< Количество надписей(строк) экрана лога

    // Разница между количествами строк последнего лога и надписей экрана
    quint16 countsDiff_; ///< Разница между количествами строк последнего лога и надписей экрана

    // Текущая строка начала показа
    quint16 currentLine_; ///< Текущая строка начала показа

    // Счетчик периодического считывания лога
    quint8 logUpdateCounter_; ///< Счетчик периодического считывания лога

    /// Поиск номера строки последнего сеанса лога
    void searchLastLog();

    /// Загрузка последнего сеанса лога
    void loadLastLog();

    /// Показать последний сеанс лога с pos строки
    void showLastLog(quint16 pos);

    ///
    void clearLog_();

    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

};

#endif // SCREENLOG_H
