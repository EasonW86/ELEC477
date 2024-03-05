
#include "kvserver.hpp"


KVServer::KVServer(std::string nodeName, ServiceDirectoryClientStub& dirClient)
: Node(nodeName), directoryClient(dirClient){
            // note this is the same as installng the service software on the server
            // it doesn't run yet until the node is started.

            //cout << "Main: Server " << nodeName << " adding key value service" << endl;

	    kvService = std::make_shared<KVServiceServer>(svcName, weak_from_this(), directoryClient);

            addService(kvService);
        }

void KVServer::setServiceName(const std::string& name) {
    svcName = name;
    if(kvService) {
        kvService->setServiceName(name);
    }
}

void KVServer::setPort(int p) {
    port = p;
    if(kvService) {
        kvService->setPort(p);
    }
}

void KVServer::start(){
   //cerr << "in KVSERVER start" << endl;
   // Register service with the directory service before starting the node
    ServerInfo info = {name, port};
    directoryClient.registerService(svcName, info);
    
    // Start the kv service
    kvService = std::make_shared<KVServiceServer>(svcName, weak_from_this(), directoryClient);
    kvService->setServiceName(svcName);
    kvService->setPort(port);
    // Register service with the directory service before starting the node
    directoryClient.registerService(svcName, info);
    addService(kvService);
    kvService->start();
    
    // Deregister the service when shutting down
    directoryClient.deleteService(svcName);
}


void KVServer::setDBMFileName(string name){
    kvService -> setDBMFileName(name);
}

