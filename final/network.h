/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/network.h,v                              */
/* Working file: network.h                                                    */
/* head: 1.3                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 3                                                         */
/* selected revisions: 3                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/03/15 18:49:25                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Added comments                                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/03/05 11:19:10                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Finished getting UDP working.  Added exception throwing to UDP and         */
/* UDPacket.                                                                  */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/02/19 05:14:24                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Got TCP/TCPServer working for the first time                               */
/* Added network.h and network.cc                                             */
/*                                                                            */
/******************************************************************************/

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

typedef unsigned char byte;
const int MAXPACKETLEN = 1024;

bool fdReady(int fid);

ostream& writeAddress(const sockaddr_in* address,ostream& os);

string addressToString(const sockaddr_in* address);

#endif
