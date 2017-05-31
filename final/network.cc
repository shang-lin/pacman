#include "network.h"
#include <sys/select.h>
#include <sys/time.h>

bool fdReady(int fid){
  fd_set rset;
  FD_ZERO(&rset);
  FD_SET(fid,&rset);
  struct timeval tv;
  tv.tv_sec = 0; tv.tv_usec = 0;
  int result = select(fid+1,&rset,NULL,NULL,&tv);
  if(result == 1){
    return true;
  } else {
    return false;
  }
}

ostream& writeAddress(const sockaddr_in* address,ostream& os){
	int tempport = ntohs(address->sin_port);
	int tempip = ntohl(address->sin_addr.s_addr);
	int tempa = (tempip & 0xff000000) >> 24;
	int tempb = (tempip & 0x00ff0000) >> 16;
	int tempc = (tempip & 0x0000ff00) >> 8;
	int tempd = (tempip & 0x000000ff) >> 0;
	os << tempa << "." << tempb << "." << tempc << "." << tempd;
	os << ":" << tempport;
	return os;
}

string addressToString(const sockaddr_in* address){
	char buf[64];
	string result;
	int tempport = ntohs(address->sin_port);
	int tempip = ntohl(address->sin_addr.s_addr);
	int tempa = (tempip & 0xff000000) >> 24;
	int tempb = (tempip & 0x00ff0000) >> 16;
	int tempc = (tempip & 0x0000ff00) >> 8;
	int tempd = (tempip & 0x000000ff) >> 0;
	sprintf(buf,"%d.%d.%d.%d:%d",tempa,tempb,tempc,tempd,tempport);
	result = string(buf);
	return result;
}
