#include "emacskeythemeplugin.h"

EmacsKeyThemePlugin::EmacsKeyThemePlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *EmacsKeyThemePlugin::create(const QString &name, const QString &spec)
{
    static_assert(false, "You need to implement this function");
}
