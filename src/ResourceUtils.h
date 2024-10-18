// ResourceUtils.h
#ifndef SRC_RESOURCEUTILS_H_
#define SRC_RESOURCEUTILS_H_

#include <QString>
#include <QIcon>

class ResourceUtils {
 public:
    static constexpr const char* ICON_PATH_PREFIX = "://icons/";

    static constexpr const char* MODEL_BOX = "model/Prim-Box";
    static constexpr const char* MODEL_CYLINDER = "model/Prim-Cylinder";
    static constexpr const char* MODEL_SPHERE = "model/Prim-Sphere";

    static QString iconPath(const QString& iconName) {
        return QString("%1%2.svg").arg(ICON_PATH_PREFIX, iconName);
    }

    static QIcon icon(const QString& iconName) {
        return QIcon(iconPath(iconName));
    }
};

#endif // SRC_RESOURCEUTILS_H_
