#ifndef OPTIONAL_SETTINGS_DIALOG_H
#define OPTIONAL_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QKeyEvent>
#include <QHBoxLayout>

class Ui_OptionalSettingsEditDialog;
class MainWindow;

class ScreenRender : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenRender(QWidget *parent = nullptr);
    uint8_t channel_name_color_a = 0;
    uint8_t channel_name_color_b = 0;
    uint8_t zone_name_color_a = 0;
    uint8_t zone_name_color_b = 0;
    uint8_t sb_text_color = 0;
    uint8_t date_type = 0;
    bool show_channel_type = true;
    bool show_ts = true;
    bool show_cc = true;
    bool show_time = true;


protected:
    void paintEvent(QPaintEvent *event) override;
};

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
    ScreenRender *screen_render;
    QHBoxLayout *screen_render_layout;

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
    void refreshScreenView();
};

#endif