#include <cctype>
#include <cstdlib>
#include <limits>
#include <cstdint>
#include <cstdio>
#include <climits>
#include <random>
#include <string_view>

#pragma once

class Uuid {
    inline static size_t _string_len = 37;
    inline static auto _rand_generator = std::mt19937(std::random_device()());
    inline static auto _rand_distr = std::uniform_int_distribution<uint16_t>(
        std::numeric_limits<uint16_t>::min(),
        std::numeric_limits<uint16_t>::max()
    );


public:

    uint16_t ui16[8]; 

    inline std::string str() const {
        std::string str;
        str.resize(_string_len);

        sprintf(
            str.data(),
            "%04hx%04hx-%04hx-%04hx-%04hx-%04hx%04hx%04hx",
            ui16[0], ui16[1], ui16[2], ui16[3],
            ui16[4], ui16[5], ui16[6], ui16[7]
        );

        return str;
    }

    static inline Uuid random() {
        Uuid uuid = { 0 };

        for (size_t i = 0; i != 8; i++) {
            uuid.ui16[i] = _rand_distr(_rand_generator);
        }

        uint8_t* version = reinterpret_cast<uint8_t*>(uuid.ui16) + 6;
        uint8_t* variant = reinterpret_cast<uint8_t*>(uuid.ui16) + 8;

        *version &= 0x0f;
        *version |= 0x04;

        *variant &= 0x3f;
        *variant |= 0x80;

        return uuid;
    }

    static inline bool parse(
        const std::string_view str,
        Uuid& uuid
    ) {
        if (str.length() != _string_len) {
            return false;
        }

        int sections = sscanf(
            str.data(), 
            "%04hx%04hx-%04hx-%04hx-%04hx-%04hx%04hx%04hx",
            &uuid.ui16[0], &uuid.ui16[1], &uuid.ui16[2], &uuid.ui16[3],
            &uuid.ui16[4], &uuid.ui16[5], &uuid.ui16[6], &uuid.ui16[7]
        );

        return sections == 8;
    }
};
