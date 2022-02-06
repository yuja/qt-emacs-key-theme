#ifndef EMACSKEYTHEME_H
#define EMACSKEYTHEME_H

#include <qpa/qplatformtheme.h>

class EmacsKeyTheme : public QPlatformTheme
{
public:
    EmacsKeyTheme();
    EmacsKeyTheme(const EmacsKeyTheme &) = delete;
    EmacsKeyTheme &operator=(const EmacsKeyTheme &) = delete;
};

#endif // EMACSKEYTHEME_H