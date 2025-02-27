// ResourceUtils.h
#ifndef RESOURCEUTILS_H_
#define RESOURCEUTILS_H_

#include <QString>
#include <QIcon>
#include <QFile>
#include <QDebug>

class ResourceUtils 
{
public:
    static constexpr const char* ICON_PATH_PREFIX = "://icons/";

    static QString IconPath(const QString& iconName) 
    {
        return QString("%1%2.svg").arg(ICON_PATH_PREFIX, iconName);
    }

    static QIcon Icon(const QString& iconName) 
    {
        return QIcon(IconPath(iconName));
    }

 public:
    static bool IsResourcePathValid(const QString& resourcePath)
    {
        QFile file(resourcePath);
        return file.exists();
    }
};

#endif // RESOURCEUTILS_H_
