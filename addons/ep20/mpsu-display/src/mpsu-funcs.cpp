#include    "mpsu-funcs.h"

QString getConfPath(QString conf_name)
{
    return QDir::separator() + QString("MPSU") + QDir::separator() + conf_name;
}

