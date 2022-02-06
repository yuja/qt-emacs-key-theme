#include "emacskeytheme.h"
#include "emacskeythemeplugin.h"

EmacsKeyThemePlugin::EmacsKeyThemePlugin(QObject *parent) : QPlatformThemePlugin(parent) { }

QPlatformTheme *EmacsKeyThemePlugin::create(const QString &key, const QStringList & /*paramList*/)
{
    if (key.compare(QLatin1String("emacskey"), Qt::CaseInsensitive) != 0)
        return nullptr;
    return new EmacsKeyTheme;
}
