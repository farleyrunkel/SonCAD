// Copyright [2024] SunCAD

#ifndef SRC_CORE_APP_H_
#define SRC_CORE_APP_H_

#include "App/Application.h"

class Core {
public:
     static Sun::Application* application() noexcept {
         return static_cast<Sun::Application*>(Sun::Application::instance());
     }

     static CommandManager* commandManager() noexcept {
         return application()->m_commandManager;
     }

     static Sun::AppContext* appContext() noexcept {
         return application()->m_appContext;
     }

     static Sun::MainWindow* mainWindow() noexcept {
         return application()->m_mainWindow;
     }
};

#endif  // SRC_CORE_APP_H_
