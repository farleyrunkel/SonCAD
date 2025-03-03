// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_IHUDMANAGER_H_
#define IACT_HUD_ELEMENTS_IHUDMANAGER_H_

#include <QString>
#include <QPointer>
#include <QWidget>
#include <functional>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

class HudElement;

DEFINE_STANDARD_HANDLE(HudManager, Standard_Transient)

class HudManager : public Standard_Transient
{
public:
    virtual ~HudManager() = default;

    virtual void addElement(HudElement* element) = 0;
    virtual void removeElement(HudElement* element) = 0;
    virtual void removeElements(std::function<bool(HudElement*)> predicate) = 0;

    // virtual void SetCursor(QObject* owner, Cursor* cursor) = 0;
    virtual void setHintMessage(const QString& message) = 0;
};

#endif  // IACT_HUD_ELEMENTS_IHUDMANAGER_H_
