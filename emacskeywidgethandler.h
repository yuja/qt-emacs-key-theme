#ifndef EMACSKEYWIDGETHANDLER_H
#define EMACSKEYWIDGETHANDLER_H

#include <QLineEdit>
#include <QObject>
#include <QPointer>
#include <QWidget>

class EmacsKeyWidgetHandler : public QObject
{
    Q_OBJECT

public:
    explicit EmacsKeyWidgetHandler(QObject *parent = nullptr);
    void resetFocusWidget(QWidget *widget);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private Q_SLOTS:
    void clearMark();

private:
    void setMark(int position);

    QPointer<QLineEdit> focusLineEdit_ = nullptr;
    QPointer<QWidget> focusCompleterPopup_ = nullptr;
    int markPosition_ = -1;
};

#endif // EMACSKEYWIDGETHANDLER_H
