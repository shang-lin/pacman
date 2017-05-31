/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/ComTracker.h,v                           */
/* Working file: ComTracker.h                                                 */
/* head: 1.1                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 1                                                         */
/* selected revisions: 1                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/03/22 10:56:56                                                  */
/* CHANGES MADE BY: Philip Nowell                                             */
/*                                                                            */
/* Initial addition of RUDP and ComTracker                                    */
/* Both work with relatively decent tests                                     */
/* Intensive tests to come later                                              */
/*                                                                            */
/******************************************************************************/

#ifndef _COMTRACKER_H_
#define _COMTRACKER_H_

#include <pthread.h>
#include "network.h"
#include "UDP.h"
#include "UDPacket.h"

class ComTracker{
	private:

	/**
	 * This byte array stores which packets have been received
	 **/
	byte recvbuff[32];
	
	/**
	 * This stores the latest '1st missing' byte received
	 **/
	byte recvspot;
	
	/**
	 * Stores the highest consecutive packet received plus 1
	 * That way this stores the first packet that hasn't been 
	 * received consecutively
	 **/
	byte spot;
	
	/**
	 * Stores the sequence number to place on the next outgoing packet
	 **/
	byte sequence;
	
	/**
	 * Stores any packets that haven't been accounted at the index of
	 * their sequence number
	 **/
	UDPacket* buff[256];

	int longest;

	/**
	 *
	 **/
	pthread_mutex_t dataMutex;

	public:
	/**
	 * Constructs a ComTracker
	 **/
	ComTracker();
	
	/**
	 * Retreives the current next8 byte
	 **/
	byte getNext8Byte();
	
	/**
	 * Takes a regular UDPacket and attaches a header to it with the
	 * appropriate sequence number, 1st missing and next8 byte and 
	 * places it into the UDPacket buffer
	 * This method should lock the dataMutex before doing anything,
	 * and then unlock it when its finished.
	 **/
	void attachReliableHeader(UDPacket* to_send);
	
	/**
	 * Takes a regular UDPacket and attaches a header to it with
	 * a sequence number of 0
	 * This method should lock the dataMutex before doing anything,
	 * and then unlock it when its finished.
	 **/
	void attachUnreliableHeader(UDPacket* to_send);
	
	/**
	 * Takes an incoming UDPacket with an RUDP header and 
	 * strips the header off of it, adjusting the information in
	 * recvbuff and recvspot accordingly
	 * This method should lock the dataMutex before doing anything,
	 * and then unlock it when its finished.
	 **/
	void stripHeader(UDPacket* received);
	
	/**
	 * Resends UDPackets that are still stored in the UDPacket buff
	 * This method should lock the dataMutex before doing anything,
	 * and then unlock it when its finished.
	 **/
	void resendMissing(UDP* udp); // Can put TCP* tcp for emergencies later

	/**
	 * Puts the current 1st missing and next8 byte into the buffered
	 * UDPackets
	 **/
	void updatePackets();

	/**
	 * Destroys all buffered RUDP packets
	 **/
	~ComTracker();
};

#endif
