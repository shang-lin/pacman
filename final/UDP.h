/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/UDP.h,v                                  */
/* Working file: UDP.h                                                        */
/* head: 1.4                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 4                                                         */
/* selected revisions: 4                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.4                                                               */
/*                                                                            */
/* DATE: 2002/03/15 18:49:25                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Added comments                                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/03/05 11:19:10                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Finished getting UDP working.  Added exception throwing to UDP and         */
/* UDPacket.                                                                  */
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
/* DATE: 2002/02/17 06:13:41                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Adding skeleton files as examples                                          */
/*                                                                            */
/******************************************************************************/

#ifndef _UDP_H_
#define _UDP_H_

#include "UDPacket.h"
#include "network.h"
#include "NetworkException.h"
#include <pthread.h>

/**
 * Maintains a UDP socket
 **/
class UDP{
	private:
	int socketid;
	pthread_mutex_t udpMutex;

  public:
  
	/**
	 * Creates a UDP socket on the specified port
	 **/
	UDP(int port);
	
	/**
	 * Sends a UDPacket to the address specified in the UDPacket object
	 **/
	void sendPacket(UDPacket* pack);
	
	/**
	 * Receives a UDPacket
	 **/
	void receivePacket(UDPacket* pack);

	/**
	 * Returns whether there is a UDPacket to be read
	 **/
	bool isReady();
	
	/**
	 * Shuts down this UDP socket
	 **/
	void disconnect();

	/**
	 * Destroys this UDP object, disconnecting it from its socket
	 **/
	~UDP();
};

#endif
