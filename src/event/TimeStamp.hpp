#pragma once
#include <string>
#include <map>

namespace mirror {
    /**
     * TimeStamp stores a single point in time. (YYYY-MM-DD hh:mm:ss)
    */
    class TimeStamp {
    public:
        /**
         * Constructs a TimeStamp by parsing a timestamp from the NGINX log.
        */
        TimeStamp(const std::string &line);

        /**
         * @returns This TimeStamp as a string (YYYY-MM-DD hh:mm:ss)
        */
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
        /**
         * Parses a number and returns its value.
         * @param line Line to scan
         * @param index Index to start scanning at
         * @returns Value of the parsed number
        */
        template <typename T>
        T parseNumber(const std::string &line, uint8_t &index);

        /**
         * Converts a month from its shortened name to its number.
         * (ex. "Feb" -> 2)
         * @param line String containing the month
         * @param index Index of the first character of the month
         * @returns Month (1-12)
        */
        uint8_t parseMonth(const std::string &line, uint8_t &index);
        
        /**
         * @returns True if the character is a separator (':', '/', or ' ')
        */
        inline bool isSeparator(const char& c);
    };
}
