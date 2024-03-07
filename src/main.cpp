#include <event/Event.hpp>
#include <event/TimeStamp.hpp>
#include <mirror/logger.hpp>

#include <iostream>

using namespace mirror;

void terminate(int signal) {
    std::cout << "Received SIGINT, terminating..." << std::endl;
    Logger* logger = Logger::getInstance();
    logger->close();
}

int main() {
    std::string a = "\"07/Mar/2024:00:01:05 -0500\" \"66.203.67.100\" \"GET /opensuse/opensuse/update/leap/15.5/backports/repodata/23a22ea99529a8ab0529648312715d3ffe1252963f9f545d444c184cfaa91cd3-primary.xml.gz HTTP/1.1\" \"206\" \"169061\" \"259\" \"ZYpp 17.31.15 (curl 8.0.1)";

    mirror::Event ab(a);

    std::cout << ab.toString();
}
