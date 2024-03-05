#include <event/Event.hpp>
#include <event/TimeStamp.hpp>

#include <iostream>


int main() {
    std::cout << "test" << std::endl;

    std::string s = "24/Mar/2024 12:34:56 blah blah blah";

    mirror::TimeStamp ts(s);

    std::cout << ts.toString();
}