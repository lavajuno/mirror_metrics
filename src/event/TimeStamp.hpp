#pragma once
#include <string>
#include <map>

namespace mirror {
    class TimeStamp {
    public:
        TimeStamp(const std::string& line);

        std::string toString();

    private:
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        static const std::map<std::string, uint8_t> month_map;

    private:
        uint16_t parseU16(const std::string& line, uint8_t &index);
        uint8_t parseU8(const std::string& line, uint8_t &index);
        uint8_t parseMonth(const std::string& line, uint8_t &index);
        inline bool isSeparator(const char& c);
    };
}