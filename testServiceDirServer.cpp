#include "serviceDirServer.hpp"
#include "ServiceDirectoryClientStub.hpp"
#include <iostream>
#include <string>

void printTestResult(const std::string& testName, bool result) {
    std::cout << testName << ": " << (result ? "PASSED" : "FAILED") << std::endl;
}

int main() {
    bool allTestsPassed = true;

    serviceDirServer directory;
    ServiceDirectoryClientStub client(directory);

    // Test data
    ServerInfo server1Info = {"Server1", 1234};
    ServerInfo server2Info = {"Server2", 5678};
    std::string serviceName1 = "apartments";
    std::string serviceName2 = "stocks";

    // Register services using client
    client.registerService(serviceName1, server1Info);
    client.registerService(serviceName2, server2Info);
    std::cout << "Registering services..." << std::endl;

    // Search for services using client
    ServerInfo searchResult1 = client.searchService(serviceName1);
    bool searchTest1 = searchResult1.serverName == server1Info.serverName && searchResult1.port == server1Info.port;
    printTestResult("Search Service " + serviceName1, searchTest1);
    allTestsPassed &= searchTest1;

    // Print server name and port of searchResult1
    std::cout << "Search Result for " << serviceName1 << ": ";
    std::cout << "Server Name: " << searchResult1.serverName << ", Port: " << searchResult1.port << std::endl;

    ServerInfo searchResult2 = client.searchService(serviceName2);
    bool searchTest2 = searchResult2.serverName == server2Info.serverName && searchResult2.port == server2Info.port;
    printTestResult("Search Service " + serviceName2, searchTest2);
    allTestsPassed &= searchTest2;

    // Delete a service using client
    client.deleteService(serviceName1);
    ServerInfo deleteResult = client.searchService(serviceName1);
    bool deleteTest = deleteResult.serverName.empty() && deleteResult.port == -1;
    printTestResult("Delete Service " + serviceName1, deleteTest);
    allTestsPassed &= deleteTest;

    // Summary
    std::cout << "\n=== Summary ===\n";
    std::cout << "All tests " << (allTestsPassed ? "PASSED" : "FAILED") << std::endl;

    return allTestsPassed ? 0 : 1;
}
