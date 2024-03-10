#include <string>
#include <map>

#include <mirror/logger.hpp>
#include <event/Event.hpp>


namespace mirror {
    class State {
    public:
        State();

        const std::map<std::string, u_long> &getHits() { return hits; }

        const std::map<std::string, u_long> &getBytesSent() { return bytes_sent; }

        void registerHit(const std::string &project);

        void registerBytesSent(const std::string &project, uint64_t req_bytes_sent);

        void registerLastEvent(const std::string &event) { last_event = event; }

        void save();

    private:
        std::map<std::string, u_long> hits;

        std::map<std::string, u_long> bytes_sent;

        std::string last_event;

        Logger *logger;
    
    };

}
