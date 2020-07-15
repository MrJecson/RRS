//-----------------------------------------------------------------------------
//
//      Класс простой вкладки
//      (c) РГУПС, ВЖД 11/10/2017
//      Разработал: Ковшиков С. В.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс простой вкладки
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 11/10/2017
 */

#ifndef SIMPLETAB_H
#define SIMPLETAB_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QPair>

class QWidget;
class QLabel;
//class ElementIndicator;
#include "element-indicator.h"
#include "display-shared-data.h"

//struct panel_diagnostic_t;

struct screen_data_t;


/*!
 * \class SimpleTab
 * \brief Класс имитации вкладки
 */
class SimpleTab
{
public:
    /// Конструктор
    SimpleTab(QString tabName, QWidget* container);
    /// Деструктор
    ~SimpleTab();

    /*!
     * \enum FieldType enum
     * \brief Перечислитель типов
     */
    enum FieldType
    {
        ftBOX,
        ftFIELD_UINT,
        ftFIELD_INT
    };

    /// Добавить элемент нужного типа
    SimpleTab* addElement(QString name, FieldType type);

    /// Добавить список элементов
    void addElementsList(QList<QPair<QString, FieldType>> list);

    /// Добавить нижнюю строку
    void addFooter(QString str);

    /// Сделать вкладку видимой
    void setTabVisible(bool visible);

    /// Перейти на предыдущую вкладку
    SimpleTab* getPrevTab();

    /// Перейти на следующую вкладку
    SimpleTab* getNextTab();

    /// Установить предыдущую вкладку
    void setPrevTab(SimpleTab* prev);

    /// Устанвоить следующую вкладку
    void setNextTab(SimpleTab* next);

    /// Вернуть имя вкладки
    QString getTabName();

    /// Обновить данные вкладки
//    void updateTab(panel_diagnostic_t *data);
    template<typename T>
    void updateT(T data)
    {
    //    T* tmp = static_cast<T*>(data);
        for (int i = 0, n = listBoxes_.count(); i < n; ++i)
        {
            listBoxes_[i]->updateElement(data->flags[i],
                                         data->flags[i],
                                         Elements::itNORMAL);
        }

        for (int i = 0, n = listFieldsUint_.count(); i < n; ++i)
        {
            listFieldsUint_[i]->setText(QString::number(data->uintFields[i]));
        }

        for (int i = 0, n = listFieldsInt_.count(); i < n; ++i)
        {
            listFieldsInt_[i]->setText(QString::number(data->intFields[i]));
        }
    }


private:
    // Виджет контейнер
    QWidget* container_; ///< Виджет контейнер

    // Имя вкладки
    QString tabName_; ///< Имя вкладки

    // Флаг видимости
    bool isVisible_; ///< Флаг видимости

    // Указатель на предыдущую вкладку
    SimpleTab* prevTab_; ///< Указатель на предыдущую вкладку

    // Указатель на следующую вкладку
    SimpleTab* nextTab_; ///< Указатель на следующую вкладку

    // Список надписей
    QList<QLabel*> listLabels_; ///< Список надписей

    // Список чек-боксов
    QList<ElementIndicator*> listBoxes_; ///< Список чек-боксов

    // Список полей беззнаковых значений
    QList<QLabel*> listFieldsUint_; ///< Список полей беззнаковых значений

    // Список полей знаковых значений
    QList<QLabel*> listFieldsInt_; ///< Список полей знаковых значений

    // Список всех видимых элементов
    QList<QLabel*> listAllElements_; ///< Список всех видимых элементов

    /// Упорядочить все подконтрольные виджеты
    void arrangeAll_();
};

#endif // SIMPLETAB_H
