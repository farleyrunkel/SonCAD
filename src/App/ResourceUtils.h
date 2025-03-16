// ResourceUtils.h
#ifndef RESOURCEUTILS_H_
#define RESOURCEUTILS_H_

// Qt includes
#include <QString>
#include <QIcon>
#include <QFile>
#include <QImage>

class Resource
{
public:
    static constexpr const char* ICON_PATH_PREFIX = "://Icons/";
    static constexpr const char* MARKER_PATH_PREFIX = "://Marker/";

    static QString IconPath(const QString& iconName)
    {
        return QString("%1%2.svg").arg(ICON_PATH_PREFIX, iconName);
    }

    static QString MarkerPath(const QString& iconName)
    {
        return QString("%1%2.svg").arg(MARKER_PATH_PREFIX, iconName);
    }

    static QIcon Icon(const QString& iconName)
    {
        return QIcon(IconPath(iconName));
    }

    static QString GetResourceUri(const QString& filename)
    {
        return AssemblyName().append(filename);
    }

    static QImage ReadBitmapFromResource(const QString& filename)
    {
        return QImage(GetResourceUri(filename));
    }


public:
    static bool IsResourcePathValid(const QString& resourcePath)
    {
        QFile file(resourcePath);
        return file.exists();
    }

private:
    static QString AssemblyName()
    {
        return ":/";
    };
};

#endif // RESOURCEUTILS_H_
