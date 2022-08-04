#include <QIcon>
#include <QKeySequence>
#include <QList>
#include <QPixmap>
#include <QVariant>
#include "proxytheme.h"

ProxyTheme::ProxyTheme(std::unique_ptr<QPlatformTheme> baseTheme) : baseTheme_(std::move(baseTheme))
{
}

ProxyTheme::~ProxyTheme() = default;

QPlatformMenuItem *ProxyTheme::createPlatformMenuItem() const
{
    return baseTheme_ ? baseTheme_->createPlatformMenuItem()
                      : QPlatformTheme::createPlatformMenuItem();
}

QPlatformMenu *ProxyTheme::createPlatformMenu() const
{
    return baseTheme_ ? baseTheme_->createPlatformMenu() : QPlatformTheme::createPlatformMenu();
}

QPlatformMenuBar *ProxyTheme::createPlatformMenuBar() const
{
    return baseTheme_ ? baseTheme_->createPlatformMenuBar()
                      : QPlatformTheme::createPlatformMenuBar();
}

void ProxyTheme::showPlatformMenuBar()
{
    baseTheme_ ? baseTheme_->createPlatformMenuItem() : QPlatformTheme::createPlatformMenuItem();
}

bool ProxyTheme::usePlatformNativeDialog(DialogType type) const
{
    return baseTheme_ ? baseTheme_->usePlatformNativeDialog(type)
                      : QPlatformTheme::usePlatformNativeDialog(type);
}

QPlatformDialogHelper *ProxyTheme::createPlatformDialogHelper(DialogType type) const
{
    return baseTheme_ ? baseTheme_->createPlatformDialogHelper(type)
                      : QPlatformTheme::createPlatformDialogHelper(type);
}

QPlatformSystemTrayIcon *ProxyTheme::createPlatformSystemTrayIcon() const
{
    return baseTheme_ ? baseTheme_->createPlatformSystemTrayIcon()
                      : QPlatformTheme::createPlatformSystemTrayIcon();
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 1)
auto ProxyTheme::appearance() const -> Appearance
{
    return baseTheme_ ? baseTheme_->appearance() : QPlatformTheme::appearance();
}
#endif

const QPalette *ProxyTheme::palette(Palette type) const
{
    return baseTheme_ ? baseTheme_->palette(type) : QPlatformTheme::palette(type);
}

const QFont *ProxyTheme::font(Font type) const
{
    return baseTheme_ ? baseTheme_->font(type) : QPlatformTheme::font(type);
}

QVariant ProxyTheme::themeHint(ThemeHint hint) const
{
    return baseTheme_ ? baseTheme_->themeHint(hint) : QPlatformTheme::themeHint(hint);
}

QPixmap ProxyTheme::standardPixmap(StandardPixmap sp, const QSizeF &size) const
{
    return baseTheme_ ? baseTheme_->standardPixmap(sp, size)
                      : QPlatformTheme::standardPixmap(sp, size);
}

QIcon ProxyTheme::fileIcon(const QFileInfo &fileInfo, IconOptions iconOptions) const
{
    return baseTheme_ ? baseTheme_->fileIcon(fileInfo, iconOptions)
                      : QPlatformTheme::fileIcon(fileInfo, iconOptions);
}

QIconEngine *ProxyTheme::createIconEngine(const QString &iconName) const
{
    return baseTheme_ ? baseTheme_->createIconEngine(iconName)
                      : QPlatformTheme::createIconEngine(iconName);
}

QList<QKeySequence> ProxyTheme::keyBindings(QKeySequence::StandardKey key) const
{
    return baseTheme_ ? baseTheme_->keyBindings(key) : QPlatformTheme::keyBindings(key);
}

QString ProxyTheme::standardButtonText(int button) const
{
    return baseTheme_ ? baseTheme_->standardButtonText(button)
                      : QPlatformTheme::standardButtonText(button);
}

QKeySequence ProxyTheme::standardButtonShortcut(int button) const
{
    return baseTheme_ ? baseTheme_->standardButtonShortcut(button)
                      : QPlatformTheme::standardButtonShortcut(button);
}
