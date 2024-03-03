#ifndef SERVICE_DIRECTORY_CLIENT_STUB_HPP
#define SERVICE_DIRECTORY_CLIENT_STUB_HPP

#include "serviceDirServer.hpp"  // Assume it's a local server for simplicity

class ServiceDirectoryClientStub {
private:
    serviceDirServer& server;

public:
    ServiceDirectoryClientStub(serviceDirServer& server) : server(server) {}
    void registerService(const std::string& serviceName, const ServerInfo& serverInfo);
    ServerInfo searchService(const std::string& serviceName);
    void deleteService(const std::string& serviceName);
};

#endif // SERVICE_DIRECTORY_CLIENT_STUB_HPP
