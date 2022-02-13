#include <QAbstractItemView>
#include <QApplication>
#include <QCompleter>
#include <QKeyEvent>
#include <QKeySequence>
#include <QtDebug>
#include "emacskey.h"
#include "emacskeywidgethandler.h"

namespace {
inline bool isModifierKey(int key)
{
    // See QShortcutMap::nextState()
    switch (key) {
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_CapsLock:
    case Qt::Key_NumLock:
    case Qt::Key_ScrollLock:
        return true;
    case Qt::Key_unknown:
    default:
        return false;
    }
}

bool tryMoveCursor(QLineEdit *lineEdit, const QKeyEvent *ke, bool mark)
{
    Q_ASSERT(lineEdit);
    // See QWidgetLineControl::processKeyEvent()
    const int logicalDir = lineEdit->layoutDirection() == Qt::LeftToRight ? +1 : -1;
    const bool visual = lineEdit->cursorMoveStyle() == Qt::VisualMoveStyle;
    if (ke->matches(QKeySequence::MoveToNextChar)) {
        lineEdit->cursorForward(mark, visual ? 1 : logicalDir);
        return true;
    } else if (ke->matches(QKeySequence::MoveToPreviousChar)) {
        lineEdit->cursorBackward(mark, visual ? 1 : logicalDir);
        return true;
    } else if (ke->matches(QKeySequence::MoveToNextWord)) {
        if (lineEdit->echoMode() == QLineEdit::Normal) {
            logicalDir > 0 ? lineEdit->cursorWordForward(mark) : lineEdit->cursorWordBackward(mark);
        } else {
            logicalDir > 0 ? lineEdit->end(mark) : lineEdit->home(mark);
        }
        return true;
    } else if (ke->matches(QKeySequence::MoveToPreviousWord)) {
        if (lineEdit->echoMode() == QLineEdit::Normal) {
            logicalDir > 0 ? lineEdit->cursorWordBackward(mark) : lineEdit->cursorWordForward(mark);
        } else {
            logicalDir > 0 ? lineEdit->home(mark) : lineEdit->end(mark);
        }
        return true;
    } else if (ke->matches(QKeySequence::MoveToStartOfLine)
               || ke->matches(QKeySequence::MoveToStartOfBlock)) {
        lineEdit->home(mark);
        return true;
    } else if (ke->matches(QKeySequence::MoveToEndOfLine)
               || ke->matches(QKeySequence::MoveToEndOfBlock)) {
        lineEdit->end(mark);
        return true;
    }
    return false;
}
}

EmacsKeyWidgetHandler::EmacsKeyWidgetHandler(QObject *parent) : QObject(parent) { }

void EmacsKeyWidgetHandler::resetFocusWidget(QWidget *widget)
{
    if (focusLineEdit_) {
        focusLineEdit_->removeEventFilter(this);
        disconnect(focusLineEdit_, &QLineEdit::textChanged, this,
                   &EmacsKeyWidgetHandler::clearMark);
        focusLineEdit_ = nullptr;
    }
    if (focusCompleterPopup_) {
        focusCompleterPopup_->removeEventFilter(this);
        focusCompleterPopup_ = nullptr;
    }

    clearMark();

    if (auto *lineEdit = qobject_cast<QLineEdit *>(widget)) {
        focusLineEdit_ = lineEdit;
        focusLineEdit_->installEventFilter(this);
        connect(focusLineEdit_, &QLineEdit::textChanged, this, &EmacsKeyWidgetHandler::clearMark);
        // Since completer popup directly sends key events to the underlying line edit,
        // we need to intercept the popup events as well.
        if (lineEdit->completer() && lineEdit->completer()->popup()) {
            focusCompleterPopup_ = lineEdit->completer()->popup();
            focusCompleterPopup_->installEventFilter(this);
        }
        qCDebug(lcEmacsKey) << "focused line edit:" << focusLineEdit_ << focusCompleterPopup_;
    }
}

bool EmacsKeyWidgetHandler::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyPress: {
        const auto *ke = static_cast<QKeyEvent *>(event);
        if (isModifierKey(ke->key()))
            break;
        if (ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_H) {
            qCDebug(lcEmacsKey) << "C-h pressed in" << watched;
            if (focusLineEdit_ && !focusLineEdit_->isReadOnly()) {
                focusLineEdit_->backspace();
                return true;
            }
        } else if (ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_Space) {
            qCDebug(lcEmacsKey) << "C-SPC pressed in" << watched;
            if (focusLineEdit_) {
                if (focusCompleterPopup_) {
                    focusCompleterPopup_->hide();
                }
                focusLineEdit_->deselect();
                setMark(focusLineEdit_->cursorPosition());
                return true;
            }
        } else if (markPosition_ >= 0) {
            if (focusLineEdit_) {
                if (tryMoveCursor(focusLineEdit_, ke, /*mark=*/true))
                    return true;
            }
        }
        clearMark();
        break;
    }
    case QEvent::ShortcutOverride: {
        auto *ke = static_cast<QKeyEvent *>(event);
        if (ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_H) {
            qCDebug(lcEmacsKey) << "C-h override in" << watched;
            if (focusLineEdit_ && !focusLineEdit_->isReadOnly()) {
                event->accept();
                return true;
            }
        } else if (ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_Space) {
            qCDebug(lcEmacsKey) << "C-SPC override in" << watched;
            if (focusLineEdit_) {
                event->accept();
                return true;
            }
        }
        break;
    }
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}

void EmacsKeyWidgetHandler::clearMark()
{
    if (markPosition_ < 0)
        return;
    markPosition_ = -1;
    qCDebug(lcEmacsKey) << "mark cleared";
}

void EmacsKeyWidgetHandler::setMark(int position)
{
    if (markPosition_ == position)
        return clearMark();
    markPosition_ = position;
    qCDebug(lcEmacsKey) << "mark set to" << position;
}
