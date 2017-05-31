/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/TCPServer.h,v                            */
/* Working file: TCPServer.h                                                  */
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
/* DATE: 2002/02/19 18:26:49                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* A few more things (fixed some indentation)                                 */
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

#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "TCP.h"
#include "network.h"

/**
 * This class maintains a TCP server socket that
 * can accept TCP connections and set up TCP objects
 * to manage those connections
 **/
class TCPServer{
  protected:
  int listenid;
	pthread_mutex_t tcpServerMutex;

  public:
  
	/**
	 * Creates a server socket on the specified port
	 **/
	TCPServer(int port);
  
	/**
	 * Returns whether there are any connections to accept
	 **/
	bool isReady();
  
	/**
	 * Returns a TCP object to manage the accepted connection
	 **/
	TCP* acceptTCP();
  
	/**
	 * Closes this TCP server socket
	 **/
	void disconnect();
  
	~TCPServer();
};

#endif
