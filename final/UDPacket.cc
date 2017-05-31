#include "UDPacket.h"
#include "NetworkException.h"

/**
 * Constructs an empty UDPacket
 **/
UDPacket::UDPacket(){
	length = 0;
}

/**
 * Creates a copy of the specified UDPacket
 **/
UDPacket::UDPacket(UDPacket* to_copy){
	length = to_copy->getLength();
	const byte* other = to_copy->getData();
	for(int i=0;i<length;i++){
		data[i] = other[i];
	}
	setAddress(to_copy->getAddress());
}

/**
 * Sets the specified index to the specified value
 **/
void UDPacket::setData(int index,byte b){
	assert(index < MAX_LENGTH);
	data[index] = b;
}

/**
 * Copies the first count bytes in the specified array
 * into this UDPacket, and sets the length of this packet
 * to count
 **/
void UDPacket::setData(const byte* newdata,int count){
	for(int i=0;i<count;i++){
		data[i] = newdata[i];
	}
	length = count;
}

/**
 * Returns the value at the specified index
 **/
byte UDPacket::getData(int index){
	assert(index < MAX_LENGTH);
	return data[index];
}

/**
 * Returns the data for this packet
 **/
const byte* UDPacket::getData(){
	return data;
}

/**
 * Sets the length of this packet
 **/
void UDPacket::setLength(int len){
	length = len;
}

/**
 * Returns the length of this packet
 **/
int UDPacket::getLength(){
	return length;
}

/**
 * Gets the IP address stored in this packet
 * If this is an incoming packet, this address specifies
 * where the packet came from
 * If this is an outgoing packet, this address specifies
 * where the packet should be sent to
 **/
const struct sockaddr_in* UDPacket::getAddress(){
	return &address;
}

/**
 * Sets the IP address of this packet
 **/
void UDPacket::setAddress(const struct sockaddr_in* send_to){
	memset(&address,0,sizeof(address));
	address.sin_family = send_to->sin_family;
	address.sin_port = send_to->sin_port;
	address.sin_addr.s_addr = send_to->sin_addr.s_addr;
}

/**
 * Sets the IP address of this packet to the host specified
 * in the string addr on the specified port
 **/
void UDPacket::setAddress(string addr, int port){
	struct hostent *byname;
	byname = gethostbyname(addr.c_str());

	if(byname == NULL){
		throw UnknownHostException(string("Cannot resolve host : ") + addr);
	}

	memset(&address,0,sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	memcpy(&(address.sin_addr.s_addr),byname->h_addr_list[0],sizeof(struct in_addr));
}

/**
 * Destroys this UDPacket
 **/
UDPacket::~UDPacket(){}
