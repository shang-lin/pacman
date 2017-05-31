/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/UDPacket.h,v                             */
/* Working file: UDPacket.h                                                   */
/* head: 1.2                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 2                                                         */
/* selected revisions: 2                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/03/15 18:49:25                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Added comments                                                             */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/03/05 11:19:10                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Finished getting UDP working.  Added exception throwing to UDP and         */
/* UDPacket.                                                                  */
/*                                                                            */
/******************************************************************************/

#ifndef _UDPPACKET_H_
#define _UDPPACKET_H_

#include "network.h"

#include <string>

/**
 * Encapsulates a packet to be sent via UDP
 **/
class UDPacket{
	private:
	static const int MAX_LENGTH = 1024;
	byte data[MAX_LENGTH];
	int length;
	struct sockaddr_in address;
	
	public:
	/**
	 * Constructs an empty UDPacket
	 **/
	UDPacket();

	/**
	 * Creates a copy of the specified UDPacket
	 **/
	UDPacket(UDPacket* to_copy);

	/**
	 * Sets the specified index to the specified value
	 **/
	void setData(int index, byte b);
	
	/**
	 * Copies the first count bytes in the specified array
	 * into this UDPacket, and sets the length of this packet
	 * to count
	 **/
	void setData(const byte* newdata,int count);
	
	/**
	 * Returns the value at the specified index
	 **/
	byte getData(int index);
	
	/**
	 * Returns the data for this packet
	 **/
	const byte* getData();

	/**
	 * Sets the length of this packet
	 **/
	void setLength(int len);

	/**
	 * Returns the length of this packet
	 **/
	int getLength();

	/**
	 * Gets the IP address stored in this packet
	 * If this is an incoming packet, this address specifies
	 * where the packet came from
	 * If this is an outgoing packet, this address specifies
	 * where the packet should be sent to
	 **/
	const struct sockaddr_in* getAddress();

	/**
	 * Sets the IP address of this packet
	 **/
	void setAddress(const struct sockaddr_in* send_to);
	
	/**
	 * Sets the IP address of this packet to the host specified
	 * in the string addr on the specified port
	 **/
	void setAddress(string addr, int port);

	/**
	 * Destroys this packet
	 **/
	~UDPacket();
};

#endif
