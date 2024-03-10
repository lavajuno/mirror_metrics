#include <string>
#include <map>
#include <event/Event.hpp>


namespace mirror {
    class State {
    public:
        State(std::string file_path);

        const std::map<std::string, u_long> &getHits();

        const std::map<std::string, u_long> &getBytesSent();

        void save(std::string file_path);

        //void rotate(const std::string& file_path);

    private:
        std::map<std::string, u_long> hits;

        std::map<std::string, u_long> bytes_sent;

        std::string last_event;
    
    };

}
