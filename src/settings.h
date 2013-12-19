#pragma once

#include <QDialog>

#define FALLBACK_LANGUAGE "English"
#define DEFAULT_SHORTCUT "Ctrl+Shift+T"

class QSettings;
class QCheckBox;
class QComboBox;
class QKeySequenceEdit;
class QDialogButtonBox;

class Settings : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool shortcutEnabled READ shortcutEnabled)
    Q_PROPERTY(bool trayIconEnabled READ trayIconEnabled)
    Q_PROPERTY(QKeySequence shortcut READ shortcut)
    Q_PROPERTY(QString language READ language)
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    bool shortcutEnabled();
    bool trayIconEnabled();
    QKeySequence shortcut() const;
    QString language() const;
private slots:
    void accept();
private:
    QString detectSystemLanguage() const;

    QSettings *settings;
    QCheckBox *tray_checkbox;
    QCheckBox *shortcut_checkbox;
    QKeySequenceEdit *shortcut_edit;
    QComboBox *language_combobox;
    QDialogButtonBox *button_box;
};
