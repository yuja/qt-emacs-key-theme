#include "emacskeythemeplugin.h"

EmacsKeyThemePlugin::EmacsKeyThemePlugin(QObject *parent) : QPlatformThemePlugin(parent) { }

QPlatformTheme *EmacsKeyThemePlugin::create(const QString &key, const QStringList &paramList)
{
    static_assert(false, "You need to implement this function");
}
