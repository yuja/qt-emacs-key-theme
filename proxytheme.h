#ifndef PROXYTHEME_H
#define PROXYTHEME_H

#include <memory>
#include <qpa/qplatformtheme.h>

class ProxyTheme : public QPlatformTheme
{
public:
    explicit ProxyTheme(std::unique_ptr<QPlatformTheme> baseTheme);
    ~ProxyTheme() override;
    ProxyTheme(const ProxyTheme &) = delete;
    ProxyTheme &operator=(const ProxyTheme &) = delete;

    QPlatformMenuItem *createPlatformMenuItem() const override;
    QPlatformMenu *createPlatformMenu() const override;
    QPlatformMenuBar *createPlatformMenuBar() const override;
    void showPlatformMenuBar() override;

    bool usePlatformNativeDialog(DialogType type) const override;
    QPlatformDialogHelper *createPlatformDialogHelper(DialogType type) const override;

    QPlatformSystemTrayIcon *createPlatformSystemTrayIcon() const override;

    const QPalette *palette(Palette type) const override;

    const QFont *font(Font type) const override;

    QVariant themeHint(ThemeHint hint) const override;

    QPixmap standardPixmap(StandardPixmap sp, const QSizeF &size) const override;
    QIcon fileIcon(const QFileInfo &fileInfo, IconOptions iconOptions) const override;
    QIconEngine *createIconEngine(const QString &iconName) const override;

    QList<QKeySequence> keyBindings(QKeySequence::StandardKey key) const override;

    QString standardButtonText(int button) const override;
    QKeySequence standardButtonShortcut(int button) const override;

private:
    std::unique_ptr<QPlatformTheme> baseTheme_;
};

#endif // PROXYTHEME_H
