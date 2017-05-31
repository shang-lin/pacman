#include "ComTracker.h"

/**
 * Constructs a ComTracker
 **/
ComTracker::ComTracker(){
	int i;
	for(i=0;i<32;i++){
		recvbuff[i] = 0x00;
	}
	for(i=0;i<256;i++){
		buff[i] = NULL;
	}
	recvspot = 1;
	spot = 1;
	sequence = 1;
	longest = 0;
	pthread_mutex_init(&dataMutex,NULL);
}

/**
 * Used for debugging
 * writes a byte in binary to cout
 **/
void displayByte(byte a){
	for(int i=7;i>=0;i--){
		if((a & (0x01 << i)) != 0){
			cout << "1";
		} else {
			cout << "0";
		}
	}
}

/**
 * Retreives the current next8 byte
 **/
byte ComTracker::getNext8Byte(){
	byte result = 0x00;
	
	if(spot == 255){
		result = result | (recvbuff[0] << 1) | (recvbuff[1] >> 7);
	} else {
		result = result | (recvbuff[(spot+1)/8] << ((spot%8)+1));
		if(((spot+1)/8) == 31){
			result = result | (recvbuff[0] >> (7-(spot%8)));
		} else {
			result = result | (recvbuff[((spot+1)/8)+1] >> (7-(spot%8)));
		}
	}
	//cout << "next8 : ";
	//displayByte(result);
	//cout << "\n";
	return result;
}

/**
 * Takes a regular UDPacket and attaches a header to it with the
 * appropriate sequence number, 1st missing and next8 byte and 
 * places it into the UDPacket buffer
 * This method should lock the dataMutex before doing anything,
 * and then unlock it when its finished.
 **/
void ComTracker::attachReliableHeader(UDPacket* to_send){
	byte newdata[1024];
	const byte* data = to_send->getData();
	int length = to_send->getLength();
	int i;

	pthread_mutex_lock(&dataMutex);

	newdata[0] = sequence;
	newdata[1] = spot;
	newdata[2] = getNext8Byte();
	for(i=0;i<length;i++){
		newdata[i+3] = data[i];
	}
	//cout << "attachReliableHeader:" 
	//		 << (int)newdata[0] << " " 
	//		 << (int)newdata[1] << " "
	//		 << (int)newdata[2] << "\n";
	to_send->setData(newdata,length+3);
	to_send->setLength(length+3);

	UDPacket* to_copy = new UDPacket(to_send);

	buff[sequence] = to_copy;
	sequence = (sequence%255)+1;

	pthread_mutex_unlock(&dataMutex);
}

/**
 * Takes a regular UDPacket and attaches a header to it with
 * a sequence number of 0
 * This method should lock the dataMutex before doing anything,
 * and then unlock it when its finished.
 **/
void ComTracker::attachUnreliableHeader(UDPacket* to_send){
	byte newdata[1024];
	const byte* data = to_send->getData();
	int length = to_send->getLength();
	int i;

	pthread_mutex_lock(&dataMutex);

	newdata[0] = 0;
	newdata[1] = spot;
	newdata[2] = getNext8Byte();
	for(i=0;i<length;i++){
		newdata[i+3] = data[i];
	}
	//cout << "attachUnreliableHeader:" 
	//		 << (int)newdata[0] << " " 
	//		 << (int)newdata[1] << " "
	//		 << (int)newdata[2] << "\n";
	to_send->setData(newdata,length+3);
	to_send->setLength(length+3);

	pthread_mutex_unlock(&dataMutex);
}

// Returns true if b should be considered after a
bool isOrdered(byte a,byte b){
	return ((a < b) && (b <= (a+0x80))) || ((a >= 0xC0) && (b <= 0x40));
}

/**
 * Takes an incoming UDPacket with an RUDP header and 
 * strips the header off of it, adjusting the information in
 * recvbuff and recvspot accordingly
 * This method should lock the dataMutex before doing anything,
 * and then unlock it when its finished.
 **/
void ComTracker::stripHeader(UDPacket* received){
	const byte* data = received->getData();
	int length = received->getLength();
	int i;
	//cout << "stripHeader:" 
	//		 << (int)data[0] << " "
	//		 << (int)data[1] << " "
	//		 << (int)data[2] << "\n";
	
	if(length < 3){
		throw ProtocolException("Malformed RUDP packet");
	}

	pthread_mutex_lock(&dataMutex);

	if((data[0] != 0x00) && isOrdered(spot,data[0]) || spot==data[0]){
		int index = data[0]/8;
		int shift = 7-(data[0]%8);
		byte mask = 0x01 << shift;
		recvbuff[index] = recvbuff[index] | mask;
		if(data[0] == spot){
			while((recvbuff[index] & mask) != 0x00){
				recvbuff[index] = recvbuff[index] - mask;
				shift--;
				if(shift == -1){
					shift = 7;
					index = (index + 1) % 32;
					if(index==0) shift--;
				}
				mask = 0x01 << shift;
			}
			spot = index*8 + (7-shift);
		}
	}

	if(isOrdered(recvspot,data[1])){
		//cout << " updating recvspot from " << (int)recvspot 
		//     << " to " << (int)(data[1]) << "\n";
		for(i=recvspot;i!=data[1];i=(i%255)+1){
			if(buff[i] != NULL){
				delete buff[i];
				buff[i] = NULL;
			}
		}
		recvspot = data[1];
	}
	byte mask = 0x01 << 7;
	i=(data[1]%255)+1;
	for(byte mask = 0x01 << 7;mask != 0x00;mask = mask >> 1){
		if((data[2] & mask) != 0x00 && buff[i] != NULL){
			delete buff[i];
			buff[i] = NULL;
		}
		i=(i%255)+1;
	}

	byte newdata[1024];
	
	for(i=0;i<length-3;i++){
		newdata[i] = data[i+3];
	}
	received->setData(newdata,length-3);
	received->setLength(length-3);

	//cout << "buff :   1         2         3         4         5         6";
	//cout << "         7         8         9        10        11        12";
	//cout << "        13        14        15        16        17        18";
	//cout << "        19        20        21        22        23        24";
	//cout << "        25\n";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345\n";
	//for(int i=1;i<256;i++){
	//	if(buff[i]==NULL){
	//		cout << ".";
	//	} else {
	//		cout << "*";
	//	}
	//}
	//cout << "\n";
	//cout << "recvbuff: 1         2         3         4         5         6";
	//cout << "         7         8         9        10        11        12";
	//cout << "        13        14        15        16        17        18";
	//cout << "        19        20        21        22        23        24";
	//cout << "        25\n";
	//cout << "0123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345678901234567890123456789012345678901234567890";
	//cout << "123456789012345\n";
	//for(int i=0;i<32;i++){
	//	displayByte(recvbuff[i]);
	//}
	//cout << "\n";
	//cout << "  spot=" << (int)spot << "\n";
	//cout << "  recvspot=" << (int)recvspot << "\n";
  
	pthread_mutex_unlock(&dataMutex);

}

/**
 * Puts the current 1st missing and next8 byte into the buffered
 * UDPackets
 **/
void ComTracker::updatePackets(){
	for(int i=0;i<256;i++){
		if(buff[i] != NULL){
			buff[i]->setData(1,spot);
			buff[i]->setData(2,getNext8Byte());
		}
	}
}

/**
 * Resends UDPackets that are still stored in the UDPacket buff
 * This method should lock the dataMutex before doing anything,
 * and then unlock it when its finished.
 **/
void ComTracker::resendMissing(UDP* udp){

	pthread_mutex_lock(&dataMutex);

	updatePackets();
	int numInBuff = 0;
	for(int i=1;i<256;i++){
		if(buff[i] != NULL){
			//cout << "resending packet:" 
			//		 << buff[i]->getLength() << " "
			//		 << (int)(buff[i]->getData(0)) << " "
			//		 << (int)(buff[i]->getData(1)) << " "
			//		 << (int)(buff[i]->getData(2)) << " "
			//		 << (int)(buff[i]->getData(3)) << "\n";
			udp->sendPacket(buff[i]);
			numInBuff++;
		}
	}
	if(longest < numInBuff){
		longest = numInBuff;
		cerr << numInBuff << "/" << longest << " : ";
	}

	pthread_mutex_unlock(&dataMutex);

}

/**
 * Destroys all buffered RUDP packets
 **/
ComTracker::~ComTracker(){
	for(int i=1;i<256;i++){
		if(buff[i] != NULL){
			delete buff[i];
		}
	}
	pthread_mutex_destroy(&dataMutex);
}
