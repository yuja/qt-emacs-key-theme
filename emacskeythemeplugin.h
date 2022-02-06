#ifndef EMACSKEYTHEMEPLUGIN_H
#define EMACSKEYTHEMEPLUGIN_H

#include <qpa/qplatformthemeplugin.h>

class EmacsKeyThemePlugin : public QPlatformThemePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformThemeFactoryInterface_iid FILE "emacskeytheme.json")

public:
    explicit EmacsKeyThemePlugin(QObject *parent = nullptr);

private:
    QPlatformTheme *create(const QString &key, const QStringList &paramList) override;
};

#endif // EMACSKEYTHEMEPLUGIN_H
