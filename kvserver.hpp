#ifndef KVSERVER_HPP
#define KVSERVER_HPP

#include "network.hpp"
#include "kvservice.hpp"
#include "ServiceDirectoryClientStub.hpp"

class KVServer: public Node{
    private:
        std:: shared_ptr<KVServiceServer> kvService;
        std::string svcName; // Human-readable service name
        int port; // Port number for the kv service
        ServiceDirectoryClientStub directoryClient;
    public:
        KVServer(std::string nodeName, ServiceDirectoryClientStub& directoryClient);
        ~KVServer(){}

        void setServiceName(const std::string& name);
        
        void setPort(int p);

	    void start();
    
        void setDBMFileName(string name);
};

#endif
