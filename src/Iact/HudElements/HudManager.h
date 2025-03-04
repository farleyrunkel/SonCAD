// Copyright [2024] SunCAD

#ifndef IACT_HUD_ELEMENTS_IHUDMANAGER_H_
#define IACT_HUD_ELEMENTS_IHUDMANAGER_H_

#include <functional>
#include <string>

#include "Comm/BaseObject.h"

class HudElement;

class HudManager : public enable_property_changed_signal
{
public:
    virtual ~HudManager() = default;

    virtual void addElement(HudElement* element) = 0;
    virtual void removeElement(HudElement* element) = 0;
    virtual void removeElements(std::function<bool(HudElement*)> predicate) = 0;

    virtual void setHintMessage(const std::string& message) = 0;
};

#endif  // IACT_HUD_ELEMENTS_IHUDMANAGER_H_
