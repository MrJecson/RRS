#ifndef MPSUDISPLAY_H
#define MPSUDISPLAY_H

#include    "display.h"
#include    "mpsu-funcs.h"
#include "structures-display.h"

#include "middle-block.h"
#include "top-block.h"
#include "bottom-block.h"
#include "right-block.h"
#include "left-block.h"


#include    <QPoint>
#include    <QTimer>

class MpsuDisplay: public AbstractDisplay
{

    Q_OBJECT

public:

    MpsuDisplay(QWidget *parent = Q_NULLPTR,
                Qt::WindowFlags f = Qt::WindowFlags());

    ~MpsuDisplay();

    void init() override;

private:

    QTimer  *updateTimer;

    void initMainWindow();

    void initMiddleBlock();

    void initTopBlock();


    /// Геометрия центрального виджета
    const QRect MIDDLE_BLOCK_GEO;
    /// Геометрия верхнего виджета
    const QRect TOP_BLOCK_GEO;
    /// Геометрия левого виджета
    const QRect LEFT_BLOCK_GEO;
    /// Геометрия правого виджета
    const QRect RIGHT_BLOCK_GEO;
    /// Геометрия нижнего виджета
    const QRect BOTTOM_BLOCK_GEO;

        // Экземпляр класса "Центральный блок"
        MiddleBlock*    middleBlock_; ///< Центральный блок

//        // Экземпляр класса "Верхний блок"
//        TopBlock*       topBlock_; ///< Верхний блок

//        // Экземпляр класса "Нижний блок"
//        BottomBlock*    bottomBlock_; ///< Нижний блок

//        // Экземпляр класса "Правый блок"
//        RightBlock*     rightBlock_; ///< Правый блок

//        // Экземпляр класса "Левый блок"
//        LeftBlock*      leftBlock_; ///< Левый блок

private slots:

    void slotUpdateTimer();

};

#endif // MPSUDISPLAY_H
