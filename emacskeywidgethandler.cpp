#include <QAbstractItemView>
#include <QApplication>
#include <QCompleter>
#include <QKeyEvent>
#include <QtDebug>
#include "emacskey.h"
#include "emacskeywidgethandler.h"

EmacsKeyWidgetHandler::EmacsKeyWidgetHandler(QObject *parent) : QObject(parent) { }

void EmacsKeyWidgetHandler::resetFocusWidget(QWidget *widget)
{
    if (focusLineEdit_) {
        focusLineEdit_->removeEventFilter(this);
        focusLineEdit_ = nullptr;
    }
    if (focusCompleterPopup_) {
        focusCompleterPopup_->removeEventFilter(this);
        focusCompleterPopup_ = nullptr;
    }

    if (auto *lineEdit = qobject_cast<QLineEdit *>(widget)) {
        focusLineEdit_ = lineEdit;
        focusLineEdit_->installEventFilter(this);
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
        if (ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_H) {
            qCDebug(lcEmacsKey) << "C-h pressed in" << watched;
            if (focusLineEdit_ && !focusLineEdit_->isReadOnly()) {
                focusLineEdit_->backspace();
                return true;
            }
        }
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
        }
        break;
    }
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}
