#ifndef SATELLITE_H
#define SATELLITE_H

#include <QString>

namespace Anytone {

    struct SatData {
        int RxFrequency;
        int TxFrequency;
        int CTCSS_DCS_Encode;
        int CTCSS_DCS_Decode;
        int CTCSS_Encode_Tone;
        int CTCSS_Decode_Tone;
        int DCS_Encode_Tone;
        int DCS_Decode_Tone;
    };

    constexpr SatData EYESAT_AO27 = {
        .RxFrequency = 43679500,
        .TxFrequency = 14585000,
        .CTCSS_DCS_Encode = 0,
        .CTCSS_DCS_Decode = 0,
        .CTCSS_Encode_Tone = 0,
        .CTCSS_Decode_Tone = 0,
        .DCS_Encode_Tone = 0,
        .DCS_Decode_Tone = 0
    };

    constexpr SatData ISS_ZAYRA = {
        .RxFrequency = 43780000,
        .TxFrequency = 14599000,
        .CTCSS_DCS_Encode = 1,
        .CTCSS_DCS_Decode = 1,
        .CTCSS_Encode_Tone = 1,
        .CTCSS_Decode_Tone = 1,
        .DCS_Encode_Tone = 0,
        .DCS_Decode_Tone = 0
    };
    constexpr SatData SAUDISAT_1C = {
        .RxFrequency = 43679500,
        .TxFrequency = 14585000,
        .CTCSS_DCS_Encode = 1,
        .CTCSS_DCS_Decode = 1,
        .CTCSS_Encode_Tone = 1,
        .CTCSS_Decode_Tone = 1,
        .DCS_Encode_Tone = 0,
        .DCS_Decode_Tone = 0
    };
    constexpr SatData SWISSCUBE = {
        .RxFrequency = 43780000,
        .TxFrequency = 14599000,
        .CTCSS_DCS_Encode = 1,
        .CTCSS_DCS_Decode = 1,
        .CTCSS_Encode_Tone = 1,
        .CTCSS_Decode_Tone = 1,
        .DCS_Encode_Tone = 0,
        .DCS_Decode_Tone = 0
    };
    constexpr SatData LILAC_SAT2 = {
        .RxFrequency = 43720000,
        .TxFrequency = 14435000,
        .CTCSS_DCS_Encode = 0,
        .CTCSS_DCS_Decode = 0,
        .CTCSS_Encode_Tone = 0,
        .CTCSS_Decode_Tone = 0,
        .DCS_Encode_Tone = 0,
        .DCS_Decode_Tone = 0
    };

    constexpr SatData TEVEL = {
            .RxFrequency = 43640000,
            .TxFrequency = 14597000,
            .CTCSS_DCS_Encode = 0,
            .CTCSS_DCS_Decode = 0,
            .CTCSS_Encode_Tone = 0,
            .CTCSS_Decode_Tone = 0,
            .DCS_Encode_Tone = 0,
            .DCS_Decode_Tone = 0
        };

    class Satellite {
    public:
        Satellite(){}
        ~Satellite(){};

        

        void decodeKeplerData(QString data);
        QByteArray encode();

        QString name;
        QString sat_number;
        QString classification;
        QString int_designator;
        QString epoch;
        QString mean_motion_derivative;
        QString mean_motion_sec_derivative;
        QString bstar;
        QString ephemeris_type;
        QString element_number;
        QString catalog_number;
        QString inclination;
        QString raan;
        QString eccentricity;
        QString argument_of_perigee;
        QString mean_anomaly;
        QString mean_motion;
        QString revolution_number;
        int write_enable = 0;
        int rx_frequency = 0;
        int tx_frequency = 0;
        int ctcss_dcs_encode = 0;
        int ctcss_dcs_decode = 0;
        int ctcss_encode_tone = 0;
        int ctcss_decode_tone = 0;
        int dcs_encode_tone = 0;
        int dcs_decode_tone = 0;
        
    };
}

#endif  // SATELLITE_H