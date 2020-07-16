#ifndef ACONSTS_H
#define ACONSTS_H

#include <QStringList>
#include <qglobal.h>


namespace Local
{
    /*!
     * \enum ButtonId
     * \brief ButtonId enum - уникальные коды всех "физических" кнопок
     */
    enum ButtonId
    {
        biDIGIT1,           // Кнопка 1
        biDIGIT2,           // Кнопка 2
        biDIGIT3,           // Кнопка 3
        biDIGIT4,           // Кнопка 4
        biDIGIT5,           // Кнопка 5
        biDIGIT6,           // Кнопка 6
        biDIGIT7,           // Кнопка 7
        biDIGIT8,           // Кнопка 8
        biDIGIT9,           // Кнопка 9
        biDIGIT0,           // Кнопка 0
        biOTM,
        biF1,
        biF2,
        biF3,
        biF4,
        biF5,
        biMINUS,
        biPLUS,
        biSTAR,
        biCORRECTION,       // Кнопка коррекция
        biLEFT,             // Кнопка влево
        biRIGHT,            // Кнопка вправо
        biUP,               // Кнопка вверх
        biDOWN,             // Кнопка вниз
        biINPUT,            // Кнопка ввод
        biNULL_ID           // Пустышка
    };



    /*!
     * \brief FootboardSide enum - перечислитель позиций подножки ступеней
     */
    enum FootboardSide{
        fsTOP,
        fsBOT
    };



    /*!
     * \brief cmd_option_display_t - структура параметров командной строки
     */
    template <typename T>
    struct cmd_option_display_t
    {
        T value;
        bool is_present;

        cmd_option_display_t()
            : is_present(false)
        {

        }
    };



    /*!
     * \brief cmd_line_display_t - структура параметров командной строки
     */
    struct cmd_line_display_t
    {
        cmd_option_display_t<QString> cfgFileName;

        cmd_line_display_t()
        {
            cfgFileName.value.clear();
        }
    };

}

#endif // ACONSTS_H

