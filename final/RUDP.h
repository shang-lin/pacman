/******************************************************************************/
/* RCS file: /www/cvs/pacman/network/RUDP.h,v                                 */
/* Working file: RUDP.h                                                       */
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

#ifndef _RUDP_H_
#define _RUDP_H_

#include <string>
#include <map>
#include "network.h"
#include "UDP.h"
#include "ComTracker.h"

class RUDP{
	private:
	UDP* udp;
	map<string,ComTracker*> trackers;

	/**
	 * Creates a new ComTracker object and places it in the
	 * stl map with the specified string as a key
	 **/
	ComTracker* newTracker(string key);

	public:
	/**
	 * Creates a reliable UDP object on the specified port
	 **/
	RUDP(int port);

	/**
	 * Returns whether there is a UDPacket ready to be read
	 **/
	bool isReady();
	
	/**
	 * Attaches a reliable RUDP header onto the specified packet
	 * and sends it via RUDP
	 **/
	void sendReliable(UDPacket* to_send);
	
	/**
	 * Attaches an unreliable RUDP header onto the specified packet
	 * and sends it via RUDP
	 **/
	void sendUnreliable(UDPacket* to_send);
	
	/**
	 * Receives a UDP packet with an RUDP header, strips the header
	 * and fills the specified packet with the header-free data
	 **/
	void receivePacket(UDPacket* packet);

	/**
	 * Resends all packets that haven't been confirmed 
	 * by all communications partners
	 **/
	void resendUnsent();

	/**
	 * Shuts down this RUDP object and disconnects its 
	 * underlying UDP object
	 **/
	void disconnect();

	/**
	 * Destroys this RUDP object and all its ComTrackers
	 **/
	~RUDP();
};

#endif
