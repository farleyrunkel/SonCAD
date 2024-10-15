// Copyright [2024] SonCAD

#include "App/Application.h"

#include <QTranslator>
#include <QLocale>
#include <QStringList>
#include <iostream>

#include "App/CommandLine.h"
#include "App/MainWindow.h"
#include "App/WelcomeDialog.h"

#include "Pres/GlobalEventHandler.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv),
    mSharedMemory(mMutexName), // Initialize shared memory with mutex name
    mSemaphore(1)
{
    // ÉèÖÃ·­Òë
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "SonCAD_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            installTranslator(&translator);
            break;
        }
    }

    CommandLine cmdLine(argc, argv);

    // Show Welcome Dialog while initializing
    bool bSkipWelcome = cmdLine.isWelcomeDialogDisabled() || cmdLine.hasPathToOpen() || cmdLine.hasScriptToRun();
    if (!bSkipWelcome)
    {
        mWelcomeDialog = new WelcomeDialog;
        mWelcomeDialog->setWindowFlags(mWelcomeDialog->windowFlags() | Qt::WindowStaysOnTopHint);
        mWelcomeDialog->show();
    }

    mMainWindow = new MainWindow;
    mMainWindow->show();

    // Additional initialization can go here
    InitializeSynchronization();

    // Install the event filter for global key handling
    GlobalEventHandler* globalEventHandler = new GlobalEventHandler(this);
    this->installEventFilter(globalEventHandler);
}

// Initialize synchronization mechanisms
void Application::InitializeSynchronization() {
    // Implement mutex handling logic
    if (mSharedMemory.attach()) {
        // An instance is already running
        qDebug() << "Another instance is already running.";
        exit(0);
    }

    if (!mSharedMemory.create(1)) {
        qDebug() << "Could not create shared memory:" << mSharedMemory.errorString();
        exit(1);
    }
}
