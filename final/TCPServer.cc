#include "TCPServer.h"

TCPServer::TCPServer(int port){
  struct sockaddr_in server_address;

  memset(&server_address,0,sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);

  listenid = socket(AF_INET, SOCK_STREAM, 0);
  bind(listenid,(sockaddr *)&server_address,sizeof(server_address));
  listen(listenid,0);

	//int one=1;
	//setsockopt(listenid,IPPROTO_TCP,TCP_NODELAY,(char*)&one,sizeof(one));

	pthread_mutex_init(&tcpServerMutex,NULL);
}

bool TCPServer::isReady(){
  return fdReady(listenid);
}

TCP* TCPServer::acceptTCP(){
  struct sockaddr_in client_address;
  socklen_t len = sizeof(client_address);
	pthread_mutex_lock(&tcpServerMutex);
  int connectid = accept(listenid,(sockaddr *)&client_address,&len);
	pthread_mutex_unlock(&tcpServerMutex);
  TCP* result = new TCP(connectid);

	//int one=1;
	//setsockopt(connectid,IPPROTO_TCP,TCP_NODELAY,(char*)&one,sizeof(one));
  
	return result;
}

void TCPServer::disconnect(){
  close(listenid);
}

TCPServer::~TCPServer(){
  disconnect();
	pthread_mutex_destroy(&tcpServerMutex);
}
