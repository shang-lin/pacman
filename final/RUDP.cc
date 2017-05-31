#include "RUDP.h"


/**
 * Creates a new ComTracker object and places it in the
 * stl map with the specified string as a key
 **/
ComTracker* RUDP::newTracker(string key){
	ComTracker* ct = new ComTracker();
	trackers[key] = ct;
	return ct;
}

/**
 * Creates a reliable UDP object on the specified port
 **/
RUDP::RUDP(int port){
	udp = new UDP(port);
}

/**
 * Returns whether there is a UDPacket ready to be read
 **/
bool RUDP::isReady(){
	return udp->isReady();
}

/**
 * Attaches a reliable RUDP header onto the specified packet
 * and sends it via RUDP
 **/
void RUDP::sendReliable(UDPacket* to_send){
	const sockaddr_in* address = to_send->getAddress();
	string key = addressToString(address);
	map<string,ComTracker*>::iterator mi = trackers.find(key);
	ComTracker* ct;
	if(mi == trackers.end()){
		ct = newTracker(key);
	} else {
		ct = mi->second;
	}
	ct->attachReliableHeader(to_send);
	udp->sendPacket(to_send);
}

/**
 * Attaches an unreliable RUDP header onto the specified packet
 * and sends it via RUDP
 **/
void RUDP::sendUnreliable(UDPacket* to_send){
	const sockaddr_in* address = to_send->getAddress();
	string key = addressToString(address);
	map<string,ComTracker*>::iterator mi = trackers.find(key);
	ComTracker* ct;
	if(mi == trackers.end()){
		ct = newTracker(key);
	} else {
		ct = mi->second;
	}
	ct->attachUnreliableHeader(to_send);
	udp->sendPacket(to_send);
}

/**
 * Receives a UDP packet with an RUDP header, strips the header
 * and fills the specified packet with the header-free data
 **/
void RUDP::receivePacket(UDPacket* packet){
	udp->receivePacket(packet);
	const sockaddr_in* address = packet->getAddress();
	string key = addressToString(address);
	map<string,ComTracker*>::iterator mi = trackers.find(key);
	ComTracker* ct;
	if(mi == trackers.end()){
		ct = newTracker(key);
	} else {
		ct = mi->second;
	}
	ct->stripHeader(packet);
}

/**
 * Resends all packets that haven't been confirmed 
 * by all communications partners
 **/
void RUDP::resendUnsent(){
	for(
			map<string,ComTracker*>::iterator mi=trackers.begin();
			mi != trackers.end();
			mi++){
		mi->second->resendMissing(udp);
	}
}

/**
 * Shuts down this RUDP object and disconnects its 
 * underlying UDP object
 **/
void RUDP::disconnect(){
	udp->disconnect();
}

/**
 * Destroys this RUDP object and all its ComTrackers
 **/
RUDP::~RUDP(){
	for(
			map<string,ComTracker*>::iterator mi=trackers.begin();
			mi != trackers.end();
			mi++){
		delete mi->second;
	}
	delete udp;
}
