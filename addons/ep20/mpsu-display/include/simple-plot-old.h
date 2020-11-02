//-----------------------------------------------------------------------------
// KILL
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс обычного графика
 *  \copyright РГУПС, ВЖД
 *  \author Ковшиков С. В.
 *  \date 04/04/2017
 */

#ifndef SIMPLEPLOT_OLD_H
#define SIMPLEPLOT_OLD_H


//#include <QWidget>

//class QLabel;
//class SimpleBarOld;

///*!
// * \class SimplePlot
// * \brief Класс простого графика с гистограммой
// */
//class SimplePlotOld : public QWidget
//{
//    Q_OBJECT

//public:
//    /*!
//     * \brief Конструктор
//     * \param header - текст заголовка
//     * \param dimension - текст единиц измерения
//     */
//    SimplePlotOld(QString header, QString dimension, QWidget* parent = Q_NULLPTR);
//    /// Деструктор
//    ~SimplePlotOld();

//    /// Метод прикрепления гистограммы на график
//    void attachItem(SimpleBarOld* item);

//    /// Установка расстояния межу гистограммами
//    void setPadding(int padding);

//    /// Установка диапазона шкалы
//    void setRange(double min, double max);

//    // Получение диапазона шкалы
//    double getRange(); // ??? delete ??? move to abstract ???

//    /// Установить размер старшего шага
//    void setMajorStep(int step);

//    /// Установить размер младшего шага
//    void setMinorLength(int length);

//    /// Установка заголовка
//    void setTitle(QString tit);

//    /// Установка единиц измерения
//    void setDimension(QString dimension);

//    /// Перестройка графика
//    void replot();


//private:
//    // Мин./Макс. границы графика
//    double  min_; ///< Минимальная граница
//    double  max_; ///< Максимальная граница

//    int majorStep_; ///< Деления между мажорными линиями

//    int minorLength_; ///< Длина минорной линии

//    // Коэффициент преобразования реальных значения в пиксельные
//    double  coeff_; ///< Коэффициент преобразования (real to pix)

//    // Расстояние между гистограммами
//    int     padding_;  ///< Расстояние между гистограммами

//    QString dimension_; ///< Единицы измерения

//    // Заголовок графика
//    QLabel* labelHeader_; ///< Заголовок графика

//    // Холст со шкалой
//    QLabel* labelGrid_; ///< Холст со шкалой

//    // Значение + размерность графика.
//    QLabel* labelFooter_; ///< Значение + размерность

//    // Список гистограмм
//    QList<SimpleBarOld*> listItems_; // delete ??? move to abstract ???

//    /// Метод упорядочивания дочерних виджетов
//    void arrangeChildren_();

//    /// Метод генерации шкалы графика
//    void generateGrid_(QLabel* &lab, double min, double max);

//    /// Метод расчёта цены деления
//    double calculateStep(double min, double max);
//};

#endif // SIMPLEPLOT_OLD_H
