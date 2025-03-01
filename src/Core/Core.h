// Copyright [2024] SunCAD

#ifndef CORE_APP_H_
#define CORE_APP_H_

#include "App/Application.h"

class Core
{
public:
    static Application* GetApplication() noexcept
    {
        return static_cast<Application*>(Application::instance());
    }

    static MainWindow* GetMainWindow() noexcept
    {
        return GetApplication()->GetMainWindow();
    }

    static Handle(AppContext) GetAppContext() noexcept
    {
        return GetApplication()->GetAppContext();
    }

    //static CommandManager* commandManager() noexcept 
    //{
    //    return application()->m_commandManager;
    //}
};

#endif  // CORE_APP_H_
