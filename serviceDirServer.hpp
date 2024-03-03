#ifndef SERVICE_DIR_SERVER_HPP
#define SERVICE_DIR_SERVER_HPP

#include <map>
#include <string>
#include <mutex>

// Structure to hold server information
struct ServerInfo {
    std::string serverName;
    int port;
};

class serviceDirServer {
private:
    std::map<std::string, ServerInfo> directory;
    std::mutex directoryMutex;

public:
    void registerService(const std::string& serviceName, const ServerInfo& serverInfo);
    ServerInfo searchService(const std::string& serviceName);
    void deleteService(const std::string& serviceName);
};

#endif // SERVICE_DIRECTORY_SERVER_HPP
