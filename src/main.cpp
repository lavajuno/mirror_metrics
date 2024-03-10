#include <event/Event.hpp>
#include <event/TimeStamp.hpp>
#include <mirror/logger.hpp>

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <memory>
#include <iostream>
#include <thread>
#include <csignal>

using namespace mirror;

/**
 * Shut down logger on exit
*/
void terminate(int signal) {
    std::cout << "Received SIGINT, terminating..." << std::endl;
    Logger* logger = Logger::getInstance();
    logger->close();
    exit(signal);
}

int main() {
    // Register signal handler
    std::signal(SIGINT, terminate);

    // Connect to log server
    Logger* logger = Logger::getInstance();
    logger->configure(4001, "Metrics Engine", "mirrorlog");

    logger->info("Configuring Prometheus...");

    // Expose port 8080 to be scraped
    prometheus::Exposer exposer{"0.0.0.0:8080"};

    // Create registry
    auto registry = std::make_shared<prometheus::Registry>();

    // Register counters
    auto& hit_counter = prometheus::BuildCounter()
            .Name("hits")
            .Help("Hit counter")
            .Register(*registry);

    // Allow scraping of registry
    exposer.RegisterCollectable(registry);

    logger->info("Ready to process events.");

    std::string line;
    while(true) {
        // Parse from stdin
        getline(std::cin, line);
        mirror::Event event(line);
        logger->debug(event.toString());
        std::string project = event.getProject();
        if(project.size() > 0) {
            logger->debug("Hit on project " + project + ".");
            hit_counter.Add({{"project", project}}).Increment();
        } else {
            logger->debug("Hit - Invalid path / request.");
            hit_counter.Add({{"project", "invalid"}}).Increment();
        }
    }
}
