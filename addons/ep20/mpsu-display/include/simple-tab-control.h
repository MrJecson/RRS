//-----------------------------------------------------------------------------
//
//      Класс простого менеджера вкладок
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс простого менеджера вкладок
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#ifndef SIMPLETABCONTROL_H
#define SIMPLETABCONTROL_H

#include <QList>

class QWidget;
class QLabel;

//class SimpleTab;
#include "simple-tab.h"

//struct panel_diagnostic_t;

struct screen_data_t;


/*!
 * \class SimpleTabControl
 * \brief Класс имитации QTabControl в простом исполнении
 */
class SimpleTabControl
{

public:
    /// Конструктор
    SimpleTabControl(QWidget* container);
    /// Деструктор
    ~SimpleTabControl();

    /// Перейти на следующую вкладку
    void goNextTab();

    /// Перейти на предыдущую вкладку
    void goPrevTab();

    /// Добавить вкладку
    void addTab(SimpleTab* tab, QString mapKey = QString(""));

    /// Обновить вкладку
//    void updateTab(QString tabName, panel_diagnostic_t *data);
//    template<typename T>
//    void updateTab(QString tabName, screen_data_t* data);

    template<typename T>
    void updateTab(QString tabName, T data)
    {
        SimpleTab* tab = mapTabs_.value(tabName, Q_NULLPTR);

        if (tab)
        {
            tab->updateT(data);
        }
    }

    /// Вернуть имя текущей вкладки
    QString getCurrentTabName();


private:
    // Виджет контейнер всего
    QWidget* container_; ///< Виджет контейнер всего

    // Основа заголовка (рамка)
    QLabel* labelHead_; ///< Основа заголовка (рамка)

    // Стрелочка влево
    QLabel* labelBack_; ///< Стрелочка влево

    // Надпись предыдущая вкладка
    QLabel* labelPrev_; ///< Надпись предыдущая вкладка

    // Надпись текущая вкладка
    QLabel* labelName_; ///< Надпись текущая вкладка

    // Надпись следующая вкладка
    QLabel* labelNext_; ///< Надпись следующая вкладка

    // Стрелочка вправо
    QLabel* labelFrwd_; ///< Стрелочка вправо

    // Список вкладок
    QList<SimpleTab*> listTabs_; ///< Список вкладок

    // Карта вкладок
    QMap<QString, SimpleTab*> mapTabs_; ///< Карта вкладок

    // Указатель на текущую вкладку
    SimpleTab* currentTab_; ///< Указатель на текущую вкладку

    /// Выровнять заголовок
    void arrangeHead_();

    /// Соединить указатели вкладок
    void connectTabs_();

    /// Установить текущую вкладку
    void setCurrettab_(SimpleTab* otherTab);

    /*!
     * \enum ArrowDir
     * \brief Направление отрисовки стрелки
     */
    enum ArrowDir
    {
        adLEFT,
        adDOWN,
        adRIGHT,
        adUP
    };

    /// Отрисовать линии шапки заголовка
    void drawHead_();

    /// Отрисовать стрелочку
    void drawArrowImage_(QLabel* label, ArrowDir arrDir);

};

#endif // SIMPLETABCONTROL_H
