#ifndef EMACSKEYTHEME_H
#define EMACSKEYTHEME_H

#include "proxytheme.h"

class EmacsKeyTheme : public ProxyTheme
{
public:
    explicit EmacsKeyTheme(std::unique_ptr<QPlatformTheme> baseTheme);
    EmacsKeyTheme(const EmacsKeyTheme &) = delete;
    EmacsKeyTheme &operator=(const EmacsKeyTheme &) = delete;

    QList<QKeySequence> keyBindings(QKeySequence::StandardKey key) const override;
};

#endif // EMACSKEYTHEME_H
