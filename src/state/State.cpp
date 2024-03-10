#include <state/State.hpp>

#include <event/Event.hpp>
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using json = nlohmann::json;

namespace mirror {

    /* ----- Public ----- */

    State::State(std::string file_path) {
        std::ifstream f;
        f.open(file_path);
        if(f.fail()) {
            std::cerr << "Failed to load state." << std::endl;
            this->hits = std::map<std::string, u_long>();
            this->bytes_sent = std::map<std::string, u_long>();
            this->last_event = "INVALID";
            return;
        }
        json state = json::parse(f);
        state.items();
        f.close();
        this->hits = state["hits"].template get<std::map<std::string, u_long>>();
        this->bytes_sent = state["bytes_sent"].template get<std::map<std::string, u_long>>();
        this->last_event = state["last_event"].template get<std::string>();
    }

    void State::save(std::string file_path) {
        json j;
        j["hits"] = hits;
        j["bytes_sent"] = bytes_sent;
        j["last_event"] = last_event;
        std::ofstream f;
        f.open(file_path, std::ofstream::trunc);
        if(f.fail()) {
            std::cerr << "Failed to save state." << std::endl;
            return;
        }
        f << j;
        std::cout << j;
        f.close();
    }

    /* ----- Private ----- */
}