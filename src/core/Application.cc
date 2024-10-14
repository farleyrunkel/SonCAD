// Copyright [2024] SonCAD

#include "core/Application.h"

#include <QTranslator>
#include <QLocale>
#include <QStringList>

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "SonCAD_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            installTranslator(&translator);
            break;
        }
    }
}
