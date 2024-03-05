#include <event/TimeStamp.hpp>
#include <sstream>
#include <iomanip>

namespace mirror {

    TimeStamp::TimeStamp(const std::string &line) {
        uint8_t index = 0;
        this->day = parseU8(line, index);
        this->month = parseMonth(line, index);
        this->year = parseU16(line, index);
        this->hour = parseU8(line, index);
        this->minute = parseU8(line, index);
        this->second = parseU8(line, index);
    }

    std::string TimeStamp::toString() {
        std::stringstream s;
        s << std::setfill('0') << std::setw(4) << (uint) year << "-";
        s << std::setfill('0') << std::setw(2) << (uint) month << "-";
        s << std::setfill('0') << std::setw(2) << (uint) day << " ";
        s << std::setfill('0') << std::setw(2) << (uint) hour << ":";
        s << std::setfill('0') << std::setw(2) << (uint) minute << ":";
        s << std::setfill('0') << std::setw(2) << (uint) second;
        return s.str();
    }

    // Private

    uint8_t TimeStamp::parseMonth(const std::string& line, uint8_t &index) {
        std::stringstream s;
        for(; index < line.size() && !isSeparator(line.at(index)); index++) {
            s << line.at(index);
        }
        index++;

        try {
            return month_map.at(s.str());
        } catch(const std::out_of_range& e) {
            return 0;
        }
    }

    uint16_t TimeStamp::parseU16(const std::string& line, uint8_t &index) {
        std::stringstream s;
        for(; index < line.size() && !isSeparator(line.at(index)); index++) {
            s << line.at(index);
        }
        index++;
        uint16_t result = 0;
        s >> result;
        return result;
    }

    uint8_t TimeStamp::parseU8(const std::string& line, uint8_t &index) {
        return (uint8_t) parseU16(line, index);
    }

    

    inline bool TimeStamp::isSeparator(const char& c) {
        return c == '/' || c == ':' || c == ' ';
    }

    const std::map<std::string, uint8_t> TimeStamp::month_map {
            {"Jan", 1}, {"Feb", 2},  {"Mar", 3},  {"Apr", 4}, 
            {"May", 5}, {"Jun", 6},  {"Jul", 7},  {"Aug", 8}, 
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12},
    };
}