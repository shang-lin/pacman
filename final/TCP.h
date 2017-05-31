/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/TCP.h,v                                  */
/* Working file: TCP.h                                                        */
/* head: 1.6                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 6                                                         */
/* selected revisions: 6                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.6                                                               */
/*                                                                            */
/* DATE: 2002/03/15 18:49:25                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Added comments                                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.5                                                               */
/*                                                                            */
/* DATE: 2002/02/20 05:32:46                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Fixed a few more bugs in the write function                                */
/* and added the spot that throws unknownhostexceptions                       */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.4                                                               */
/*                                                                            */
/* DATE: 2002/02/19 18:26:49                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* A few more things (fixed some indentation)                                 */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/02/19 18:17:09                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Finally got Exceptions working.  Now you can toss an NetworkException,     */
/* catch it as an Exception (call it Exception e) and then just call          */
/* cerr << e  to print it out.                                                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/02/19 05:14:24                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Got TCP/TCPServer working for the first time                               */
/* Added network.h and network.cc                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/02/17 06:13:41                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Adding skeleton files as examples                                          */
/*                                                                            */
/******************************************************************************/

#ifndef _TCP_H_
#define _TCP_H_

#include "network.h"
#include "NetworkException.h"
#include <pthread.h>
#include <string>

/**
 * This is the class that maintains a TCP connection
 **/
class TCP{
  protected:
  static const int MAX_LENGTH = 1024;
  int socketid;
  bool connected;
	pthread_mutex_t tcpMutex;

  public:
  /**
	 * This opens a TCP connection to the specified address on the
	 * specified port
	 **/
	TCP(string address,int port);
  
	/**
	 * This creates a TCP object that will use the specified socket
	 * file descriptor.  This is useful for constructing a TCP object
	 * in TCPServer
	 **/
	TCP(int sockfd);

	/**
	 * This sends the first length bytes of the array data
	 **/
  void sendBytes(const byte* data,int length);
  
	/**
	 * This sends the specified string
	 **/
	void sendString(const string* message);
  
	/**
	 * This returns whether this TCP connection is ready for reading
	 **/
	bool isReady();

	/**
	 * This reads a string
	 **/
  const string* getString();
  
	/**
	 * Closes the socket
	 **/
	void disconnect();

  ~TCP();
};

#endif
