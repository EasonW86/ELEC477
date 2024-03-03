#include "serviceDirServer.hpp"

void serviceDirServer::registerService(const std::string& serviceName, const ServerInfo& serverInfo) {
    std::lock_guard<std::mutex> lock(directoryMutex);
    directory[serviceName] = serverInfo;
}

ServerInfo serviceDirServer::searchService(const std::string& serviceName) {
    std::lock_guard<std::mutex> lock(directoryMutex);
    if (directory.find(serviceName) != directory.end()) {
        return directory[serviceName];
    }
    return {"", -1}; // Return empty server info if not found
}

void serviceDirServer::deleteService(const std::string& serviceName) {
    std::lock_guard<std::mutex> lock(directoryMutex);
    directory.erase(serviceName);
}
