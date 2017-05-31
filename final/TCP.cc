#include "TCP.h"

TCP::TCP(string address,int port){
  struct in_addr ip_address;
  struct hostent* byname;
  struct sockaddr_in server_address;

  memset(&server_address,0,sizeof(server_address));
  byname = gethostbyname(address.c_str());
	if(byname == NULL){
		throw UnknownHostException(string("Cannot resolve host : ") + address);
	}
  memcpy(&ip_address,byname->h_addr_list[0],sizeof(struct in_addr));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = ip_address.s_addr;

  socklen_t len = sizeof(server_address);

  socketid = socket(AF_INET, SOCK_STREAM, 0);
  if(socketid < 0){
    throw SocketException("socket() returned < 0");
  }

  if(connect(socketid,(sockaddr *)&server_address,len) < 0){
    connected = false;
    throw ConnectException("connect() returned < 0");
  } else {
    connected = true;
  }

	//int one=1;
	//setsockopt(socketid,IPPROTO_TCP,TCP_NODELAY,(char*)&one,sizeof(one));

	pthread_mutex_init(&tcpMutex,NULL);
}

TCP::TCP(int sockfd){
  socketid = sockfd;
  connected = true;
	pthread_mutex_init(&tcpMutex,NULL);
}

void TCP::sendBytes(const byte* data,int length){
	if(connected){
		const byte* toSend = data;
		int numLeft = length;
    int numWritten;
		pthread_mutex_lock(&tcpMutex);
    while(numLeft > 0){
      numWritten = write(socketid,toSend,numLeft);
      if(numWritten <= 0){
        if(errno == EINTR){
          numWritten = 0;        
        } else {
					pthread_mutex_unlock(&tcpMutex);
          throw SocketIOException("Error writing to socket");
        }
      }
      numLeft -= numWritten;
      toSend += numWritten;
    }
		cerr << "\r";
		pthread_mutex_unlock(&tcpMutex);
  } else {
    throw SocketIOException("Error writing to socket : not connected"); 
  }
}

void TCP::sendString(const string* message){
	sendBytes((unsigned char *)message->c_str(),message->length());
}

bool TCP::isReady(){
  if(connected){
    return fdReady(socketid);
  }
  return false;
}

const string* TCP::getString(){
  if(connected){
    byte message_in[MAX_LENGTH];
		pthread_mutex_lock(&tcpMutex);
    int n = read(socketid,message_in,MAX_LENGTH);
		pthread_mutex_unlock(&tcpMutex);
		if(n == 0){
			throw SocketIOException("I think the other guy left");
		}
    const string* result = new string((char *)message_in,0,n);
    return result;
  }
  return NULL;
}

void TCP::disconnect(){
  if(connected){
    close(socketid);
    connected = false;
  }
}

TCP::~TCP(){
  disconnect();
	pthread_mutex_destroy(&tcpMutex);
}
