// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_IHUDMANAGER_H_
#define IACT_HUD_ELEMENTS_IHUDMANAGER_H_

#include <QString>
#include <QPointer>
#include <QWidget>
#include <functional>

#include "Comm/BaseObject.h"

class IHudElement;

DEFINE_STANDARD_HANDLE(HudManager, BaseObject)

class HudManager : public BaseObject
{
public:
	HudManager() = default;

    ~HudManager() = default;

    void AddElement(IHudElement* element) {}
    void RemoveElement(IHudElement* element) {}
    void RemoveElements(std::function<bool(IHudElement*)> predicate) {}

    // virtual void SetCursor(QObject* owner, Cursor* cursor) = 0;
    void SetHintMessage(const QString& message) {}
};

#endif  // IACT_HUD_ELEMENTS_IHUDMANAGER_H_
