#ifndef DISPLAY_SHARED_DATA_H
#define DISPLAY_SHARED_DATA_H

#include <QStringList>

namespace Elements
{
    /*!
     * \brief Перечислитель типов состояния элемента
     */
    enum IconType{
        itNONE = 0,
        itNORMAL = 1,     ///< Норма
        itMESSAGE = 2,    ///< Сообщение
        itREPAIR = 3,     ///< ТО
        itWARNING = 4,    ///< Сбой или ошибка. Ограничения в эксплуатации
        itERROR = 5,      ///< Сбой или ошибка. Немедленные действия
        itDISCONNECT = 6, ///< Сбой связи
        itMAXIMUM         ///< ИНДИКАТОР ПРЕДЕЛЬНОГО ЗНАЧЕНИЯ. НЕ ИСПОЛЬЗОВАТЬ!
    };
}

namespace ConditionLine
{
    /// Количество ячеек строки событий
    constexpr int IMAGED_CELLS = 12;

    /// Массив индексов картинок для строки событий
    typedef quint8 CellsIndexes[IMAGED_CELLS];

    /*!
     * \brief Перечислитель индексов ячеек строки событий
     */
    enum CellNumber
    {
        CN_1,
        CN_2,
        CN_3,
        CN_4,
        CN_5,
        CN_6,
        CN_7,
        CN_8,
        CN_9,
        CN_10,
        CN_11,
        CN_12,
    };

    /*!
     * \brief Перечислитель значков строки событий
     */
    enum Cells{
        CELL_EMPTY,                     ///< Пустой значок "чёрный"
        C1_MOON,                        ///< Отстой во вкл. сост. активен
        C2_ALL_PANTOGRAPHS_OFF,         ///< Токоприёмники опущены

        C3_NOT_ALL_GVBV_ON,             ///< Не все ГВ включены
        C3_ALL_GVBV_OFF,                ///< Все ГВ выключены

        C4_NOT_ALL_PSN_ON,              ///< Не все ПСН включены
        C4_ALL_PSN_OFF,                 ///< Все ПСН выключены

        C5_DISTANT_LIGHT,               ///< Дальний свет Вкл
        C6_BRAKE_CONTROLLER_BLOCKED,    ///< КМ ТормУ заблокирован
        C7_CAN_CHANGE_REVERSOR,         ///< Смена кабины машиниста возможна
        C8_STOP_CRANE,                  ///< Стоп-кран
        C9_NOT_ALL_DOORS_CLOSED,        ///< Хотя бы 1 дверь открыта
        C10_DOORS_CONNECTION_FAIL,      ///< Сбой связи с дверьми
        C11_FIRE,                       ///< Пожар
        C12_MAIN_DOOR_DEBLOCKED         ///< Деблок. двери МП для выхода
    };

    /// Список имён файлов изображений для ячеек
    const QStringList allCells{"moon.svg",
                               "pantograph.svg",
                               "not-all-gvbv-on.svg",
                               "all-gvbv-off.svg",
                               "not-all-psn-on.svg",
                               "all-psn-off.svg",
                               "distant-light.svg",
                               "brake-controller-blocked.svg",
                               "can-change-reversor.svg",
                               "stop-crane.svg",
                               "not-all-doors-closed.svg",
                               "doors-connection-fail.svg",
                               "fire.svg",
                               "main-door-deblocked.svg"};
}

#endif // DISPLAY_SHARED_DATA_H
