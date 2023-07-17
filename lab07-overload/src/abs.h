#ifndef MESA_CISC187_LAB02_ABS
#define MESA_CISC187_LAB02_ABS

namespace mesa {

    constexpr int abs(const int value) {
        return value < 0 ? -value : value;
    }

    constexpr unsigned int abs(const unsigned int value) {
        return value;
    }

    constexpr char abs(const char value) {
        return value < 0 ? -value : value;
    }

    constexpr unsigned char abs(const unsigned char value) {
        return value;
    }

    constexpr long abs(const long value) {
        return value < 0 ? -value : value;
    }

    constexpr double abs(const double value) {
        return value < 0 ? -value : value;
    }

    constexpr long double abs(const long double value) {
        return value < 0 ? -value : value;
    }

    constexpr long long abs(const long long value) {
        return value < 0 ? -value : value;
    }

    constexpr unsigned long abs(const unsigned long value) {
        return value < 0 ? -value : value;
    }
}

#endif