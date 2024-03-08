#include <event/Event.hpp>
#include <event/TimeStamp.hpp>
#include <mirror/logger.hpp>

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <memory>
#include <iostream>
#include <thread>

using namespace mirror;

void terminate(int signal) {
    std::cout << "Received SIGINT, terminating..." << std::endl;
    Logger* logger = Logger::getInstance();
    logger->close();
}

int main() {

    prometheus::Exposer exposer{"0.0.0.0:8080"};

    auto registry = std::make_shared<prometheus::Registry>();

    auto& hit_counter = prometheus::BuildCounter()
            .Name("hits")
            .Help("Hit counter")
            .Register(*registry);

    auto& tx_counter = hit_counter.Add({{"test", "tset2"}});

    exposer.RegisterCollectable(registry);

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        tx_counter.Increment();
        std::cout << tx_counter.Value() << std::endl;
    }

    std::string a = "\"07/Mar/2024:00:01:05 -0500\" \"66.203.67.100\" \"GET /opensuse/opensuse/update/leap/15.5/backports/repodata/23a22ea99529a8ab0529648312715d3ffe1252963f9f545d444c184cfaa91cd3-primary.xml.gz HTTP/1.1\" \"206\" \"169061\" \"259\" \"ZYpp 17.31.15 (curl 8.0.1)";

    mirror::Event ab(a);

    std::cout << ab.toString();
}
