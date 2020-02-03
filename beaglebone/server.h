#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

class Server {
private:
	int 		portNumber;
    int 	    socketfd, clientSocketfd;
    struct 	    sockaddr_in   serverAddress;
    struct 	    sockaddr_in   clientAddress;
    bool		clientConnected;

public:
	Server(int portNumber);
	virtual int listen();
	virtual int send(std::string message);
	virtual std::string receive(int size);

	virtual ~Server();
};


#endif