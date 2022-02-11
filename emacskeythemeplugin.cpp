#include <QApplication>
#include <QStringList>
#include <QtDebug>
#include <memory>
#include <private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>
#include <qpa/qplatformthemefactory_p.h>
#include "emacskey.h"
#include "emacskeytheme.h"
#include "emacskeythemeplugin.h"
#include "emacskeywidgethandler.h"

Q_LOGGING_CATEGORY(lcEmacsKey, "qt.qpa.emacskey")

namespace {
// extracted from init_platform()
std::unique_ptr<QPlatformTheme> lookupTheme(const QStringList &themeNames)
{
    for (const auto &name : themeNames) {
        if (auto *p = QPlatformThemeFactory::create(name))
            return std::unique_ptr<QPlatformTheme>(p);
    }

    for (const auto &name : themeNames) {
        if (auto *p = QGuiApplicationPrivate::platform_integration->createPlatformTheme(name))
            return std::unique_ptr<QPlatformTheme>(p);
    }

    return {};
}
}

EmacsKeyThemePlugin::EmacsKeyThemePlugin(QObject *parent) : QPlatformThemePlugin(parent) { }

QPlatformTheme *EmacsKeyThemePlugin::create(const QString &key, const QStringList &paramList)
{
    if (key.compare(QLatin1String("emacskey"), Qt::CaseInsensitive) != 0)
        return nullptr;

    // TODO: who should set up the global event filter object?
    if (auto *app = qobject_cast<QApplication *>(QCoreApplication::instance())) {
        auto *handler = new EmacsKeyWidgetHandler(app);
        QObject::connect(app, &QApplication::focusChanged, handler,
                         [handler](QWidget *, QWidget *now) { handler->resetFocusWidget(now); });
    }

    QStringList baseThemeNames;
    for (int i = 0; i < paramList.size(); ++i) {
        const QString &param = paramList.at(i);
        if (param.startsWith("base=")) {
            QStringList args { param.mid(5) };
            args.append(paramList.mid(i + 1)); // consume remainder as base parameters
            baseThemeNames.push_back(args.join(':'));
            break;
        } else {
            qCWarning(lcEmacsKey) << "unknown theme parameter:" << param;
        }
    }
    baseThemeNames.append(QGuiApplicationPrivate::platform_integration->themeNames());

    return new EmacsKeyTheme(lookupTheme(baseThemeNames));
}
