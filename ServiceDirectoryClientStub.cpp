#include "ServiceDirectoryClientStub.hpp"

void ServiceDirectoryClientStub::registerService(const std::string& serviceName, const ServerInfo& serverInfo) {
    server.registerService(serviceName, serverInfo);
}

ServerInfo ServiceDirectoryClientStub::searchService(const std::string& serviceName) {
    return server.searchService(serviceName);
}

void ServiceDirectoryClientStub::deleteService(const std::string& serviceName) {
    server.deleteService(serviceName);
}
