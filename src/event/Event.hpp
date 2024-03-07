#pragma once
#include <string>
#include <event/TimeStamp.hpp>

namespace mirror {
    /**
     * Event stores the data from a single NGINX log event.
    */
    class Event {
    public:
        /**
         * Constructs an Event by parsing a line from the NGINX log.
         * Note: The parser assumes that NGINX escapes double quotes in its log
         * output. This is its default behavior, but the parser may behave
         * unexpectedly if this is not the case.
         * @param line Line from the NGINX log to parse
        */
        Event(const std::string &line);

        /**
         * Destroys this Event.
        */
        ~Event() { delete time_stamp; }

        /**
         * @returns this Event as a JSON string
        */
        std::string toString();

    private:
        TimeStamp *time_stamp;

        std::string remote_addr;

        std::string request;

        uint16_t status;

        uint64_t bytes_sent;

        uint64_t bytes_recv;

        std::string user_agent;

    private:
        /**
         * Returns the next string (enclosed with '"') in the line.
         * This function assumes that instances of '"' within the strings
         * themselves are escaped.
         * @param line Line to scan
         * @param index Index to start scanning at
         * @returns The next '"'-enclosed string in the line.
        */
        std::string nextString(const std::string &line, uint32_t &index);

        /**
         * Returns true if the character at {index} is '"' and either of the 
         * following are true:
         *  1. {index} is 0.
         *  2. The character at {index - 1} is '\'.
         * @param index Index of the character to test
         * @returns True if the character at the given index is an unescaped '"'
        */
        inline bool isQuote(const std::string &line, uint32_t &index);

        /**
         * Returns the next number (enclosed with '"') in the line.
         * This function assumes that instances of '"' within the strings
         * themselves are escaped.
         * @param line Line to scan
         * @param index Index to start scanning at
         * @returns The next '"'-enclosed number in the line.
        */
        template <typename T>
        T nextNumber(const std::string &line, uint32_t &index);
    };
}
