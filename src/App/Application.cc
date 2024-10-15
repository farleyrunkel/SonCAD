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
    mSharedMemory(mMutexName),
    mSystemSemaphore(mMutexName, 1) {
    initializeSynchronization(); // Set up synchronization
    initializeTranslation();

    CommandLine cmdLine(argc, argv);

    // Show Welcome Dialog if not skipped
    bool bSkipWelcome = cmdLine.isWelcomeDialogDisabled() || cmdLine.hasPathToOpen() || cmdLine.hasScriptToRun();
    if (!bSkipWelcome) {
        mWelcomeDialog = new WelcomeDialog; // Create the WelcomeDialog
        mWelcomeDialog->setWindowFlags(mWelcomeDialog->windowFlags() | Qt::WindowStaysOnTopHint); // Keep it on top
        mWelcomeDialog->show(); // Show the WelcomeDialog
    }

    mMainWindow = new MainWindow; // Create the main window
    mMainWindow->show(); // Show the main window

    // Install the event filter for global key handling
    GlobalEventHandler* globalEventHandler = new GlobalEventHandler(this);
    this->installEventFilter(globalEventHandler); // Install the event filter
}

// Initialize synchronization mechanisms
void Application::initializeTranslation() {
    // Set up translator for localization
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "SonCAD_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            installTranslator(&translator); // Install the translator
            break; // Exit loop after loading the first valid translation
        }
    }
}

// Initialize synchronization mechanisms
void Application::initializeSynchronization() {
    // Try to acquire the semaphore
    mSystemSemaphore.acquire();

    // Try to attach to existing shared memory
    if (mSharedMemory.attach()) {
        // If successful, another instance is running
        qDebug() << "Warning" << "Another instance is already running."; // Output warning message
        exit(0); // Exit the application
    }

    // Try to create shared memory
    if (!mSharedMemory.create(1)) {
        // If creation fails, output the error message
        qDebug() << "Could not create shared memory:" << mSharedMemory.errorString(); // Output error message
        exit(1); // Exit the application
    }

    // Release the semaphore
    mSystemSemaphore.release(); // Release the semaphore
}
