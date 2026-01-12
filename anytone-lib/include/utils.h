#ifndef UTILS_H
#define UTILS_H

class Bit {
    public:
    static bool test(uint8_t byte, int bit_position){
        uint8_t mask = (1 << bit_position);
        return (byte & mask);
    }

    static void set(uint8_t *byte, int bit_position){
        uint8_t mask = (1 << bit_position);
        *byte |= mask;
    }

    static void clear(uint8_t *byte, int bit_position){
        uint8_t mask = (1 << bit_position);
        *byte &= ~mask;
    }
};

class Format {
    public:
    static double roundFrequency(double frequency){
        double freq = frequency * 100000;
        return double(5 * round(freq/5)) / 100000;
    }
};

#endif  