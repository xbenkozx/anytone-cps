#pragma once

#include <memory>

namespace Anytone {
    enum RadioModel {
        None,
        D878UVII_FW400,
        D890UV_FW103,
        D168UV
    };
}

enum class DeviceRWType : uint8_t {
    NONE = 0,
    RADIO_DATA = 1,
    DIGITAL_CONTACTS = 2,
    BOOT_IMAGE = 4,
    BK1_IMAGE = 8,
    BK2_IMAGE = 16,
    SATELLITE_DATA = 32
};

inline DeviceRWType operator&(DeviceRWType a, DeviceRWType b)
{
    return static_cast<DeviceRWType>(
        static_cast<uint8_t>(a) & static_cast<uint8_t>(b)
    );
}

inline DeviceRWType operator|(DeviceRWType a, DeviceRWType b)
{
    return static_cast<DeviceRWType>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b)
    );
}

inline DeviceRWType& operator|=(DeviceRWType& a, DeviceRWType b)
{
    a = a | b;
    return a;
}

enum DeviceStatus{
    STATUS_SUCCESS,
    STATUS_COM_ERROR,
    STATUS_DEVICE_MISMATCH
};