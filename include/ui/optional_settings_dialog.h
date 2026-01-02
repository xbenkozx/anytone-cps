#ifndef OPTIONAL_SETTINGS_DIALOG_H
#define OPTIONAL_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QKeyEvent>

class Ui_OptionalSettingsEditDialog;
class MainWindow;

class PowerOnCharLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit PowerOnCharLineEdit(QWidget *parent = nullptr);

signals:
    void backspacePressed(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

class OptionalSettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit OptionalSettingsDialog(MainWindow *parent);
    ~OptionalSettingsDialog();
    void setupUI();
    void loadData();
    void updateWorkMode();
    void updateStartupChannels();
    void keyFunctionChanged();
    QString formatFrequency(QString frequency);

    void save();

    std::unique_ptr<Ui_OptionalSettingsEditDialog> ui;
    MainWindow *main_window;
    QStringList zone_names = {};
    QVector<PowerOnCharLineEdit*> display_char_line1_txt_list  = {};
    QVector<PowerOnCharLineEdit*> display_char_line2_txt_list  = {};

private:
    static void playTones(const QVector<QPair<double,double>>& toneList, int sampleRate = 16000);
    static QByteArray makeU8Sine(int sampleRate, double freqHz, double durationSec);
    
private slots:
    void saveClose();
    void powerOnCharUpdate(PowerOnCharLineEdit *lineEdit);
    void powerOnCharKeyPress(PowerOnCharLineEdit *lineEdit);
    void playCallEndTone();
    void playCallAllTone();
    void playCallPermitTone();
    void playIdleChannelTone();
    void playCallResetTone();
};

#endif