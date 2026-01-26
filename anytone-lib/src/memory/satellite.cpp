#include "satellite.h"
#include <QStringList>
#include "int.h"

Anytone::SatData* getSatData(QString sat_id){
    if(sat_id == "22825") // EYESAT A (AO-27)
        return const_cast<Anytone::SatData*>(&Anytone::EYESAT_AO27);
    if(sat_id == "25544") // ISS (ZARYA)
        return const_cast<Anytone::SatData*>(&Anytone::ISS_ZAYRA);
    if(sat_id == "27607") // SAUDISAT 1C
        return const_cast<Anytone::SatData*>(&Anytone::SAUDISAT_1C);
    if(sat_id == "35932") //SWISSCUBE
        return const_cast<Anytone::SatData*>(&Anytone::SWISSCUBE);
    if(sat_id == "40908") // LilacSat-2
        return const_cast<Anytone::SatData*>(&Anytone::LILAC_SAT2);

    if(
        sat_id == "63213" || // TEVEL 2-4
        sat_id == "63218" || // TEVEL 2-3
        sat_id == "63219" || // TEVEL 2-2
        sat_id == "63238" || // TEVEL 2-7
        sat_id == "63239"    // TEVEL 2-8
    
    ) // TEVEL2-4
        return const_cast<Anytone::SatData*>(&Anytone::TEVEL);
    return nullptr;
}

void Anytone::Satellite::decodeKeplerData(QString data){
    QStringList kD = data.split("\n");
    if(kD.size() < 2) return;

    name = kD[0];
    sat_number = kD[1].mid(2, 5).trimmed();
    classification = kD[1].mid(7, 1).trimmed();
    int_designator = kD[1].mid(9, 7).trimmed();
    epoch = kD[1].mid(18, 15).trimmed();
    mean_motion_derivative = kD[1].mid(33, 10).trimmed();
    mean_motion_sec_derivative = kD[1].mid(44, 8).trimmed();
    bstar = kD[1].mid(53, 8).trimmed();
    ephemeris_type = kD[1].mid(62, 1).trimmed();
    element_number = kD[1].mid(64, 3).trimmed();

    catalog_number = kD[2].mid(2, 5).trimmed();
    inclination = kD[2].mid(8, 8).trimmed();
    raan = kD[2].mid(17, 8).trimmed();
    eccentricity = kD[2].mid(26, 7).trimmed();
    argument_of_perigee = kD[2].mid(34, 8).trimmed();
    mean_anomaly = kD[2].mid(43, 8).trimmed();
    mean_motion = kD[2].mid(52, 11).trimmed();
    revolution_number = kD[2].mid(63, 5).trimmed();

    auto* sat_data = getSatData(sat_number);
    if(sat_data != nullptr){
        rx_frequency = sat_data->RxFrequency;
        tx_frequency = sat_data->TxFrequency;
        ctcss_dcs_encode = sat_data->CTCSS_DCS_Encode;
        ctcss_dcs_decode = sat_data->CTCSS_DCS_Decode;
        ctcss_encode_tone = sat_data->CTCSS_Encode_Tone;
        ctcss_decode_tone = sat_data->CTCSS_Decode_Tone;
        dcs_encode_tone = sat_data->DCS_Encode_Tone;
        dcs_decode_tone = sat_data->DCS_Decode_Tone;
    }


    // 0123456789012345678901234567890123456789012345678901234567890123456789
    // EYESAT A (AO-27)        
    // 1 22825U 93061C   26022.62600814  .00000284  00000+0  12510-3 0  9992
    // 2 22825  98.7080  89.9783 0008775 160.8639 199.2874 14.30895003686189
    // 0123456789012345678901234567890123456789012345678901234567890123456789
    // 0         1         2         3         4         5         6         7
    
}

QByteArray Anytone::Satellite::encode(){
    QByteArray data(0x200, 0);

    data.replace(0, 8, name.leftJustified(8, ' ').toUtf8().mid(0,8));
    data.replace(0x8, 16, epoch.leftJustified(16, ' ').toUtf8());
    data.replace(0x16, 11, mean_motion_derivative.rightJustified(11, ' ').toUtf8());
    data.replace(0x21, 8, inclination.rightJustified(8, ' ').toUtf8());
    data.replace(0x29, 9, raan.rightJustified(9, ' ').toUtf8());
    data.replace(0x32, 8, eccentricity.rightJustified(8, ' ').toUtf8());
    data.replace(0x3a, 9, argument_of_perigee.rightJustified(9, ' ').toUtf8());
    data.replace(0x43, 9, mean_anomaly.rightJustified(9, ' ').toUtf8());
    data.replace(0x4c, 12, mean_motion.rightJustified(12, ' ').toUtf8());
    data.replace(0x58, 5, revolution_number.rightJustified(5, ' ').toUtf8());

    data.replace(0x60, 4, Int::toBytes(rx_frequency, 4));
    data.replace(0x64, 4, Int::toBytes(tx_frequency, 4));
    data[0x68] = ctcss_dcs_encode;
    data[0x69] = ctcss_dcs_decode;
    data[0x6a] = ctcss_encode_tone;
    data[0x6b] = ctcss_decode_tone;
    data.replace(0x6c, 2, Int::toBytes(dcs_encode_tone, 2));
    data.replace(0x6e, 2, Int::toBytes(dcs_decode_tone, 2));

    return data;
}