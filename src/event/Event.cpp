#include <event/Event.hpp>
#include <sstream>

namespace mirror {

    /* ----- Public ----- */

    Event::Event(const std::string &line) {
        uint32_t index = 0;
        this->time_stamp = new TimeStamp(nextString(line, index));
        this->remote_addr = nextString(line, index);
        this->request = nextString(line, index);
        this->status = nextNumber<uint16_t>(line, index);
        this->bytes_sent = nextNumber<uint16_t>(line, index);
        this->bytes_recv = nextNumber<uint16_t>(line, index);
        this->user_agent = nextString(line, index);
    }

    std::string Event::toString() {
        std::stringstream s;
        s << "{\"time_stamp\":\"" << time_stamp->toString() << "\",";
        s << "\"remote_addr\":\"" << remote_addr << "\",";
        s << "\"request\":\"" << request << "\",";
        s << "\"status\":" << status << ",";
        s << "\"bytes_sent\":" << bytes_sent << ",";
        s << "\"bytes_recv\":" << bytes_recv << ",";
        s << "\"user_agent\":\"" << user_agent << "\"}";

        return s.str();
    }

    /* ----- Private ----- */

    std::string Event::nextString(const std::string &line, uint32_t &index) {
        std::stringstream s;
        // skip to next string
        for(; index < line.size() && !isQuote(line, index); index++);
        index++; // skip opening "
        for(; index < line.size() && !isQuote(line, index); index++) {
            s << line.at(index);
        }
        index++; // skip closing "
        return s.str();
    }

    template <typename T>
    T Event::nextNumber(const std::string &line, uint32_t &index) {
        std::stringstream s;
        T result;
        // skip to next string
        for(; index < line.size() && !isQuote(line, index); index++);
        index++; // skip opening "
        for(; index < line.size() && !isQuote(line, index); index++) {
            s << line.at(index);
        }
        index++; // skip closing "
        s >> result;
        return result;
    }

    inline bool Event::isQuote(const std::string &line, uint32_t &index) {
        return line.at(index) == '"' 
                && (index == 0 || line.at(index - 1) != '\\');
    }
}
