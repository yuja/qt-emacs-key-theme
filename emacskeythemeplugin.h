#ifndef EMACSKEYTHEMEPLUGIN_H
#define EMACSKEYTHEMEPLUGIN_H

#include <QGenericPlugin>

class EmacsKeyThemePlugin : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid FILE "emacskeytheme.json")

public:
    explicit EmacsKeyThemePlugin(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // EMACSKEYTHEMEPLUGIN_H
