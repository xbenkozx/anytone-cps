#ifndef GPS_ROAMING_EDIT_DIALOG_H
#define GPS_ROAMING_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "gps_roaming.h"

class Ui_GpsRoamingDialog;
class MainWindow;

class GpsRoamingEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit GpsRoamingEditDialog(MainWindow *parent, int index);
    ~GpsRoamingEditDialog();
    void setupUI();
    void loadData();
    double degMinToDecimal(int deg, double minutes);
    std::pair<int, double> minToDegree(double deg);

    std::unique_ptr<Ui_GpsRoamingDialog> ui;
    int index = 0;
    MainWindow *main_window;
    Anytone::GpsRoaming *gps;
    QVector<int> zone_idx_list = {};

private slots:
    void updateDegreeTab();
    void updateMinuteTab();
    void onRadiusEditingFinished();
    void onF1LatDegreeEditFinished();
    void onF1LongDegreeEditFinished();
    void onF2LatDegreeEditFinished();
    void onF2LongDegreeEditFinished();
    QString formatDegreeMinute(QString txt);
    QString formatDegree(QString txt);
    void nextBtnClicked();
    void prevBtnClicked();
    void save();
};

#endif