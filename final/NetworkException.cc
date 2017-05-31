#include "NetworkException.h"

NetworkException::NetworkException() : 
  Exception(){}
NetworkException::NetworkException(const char* desc) : 
  Exception(desc){}
NetworkException::NetworkException(string desc) : 
  Exception(desc){}

BindException::BindException() : 
  NetworkException(){}
BindException::BindException(const char* desc) : 
  NetworkException(desc){}
BindException::BindException(string desc) : 
  NetworkException(desc){}

ConnectException::ConnectException() : 
  NetworkException(){}
ConnectException::ConnectException(const char* desc) : 
  NetworkException(desc){}
ConnectException::ConnectException(string desc) : 
  NetworkException(desc){}

SocketException::SocketException() : 
  NetworkException(){}
SocketException::SocketException(const char* desc) : 
  NetworkException(desc){}
SocketException::SocketException(string desc) : 
  NetworkException(desc){}

SocketIOException::SocketIOException() : 
  NetworkException(){}
SocketIOException::SocketIOException(const char* desc) : 
  NetworkException(desc){}
SocketIOException::SocketIOException(string desc) : 
  NetworkException(desc){}

UnknownHostException::UnknownHostException() : 
  NetworkException(){}
UnknownHostException::UnknownHostException(const char* desc) : 
  NetworkException(desc){}
UnknownHostException::UnknownHostException(string desc) : 
  NetworkException(desc){}

ProtocolException::ProtocolException() : 
  NetworkException(){}
ProtocolException::ProtocolException(const char* desc) : 
  NetworkException(desc){}
ProtocolException::ProtocolException(string desc) : 
  NetworkException(desc){}

