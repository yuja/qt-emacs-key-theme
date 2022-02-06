#include <QKeySequence>
#include <QList>
#include "emacskeytheme.h"

EmacsKeyTheme::EmacsKeyTheme(std::unique_ptr<QPlatformTheme> baseTheme)
    : ProxyTheme(std::move(baseTheme))
{
}

QList<QKeySequence> EmacsKeyTheme::keyBindings(QKeySequence::StandardKey key) const
{
    constexpr int CTRL = static_cast<int>(Qt::CTRL);
    constexpr int ALT = static_cast<int>(Qt::ALT);
    switch (key) {
    case QKeySequence::Open:
        return { { CTRL | Qt::Key_X, CTRL | Qt::Key_F } };
    case QKeySequence::Close:
        return { { CTRL | Qt::Key_X, Qt::Key_K } }; // TODO: or C-x 0?
    case QKeySequence::Save:
        return { { CTRL | Qt::Key_X, CTRL | Qt::Key_S } };
    case QKeySequence::Quit:
        return { { CTRL | Qt::Key_X, CTRL | Qt::Key_C } };
    case QKeySequence::New:
        return {};
    case QKeySequence::Delete:
        return { Qt::Key_Delete, CTRL | Qt::Key_D };
    case QKeySequence::Cut:
        return { CTRL | Qt::Key_W };
    case QKeySequence::Copy:
        return { ALT | Qt::Key_W };
    case QKeySequence::Paste:
        return { CTRL | Qt::Key_Y };
    case QKeySequence::Undo:
        return { CTRL | Qt::Key_Slash }; // TODO: more undo keys
    case QKeySequence::Redo:
        return {}; // TODO
    case QKeySequence::Print:
        return {}; // drop C-p
    case QKeySequence::Find:
        return {}; // TODO
    case QKeySequence::FindNext:
        return { CTRL | Qt::Key_S };
    case QKeySequence::FindPrevious:
        return { CTRL | Qt::Key_R };
    case QKeySequence::Replace:
        break; // TODO
    case QKeySequence::SelectAll:
        return { { CTRL | Qt::Key_X, Qt::Key_H } }; // won't work in text controls
    case QKeySequence::MoveToNextChar:
        return { Qt::Key_Right, CTRL | Qt::Key_F };
    case QKeySequence::MoveToPreviousChar:
        return { Qt::Key_Left, CTRL | Qt::Key_B };
    case QKeySequence::MoveToNextWord:
        return { CTRL | Qt::Key_Right, ALT | Qt::Key_F };
    case QKeySequence::MoveToPreviousWord:
        return { CTRL | Qt::Key_Left, ALT | Qt::Key_B };
    case QKeySequence::MoveToNextLine:
        return { Qt::Key_Down, CTRL | Qt::Key_N };
    case QKeySequence::MoveToPreviousLine:
        return { Qt::Key_Up, CTRL | Qt::Key_P };
    case QKeySequence::MoveToNextPage:
        return { Qt::Key_PageDown, CTRL | Qt::Key_V };
    case QKeySequence::MoveToPreviousPage:
        return { Qt::Key_PageUp, ALT | Qt::Key_V };
    case QKeySequence::MoveToStartOfLine:
        return { Qt::Key_Home, CTRL | Qt::Key_A };
    case QKeySequence::MoveToEndOfLine:
        return { Qt::Key_End, CTRL | Qt::Key_E };
    case QKeySequence::MoveToStartOfBlock:
        break; // TODO
    case QKeySequence::MoveToEndOfBlock:
        break; // TODO
    case QKeySequence::MoveToStartOfDocument:
        return { CTRL | Qt::Key_Home, ALT | Qt::SHIFT | Qt::Key_Less }; // TODO: M-<
    case QKeySequence::MoveToEndOfDocument:
        return { CTRL | Qt::Key_End, ALT | Qt::SHIFT | Qt::Key_Greater }; // TODO: M->
    case QKeySequence::DeleteEndOfLine:
        return { CTRL | Qt::Key_K };
    case QKeySequence::Backspace:
        return { CTRL | Qt::Key_H };
    case QKeySequence::Cancel:
        return { Qt::Key_Escape, { CTRL | Qt::Key_G } };
    default:
        break;
    }
    return ProxyTheme::keyBindings(key);
}
