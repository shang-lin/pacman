#include "UDP.h"

/**
 * Creates a UDP socket on the specified port
 **/
UDP::UDP(int port){
  struct sockaddr_in address;
	
	socketid = socket(AF_INET, SOCK_DGRAM, 0);

	if(socketid < 0){
		throw SocketException("socket() returned < 0");
	}

	memset(&address,0,sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	int er = bind(socketid,(sockaddr *)(&address),sizeof(address));
	//cout << "bind returned " << er << "\n";

	pthread_mutex_init(&udpMutex,NULL);
}

/**
 * Shuts down this UDP socket
 **/
void UDP::disconnect(){
	close(socketid);
}

/**
 * Sends a UDPacket to the address specified in the UDPacket object
 **/
void UDP::sendPacket(UDPacket* to_send){
	pthread_mutex_lock(&udpMutex);
	int n = sendto(socketid,
	               to_send->getData(),
								 to_send->getLength(),0,
								 (const sockaddr *)to_send->getAddress(),
								 sizeof(*(to_send->getAddress())));
	pthread_mutex_unlock(&udpMutex);
	if(n < 0){
		throw SocketIOException("Error writing to UDP socket");
	}
}

/**
 * Receives a UDPacket
 **/
void UDP::receivePacket(UDPacket* to_receive){
	byte message[1024];
	socklen_t len = sizeof(sockaddr_in);
	struct sockaddr_in address;
	int n;

	pthread_mutex_lock(&udpMutex);
	n = recvfrom(socketid,message,1024,0,(sockaddr *)(&address),&len);

	if(n < 0){
		throw SocketIOException("Error reading from UDP socket");
	}

	to_receive->setData(message,1024);
	to_receive->setLength(n);
	to_receive->setAddress(&address);
	pthread_mutex_unlock(&udpMutex);
}

/**
 * Returns whether there is a UDPacket to be read
 **/
bool UDP::isReady(){
	return fdReady(socketid);
}

/**
 * Destroys this UDP object, disconnecting it from its socket
 **/
UDP::~UDP(){
	disconnect();
	pthread_mutex_destroy(&udpMutex);
}
