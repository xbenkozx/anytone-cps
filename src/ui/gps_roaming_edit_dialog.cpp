
#include "gps_roaming_edit_dialog.h"
#include "ui_gps_roaming_edit_dialog.h"
#include "main_window.h"
#include "constants.h"
#include "zone.h"


GpsRoamingEditDialog::GpsRoamingEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_GpsRoamingDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->index = index;
    this->main_window = parent;

    connect(ui->f1LatitudeDegreeCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateDegreeTab);
    connect(ui->f1NsCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateDegreeTab);
    connect(ui->f1LongitudeDegreeCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateDegreeTab);
    connect(ui->f1EwCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateDegreeTab);
    connect(ui->f2NsCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateMinuteTab);
    connect(ui->f2EwCmbx, &QComboBox::currentIndexChanged, this, &GpsRoamingEditDialog::updateMinuteTab);
    connect(ui->f1LatitudeMinuteTxt, &QLineEdit::editingFinished, this, &GpsRoamingEditDialog::onF1LatDegreeEditFinished);
    connect(ui->f1LongitudeMinuteTxt, &QLineEdit::editingFinished, this, &GpsRoamingEditDialog::onF1LongDegreeEditFinished);
    connect(ui->f2LatitudeDegreeTxt, &QLineEdit::editingFinished, this, &GpsRoamingEditDialog::onF2LatDegreeEditFinished);
    connect(ui->f2LongitudeDegreeTxt, &QLineEdit::editingFinished, this, &GpsRoamingEditDialog::onF2LongDegreeEditFinished);
    connect(ui->radiusTxt, &QLineEdit::editingFinished, this, &GpsRoamingEditDialog::onRadiusEditingFinished);

    setupUI();
    loadData();
    
}
GpsRoamingEditDialog::~GpsRoamingEditDialog(){}

void GpsRoamingEditDialog::setupUI(){
    ui->onOffCmbx->addItems(Constants::OFF_ON);
    ui->zoneCmbx->addItem("Off", QVariant::fromValue(nullptr));
    
    for(Anytone::Zone *zone : Anytone::Memory::zones){
        if(zone->channels.size() > 0){
            zone_idx_list.push_back(zone->id);
            ui->zoneCmbx->addItem(zone->name, QVariant::fromValue(zone));
        }
    }
    
    for(int i = 0; i < 91; i++){
        ui->f1LatitudeDegreeCmbx->addItem(QString::number(i));
    }
    ui->f1NsCmbx->addItems(QStringList{"North", "South"});
    for(int i = 0; i < 181; i++){
        ui->f1LongitudeDegreeCmbx->addItem(QString::number(i));
    }
    ui->f1EwCmbx->addItems(QStringList{"East", "West"});

    ui->radiusTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"),
            ui->radiusTxt
        )
    );

    ui->f1LatitudeMinuteTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression(R"(\d+(\.\d+)?)"),
            ui->f1LatitudeMinuteTxt
        )
    );

    ui->f1LongitudeMinuteTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression(R"(\d+(\.\d+)?)"),
            ui->f1LongitudeMinuteTxt
        )
    );
}
void GpsRoamingEditDialog::loadData(){
    gps = Anytone::Memory::gps_roaming_list.at(index);

    ui->onOffCmbx->setCurrentIndex(gps->enabled);

    if(gps->zone_idx == 0xff){
        ui->zoneCmbx->setCurrentIndex(0);
    }else{
        ui->zoneCmbx->setCurrentIndex(zone_idx_list.indexOf(gps->zone_idx) + 1);
    }

    ui->f1LatitudeDegreeCmbx->setCurrentIndex(gps->lat_degree);
    ui->f1LatitudeMinuteTxt->setText(formatDegreeMinute(QString::number(gps->lat_minute) + "." + QString::number(gps->lat_minute_decimal)));
    ui->f1NsCmbx->setCurrentIndex(gps->north_south);
    ui->f1LongitudeDegreeCmbx->setCurrentIndex(gps->long_degree);
    ui->f1LongitudeMinuteTxt->setText(formatDegreeMinute(QString::number(gps->long_minute) + "." + QString::number(gps->long_minute_decimal)));
    ui->f1EwCmbx->setCurrentIndex(gps->east_west);
    ui->radiusTxt->setText(QString::number(gps->radius));

    updateDegreeTab();
}
double GpsRoamingEditDialog::degMinToDecimal(int deg, double minutes){
    return double(deg) + (minutes / 60);
}
std::pair<int, double> GpsRoamingEditDialog::minToDegree(double deg){
    int degrees = int(abs(deg));
    double minutes = (abs(deg) - degrees) * 60;
    return std::pair<int, double>(degrees, minutes);
}
void GpsRoamingEditDialog::updateDegreeTab(){
    ui->f2LatitudeDegreeTxt->setText(
        formatDegree(
            QString::number(degMinToDecimal(
                ui->f1LatitudeDegreeCmbx->currentIndex(), 
                ui->f1LatitudeMinuteTxt->text().toDouble()
            ))
        )
    );
    ui->f2NsCmbx->setCurrentIndex(ui->f1NsCmbx->currentIndex());
    ui->f2LongitudeDegreeTxt->setText(
        formatDegree(
            QString::number(degMinToDecimal(
                ui->f1LongitudeDegreeCmbx->currentIndex(), 
                ui->f1LongitudeMinuteTxt->text().toDouble()
            ))
        )
    );
    ui->f2EwCmbx->setCurrentIndex(ui->f1EwCmbx->currentIndex());
}
void GpsRoamingEditDialog::updateMinuteTab(){
    std::pair<int, double> lat = minToDegree(ui->f2LatitudeDegreeTxt->text().toDouble());
    ui->f1LatitudeDegreeCmbx->setCurrentIndex(lat.first);
    ui->f1LatitudeMinuteTxt->setText(formatDegreeMinute(QString::number(lat.second)));

    std::pair<int, double> lng = minToDegree(ui->f2LongitudeDegreeTxt->text().toDouble());
    ui->f1LongitudeDegreeCmbx->setCurrentIndex(lng.first);
    ui->f1LongitudeMinuteTxt->setText(formatDegreeMinute(QString::number(lng.second)));
}
void GpsRoamingEditDialog::onRadiusEditingFinished(){
    if(ui->radiusTxt->text().toInt() < 10){
        ui->radiusTxt->setText("10");
    }else if(ui->radiusTxt->text().toInt() > 100000){
        ui->radiusTxt->setText("100000");
    }
}
void GpsRoamingEditDialog::onF1LatDegreeEditFinished(){
    ui->f1LatitudeMinuteTxt->setText(formatDegreeMinute(ui->f1LatitudeMinuteTxt->text()));
    updateDegreeTab();
}
void GpsRoamingEditDialog::onF1LongDegreeEditFinished(){
    ui->f1LongitudeMinuteTxt->setText(formatDegreeMinute(ui->f1LongitudeMinuteTxt->text()));
    updateDegreeTab();
}
void GpsRoamingEditDialog::onF2LatDegreeEditFinished(){
    ui->f2LatitudeDegreeTxt->setText(formatDegree(ui->f2LatitudeDegreeTxt->text()));
    updateMinuteTab();
}
void GpsRoamingEditDialog::onF2LongDegreeEditFinished(){
    ui->f2LongitudeDegreeTxt->setText(formatDegree(ui->f2LongitudeDegreeTxt->text()));
    updateMinuteTab();
}
QString GpsRoamingEditDialog::formatDegreeMinute(QString degree_str){
    double d = degree_str.toDouble();
    if(d > double(59.99)) d = double(59.99);
    return QString::number(d, 'f', 2);
}
QString GpsRoamingEditDialog::formatDegree(QString degree_str){
    double d = degree_str.toDouble();
    if(d > double(90)) d = double(90);
    return QString::number(d, 'f', 5);
}
void GpsRoamingEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::roaming_channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::roaming_channels.size() - 1);
}
void GpsRoamingEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void GpsRoamingEditDialog::save(){
    gps->enabled = ui->onOffCmbx->currentIndex();
    auto *zone = ui->zoneCmbx->currentData().value<Anytone::Zone*>();
    if(!zone){
        gps->zone_idx = 0xff;
    }else{
        gps->zone_idx = zone->id;
    }
    gps->zone = zone;
    gps->lat_degree = ui->f1LatitudeDegreeCmbx->currentIndex();
    QStringList lat_minute = ui->f1LatitudeMinuteTxt->text().split(".");
    gps->lat_minute = lat_minute.at(0).toInt();
    gps->lat_minute_decimal = lat_minute.at(1).toInt();
    gps->north_south = ui->f1NsCmbx->currentIndex();
    gps->long_degree = ui->f1LongitudeDegreeCmbx->currentIndex();
    QStringList long_minute = ui->f1LongitudeMinuteTxt->text().split(".");
    gps->long_minute = long_minute.at(0).toInt();
    gps->long_minute_decimal = long_minute.at(1).toInt();
    gps->east_west = ui->f1EwCmbx->currentIndex();
    gps->radius = ui->radiusTxt->text().toInt();

    main_window->listGpsRoaming();
}
