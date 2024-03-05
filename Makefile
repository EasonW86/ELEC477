UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CXX=g++
CXXFLAGS=-std=c++2a -g -pthread -g
LDFLAGS= -lprotobuf -pthread -lgdbm
endif
ifeq ($(UNAME_S),Darwin)
CXXFLAGS=-std=c++20 -g -pthread -g
CXX=c++
LDFLAGS= -lprotobuf -pthread
endif

OBJS=main.o network.o E477KV.pb.o dumpHex.o kvserver.o kvservice.o kvclient1.o kvclientstub.o serviceDirServer.o ServiceDirectoryClientStub.o

all: bin/assign1
bin/assign1:  $(OBJS)
	$(CXX) -g -o bin/assign1 $(OBJS)  $(LDFLAGS)
	

main.o:  E477KV.pb.h main.cpp serviceDirServer.hpp ServiceDirectoryClientStub.hpp

E477KV.pb.h E477KV.pb.cc: E477KV.proto
	protoc --cpp_out=. E477KV.proto

kvclient1.o: kvclient1.cpp E477KV.pb.h kvclient1.hpp KVrpc.h kvclientstub.hpp network.hpp
kclientvstub.o: kvclientstub.cpp kvclientstub.hpp network.hpp ServiceDirectoryClientStub.hpp E477KV.pb.h


kvservice.o: kvservice.cpp kvservice.hpp E477KV.pb.h network.hpp ServiceDirectoryClientStub.hpp #E477.h
kvserver.o: kvserver.cpp kvserver.hpp network.hpp kvservice.hpp ServiceDirectoryClientStub.hpp

serviceDirServer.o: serviceDirServer.cpp serviceDirServer.hpp
ServiceDirectoryClientStub.o: ServiceDirectoryClientStub.cpp ServiceDirectoryClientStub.hpp serviceDirServer.hpp

# support files
network.o: network.hpp dumpHex.hpp
dumpHex.o: dumpHex.hpp

# Rule for generating protobuf source and header files from .proto file
E477KV.pb.h E477KV.pb.cc: E477KV.proto
	protoc --cpp_out=. E477KV.proto


clean:
	rm bin/* *.o E477KV.pb.h E477KV.pb.cc
