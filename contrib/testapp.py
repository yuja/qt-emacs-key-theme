import sys
from PyQt5.QtWidgets import (
    QApplication,
    QCompleter,
    QDialog,
    QLineEdit,
    QPlainTextEdit,
    QVBoxLayout,
)


def main():
    app = QApplication(sys.argv)
    dialog = QDialog()
    layout = QVBoxLayout(dialog)
    textEdit = QPlainTextEdit()
    lineEdit = QLineEdit()
    lineEdit.setCompleter(QCompleter(["foo", "bar", "baz", "qux", "quux"]))
    layout.addWidget(textEdit)
    layout.addWidget(lineEdit)
    dialog.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
