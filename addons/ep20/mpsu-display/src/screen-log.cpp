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


#include "screen-log.h"

#include "static-display-data.h"

#include <QLabel>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QChar>



namespace LogType
{
    // База стиля строки
    const QString BASE = "font-family: \'Arial\';"
                         "font-size: 16px;"
                         "color:";

    // Конечные стили в зависимости от типа строки
    const QString NONE(BASE + "#ffffff;");
    const QString OK(BASE + "#00ff00;");
    const QString WARN(BASE + "#ffff00;");
    const QString ERR(BASE + "#ff0000;");
    const QString HEAD(BASE + "#00ffff; background: #000066;");
}


namespace
{
    // Маленький и большой шаги листания лога
    constexpr quint16 SMALL_STEP = 5;
    constexpr quint16 LARGE_STEP = 10;

    // Карта цветов в зависимости от типа строки
    const QMap<QString, QString> colorMap = {{QString("OK:"), LogType::OK},
                                             {QString("WAR"), LogType::WARN},
                                             {QString("ERR"), LogType::ERR},
                                             {QString("!--"), LogType::HEAD}};

    // Смещение вверх на step
    auto goUp = [](quint16 &curLn, quint16 step)
    {
        if (curLn >= step)
            curLn -= step;
        else
            curLn = 0u;
    };

    // Смещение вниз на step
    auto goDown = [](quint16 &curLn, quint16 step, quint16 cap)
    {
        if (curLn < cap - step)
            curLn += step;
        else
            curLn = cap;
    };
}


//-----------------------------------------------------------------------------
// Конструктор
//-----------------------------------------------------------------------------
ScreenLog::ScreenLog(QString scrName, QRect scrGeo, QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
    , lastLogLine_(0u)
    , logsCount_(0u)
    , labelsCount_(0u)
    , countsDiff_(0u)
    , currentLine_(0u)
    , logUpdateCounter_(0u)
{
    this->setVisible(false);

    buttonsNames_[0] = "Диагн.\nэкран";
    buttonsNames_[9] = "Основн.\nэкран";

    createAllChildren_();
}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
ScreenLog::~ScreenLog()
{

}



//-----------------------------------------------------------------------------
// Подготовить экран и вывести лог
//-----------------------------------------------------------------------------
void ScreenLog::prepareLogScreen()
{
    searchLastLog();

    loadLastLog();

    showLastLog(currentLine_);
}



//-----------------------------------------------------------------------------
// Сброс экрана при разрыве связи с сервером
//-----------------------------------------------------------------------------
void ScreenLog::resetOnDisconnect()
{
    logUpdateCounter_ = 0;
    currentLine_ = 0;
    logsCount_ = 0;
    countsDiff_ = 0;
    listLogs_.clear();
}



//-----------------------------------------------------------------------------
// Обработка нажатия кнопки
//-----------------------------------------------------------------------------
void ScreenLog::receiveOtherButton(Local::ButtonId id)
{
    if (logsCount_ <= labelsCount_)
        return;

    switch (id)
    {
    case Local::biUP:
        goUp(currentLine_, SMALL_STEP);
        break;

    case Local::biDOWN:
        goDown(currentLine_, SMALL_STEP, countsDiff_);
        break;

    case Local::biLEFT:
        goUp(currentLine_, LARGE_STEP);
        break;

    case Local::biRIGHT:
        goDown(currentLine_, LARGE_STEP, countsDiff_);
        break;

    case Local::biCORRECTION:
        currentLine_ = 0u;
        break;

    case Local::biINPUT:
        currentLine_ = countsDiff_;
        break;

    default:
        break;
    }

    showLastLog(currentLine_);
}



//-----------------------------------------------------------------------------
// Обновление данных экрана
//-----------------------------------------------------------------------------
void ScreenLog::updateScreen(screen_data_t *data)
{
    Q_UNUSED(data)
    ++logUpdateCounter_;
    if (logUpdateCounter_ == 5)
    {
        logsCount_ = 0;
        countsDiff_ = 0;
        listLogs_.clear();
        loadLastLog();
        showLastLog(currentLine_);
    }
    else if (logUpdateCounter_ == 50)
    {
        logUpdateCounter_ = 0;
    }
}



//-----------------------------------------------------------------------------
// Поиск номера строки последнего сеанса лога
//-----------------------------------------------------------------------------
void ScreenLog::searchLastLog()
{
    QFile f(QDir().absoluteFilePath(StaticData::LOG_PATH));

    if (!f.open(QIODevice::ReadOnly))
        return;

    QTextStream s(&f);

    quint64 lineNumber = 0;

    while (!s.atEnd())
    {
        if (s.readLine().startsWith("-"))
        {
            lastLogLine_ = lineNumber;
        }
        ++lineNumber;
    }

    if (lastLogLine_ <= 4)
    {
        lastLogLine_ = 0;
    }
    else
    {
        lastLogLine_ -= 4;
    }

    f.close();
}



//-----------------------------------------------------------------------------
// Загрузка последнего сеанса лога
//-----------------------------------------------------------------------------
void ScreenLog::loadLastLog()
{
    QFile f(QDir().absoluteFilePath(StaticData::LOG_PATH));

    clearLog_();

    if (!f.open(QIODevice::ReadOnly))
        return;

    QTextStream s(&f);

    quint64 i = 0;
    while (!s.atEnd() && i < lastLogLine_)
    {
        s.readLine();
        ++i;
    }

    while (!s.atEnd())
    {
        listLogs_.append(s.readLine());
    }

    logsCount_ = listLogs_.count();

    if (logsCount_ > labelsCount_)
        countsDiff_ = logsCount_ - labelsCount_;

    f.close();
}



//-----------------------------------------------------------------------------
// Показать последний сеанс лога с pos строки
//-----------------------------------------------------------------------------
void ScreenLog::showLastLog(quint16 pos)
{
    QString labText("");


    for (quint16 i = 0; i < std::min(labelsCount_, logsCount_); ++i)
    {
        if (i + pos > logsCount_ - 1)
            return;

        QLabel* label = listLabels_[i];

        labText = listLogs_[i + pos];

        label->setStyleSheet(colorMap.value(labText.left(3), LogType::NONE));

        label->setText(labText);
    }
}

void ScreenLog::clearLog_()
{
    for (QLabel* lab : listLabels_)
    {
        lab->setStyleSheet(LogType::NONE);
        lab->setText(" -   -   -   -   -   -   - ");
    }
}



//-----------------------------------------------------------------------------
// Создать все дочерние виджеты
//-----------------------------------------------------------------------------
void ScreenLog::createAllChildren_()
{
    int leftPad = 10;
    int topPad = 16;
    int labPad = 5;
    int labH = 0;
    int curLabY = topPad;

    while ( (curLabY + labH) < this->height() )
    {
        QLabel* label = new QLabel(" -   -   -   -   -   -   - ", this);
        label->setStyleSheet(LogType::NONE);
        label->adjustSize();
        label->resize(this->width() - leftPad*2, label->height());
        label->move(leftPad, curLabY);
        labH = label->height();
        listLabels_.append(label);
        curLabY += (labPad + labH);
    }

    labelsCount_ = listLabels_.count();
}
