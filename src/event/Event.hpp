#pragma once
#include <string>
#include <event/TimeStamp.hpp>

namespace mirror {
    class Event {

    public: // methods
        /**
         * Creates an Event by parsing a line from the NGINX log file.
        */
        Event(std::string line);

        TimeStamp getTimeStamp() { return time_stamp; }

        const std::string& getRemoteAddr() { return remote_addr; }

        const std::string& getRequest() { return request; }

        uint16_t getStatus() { return status; }

        uint64_t getBytesSent() { return bytes_sent; }

        uint32_t getBytesReceived() { return bytes_recv; }

        std::string getUserAgent() { return user_agent; }

    private: // data
        TimeStamp time_stamp;
        std::string remote_addr;
        std::string request;
        std::string request_path;
        uint16_t status;
        uint64_t bytes_sent;
        uint32_t bytes_recv;
        std::string user_agent;

    private: // methods

    };
}