#include <string>
#include <map>
#include <event/Event.hpp>
#include <nlohmann/json.hpp>


namespace mirror {
    class State {
    public:
        State(std::string file_path);

    private:
        std::map<std::string, u_long> hits;
        std::map<std::string, u_long> bytes_sent;
        Event last_event;
    };
}