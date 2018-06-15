/*

	This code is released under the following license:
		- You may use the code for personal (non-commercial) projects free of charge on conditions that: (1) credit is given in any write-ups of the project, and (2) your code changes (if any) are made public at the same time as the project is.
		- You must contact Dmitry Grinberg (dmitrygr@gmail.com) if you would like to use this code in a commercial project.
		- If you do not agree to these terms, you may not use this code.

	A lot of hard work went into figuring all this out, so please respect the above.
*/



#include <stdio.h>
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned long UInt32;

const char serialNumChars[] = "0123456789ABCDEFGHJKLMNPQRSTUVWXYZ";
const UInt8 randomTable1[] = {1, 4, 15, 12, 8, 2, 3, 6, 14, 0, 5, 7, 13, 10, 9, 11};
const UInt8 randomTable2[] = {0x67, 0x6, 0x51, 0xb8, 0x4a, 0xca, 0x35, 0x3e, 0x72, 0x85, 0x12, 0xd4, 0x8e, 0x9d, 0x1c, 0x23};


UInt8 getSrcFlags(const UInt8* packet){

	return packet[0];	
}

UInt8 getDstFlags(const UInt8* packet){

	return (getSrcFlags(packet) & 0x80) ? packet[1] : 0;
}

UInt8 getSrcTypeLen(const UInt8* packet){

	return packet[0] & 3;	
}

UInt8 getSrcAddrLen(const UInt8* packet){

	UInt8 ret = packet[0];
	
	if(!(ret & 3)) return 0;
	
	return ((ret & 0x0C) >> 2) + 1;
}

UInt8 getDstAddrLen(const UInt8* packet){

	UInt8 ret = getDstFlags(packet);
	
	if(!(ret & 3)) return 0;
	
	return ((ret & 0x0C) >> 2) + 1;	
}

UInt8 getDstTypeLen(const UInt8* packet){
	
	return getDstFlags(packet) & 3;
}

UInt8* getPayloadPtr(UInt8* packet){

	UInt8 L1, L2, L3;
	
	
	L1 = getSrcTypeLen(packet);
	L2 = getSrcAddrLen(packet);
	L3 = getDstTypeLen(packet) + getDstAddrLen(packet);
	L3 += L3 ? ((getDstFlags(packet) & 0x10) ? 2 : 1) : 0;

	return packet + L1 + L2 + L3 + 2;
}

static UInt32 getAddr(const UInt8* ptr, UInt8 sz){

	UInt8 bytes[4] = {0};
	switch((sz >> 2) & 3){
		
		case 3:
			
			bytes[3] = ptr[3];
		
		case 2:
		
			bytes[2] = ptr[2];
		
		case 1:
		
			bytes[1] = ptr[1];
		
		case 0:
		
			bytes[0] = ptr[0];
	}

	return (((UInt32)(bytes[3])) << 24) | (((UInt32)(bytes[2])) << 16) | (((UInt32)(bytes[1])) << 8) | ((UInt32)(bytes[0]));
}

static UInt32 getSrcAddr(const UInt8* packet){

	UInt8 t, f = getSrcFlags(packet);
	
	t = (f & 3);
	if(!t) return 0;

	packet += t + 1;
	if(f & 0x80) packet++;

	return getAddr(packet, f);
}

static UInt32 getDstAddr(const UInt8* packet){

	UInt8 L1, L2, L3;

	L1 = getDstTypeLen(packet);
	if(!L1) return 0;

	L2 = getDstFlags(packet);
	L3 = getSrcTypeLen(packet) + getSrcAddrLen(packet);

	packet += L1 + 2 + L3;
	return getAddr(packet, L2);
}

static UInt16 getType(const UInt8* ptr, UInt8 len){
	
	UInt16 t = 0;
	switch(len){
	
		case 2:
			t |= ((UInt16)ptr[1]) << 8;
			
		case 1:
			t |= ptr[0];
	}
	return t;
}

static UInt16 getSrcType(const UInt8* packet){

	return getType(packet + 2, getSrcTypeLen(packet) - 1);
}

static UInt16 getDstType(const UInt8* packet){

	return getType(packet + getSrcTypeLen(packet) + getSrcAddrLen(packet) + 1, getDstTypeLen(packet) - 1);
}



UInt8 getPayloadLen(UInt8* packet){

	UInt8* payload = getPayloadPtr(packet);
	
	return packet + 28 - payload;
}

UInt8 getTimingByte(const UInt8* packet){

	UInt8 L1, L2, L3;

	L1 = getSrcTypeLen(packet);
	L2 = getSrcAddrLen(packet);
	L3 = getDstTypeLen(packet);
	L3 += getDstAddrLen(packet);
	if(L3) L3++;
	
	return packet[L1 + L2 + L3 + 1];
}

void descramblePayload(UInt8* packet){

	UInt8* payload;
	UInt16 srcAddr, tR;
	UInt8 t2 = 0, t1 = 0, t3, t9 = 0x23, i;
	UInt8 payloadLen, timingByte;
	
	
	payload = getPayloadPtr(packet);
	srcAddr = getSrcAddr(packet);
	payloadLen = getPayloadLen(packet);
	
	timingByte = getTimingByte(packet);
		
	if(srcAddr & 0x0080UL) t2 |= 4;
	if(srcAddr & 0x2000UL) t2 |= 2;
	if(srcAddr & 0x0400UL) t2 |= 1;
	
	if(srcAddr & 0x1000UL) t1 |= 4;
	if(srcAddr & 0x0008UL) t1 |= 2;
	if(srcAddr & 0x8000UL) t1 |= 1;
	
	i = 0;
	tR = srcAddr >> t1;
	timingByte += t2;
		
	for(i = 0; i < payloadLen; i++, payload++, timingByte++){
	
		timingByte &= 0x0F;
		t3 = randomTable1[timingByte];
		
		t3 += tR;
		t3 &= 0x0F;
		t3 = randomTable2[t3];
		t3 ^= t9;

		t9 = *payload;
		*payload = t9 - t3;
		if(t1 <= 11){
			
			t1++;
			tR >>= 1;
		}
		else{
		
			t1 = 0;
			tR = srcAddr;
		}
	}
}


void calcSN(UInt32 sn, UInt8* decodedPacket, char* dst){	//will give partial SN even without a full packet!

	UInt16 t;

	sn += 0xFF000000;

	dst[7] = serialNumChars[sn % 34];	//without the DECODED packet we can only do so much:
	sn /= 34;
	dst[6] = serialNumChars[sn % 34];
	sn /= 34;
	dst[5] = serialNumChars[sn % 34];
	sn /= 34;
	t = sn % 1156;
	sn /= 1156;
	
	dst[3] = serialNumChars[(t % 54) / 10];
	dst[4] = serialNumChars[(t % 54) % 10];
	dst[2] = serialNumChars[t / 54];
	dst[1] = serialNumChars[sn % 34];
	sn /= 34;
	
	
	if(decodedPacket){	//we can do more
		
		UInt8* p = getPayloadPtr(decodedPacket) + 0x10;
		UInt32 x = 0;
		
		x = (x << 8) | (p[2] & 0x1F);
		x = (x << 8) | p[1];
		x = (x << 8) | p[0];
		
		dst[10] = serialNumChars[x % 34];
		x /= 34;
		
		dst[9] = serialNumChars[x % 34];
		x /= 34;
		
		dst[8] = serialNumChars[x % 34];
		x /= 34;
		
		dst[0] = serialNumChars[x % 34];
	}
	else{
	
		dst[0] = '?';
		dst[8] = '?';
		dst[9] = '?';
		dst[10] = '?';
	}
	
	dst[11] = 0;
}

UInt16 getOnHours(UInt8* payload){

	return (((UInt16)(payload[18] & 0xE0)) << 3) + payload[1];	
}

UInt32 getRunningStepCount(UInt8* payload){

	UInt32 r = 0;

	r = (r << 8) | payload[12];
	r = (r << 8) | payload[11];
	r = (r << 8) | payload[10];
	
	return r;	
}

UInt32 getWalkingStepCount(UInt8* payload){

	UInt32 r = 0;

	r = (r << 8) | payload[6];
	r = (r << 8) | payload[5];
	r = (r << 8) | payload[4];
	
	return r;	
}

UInt32 getLifetimeRunningMiles(UInt8* payload){ // mul by 64 and div by 18947.368115186691 to get actual miles

	UInt32 r = 0;

	r = (r << 8) | payload[15];
	r = (r << 8) | payload[14];
	r = (r << 8) | payload[13];
	
	return r;	
}

UInt32 getLifetimeWalkingMiles(UInt8* payload){	// mul by 64 and div by 15319.148451089859 to get actual miles

	UInt32 r = 0;

	r = (r << 8) | payload[9];
	r = (r << 8) | payload[8];
	r = (r << 8) | payload[7];
	
	return r;
}

UInt16 getTc(UInt8* payload){	//what the hell is "Tc" anyways?
	
	UInt16 r = 0;
	
	r = (r << 8) | payload[3];
	r = (r << 8) | payload[2];
	
	return r & 0x7FF;
}

const char* getDeviceType(UInt8 device){

	switch(device){
		case 0x01:
			return "Polar heart rate monitor";
		case 0x06:
			return "Nike+ foot sensor";
		case 0x0D:
			return "Nike+ Amp+ remote";
		default:
			return "Unknown device";
	}
}

void printd(const UInt8* d, UInt8 sz){

	while(sz) printf((sz--) ? "%02X " : "%02X", *d++);
}

void process(UInt8* packet){

	char sn[12];
	UInt8* payload;
	
	descramblePayload(packet);
	payload = getPayloadPtr(packet);
	calcSN(getSrcAddr(packet), packet, sn);
	printf("  FRAME:\n");
	printf("    -> src flags: 0x%02X\n", getSrcFlags(packet));
	printf("    -> src type len: 0x%02X\n", getSrcTypeLen(packet));
	printf("    -> src type: 0x%04X\n", getSrcType(packet));
	printf("    -> src addr len: 0x%02X\n", getSrcAddrLen(packet));
	printf("    -> src addr: 0x%08lX\n", getSrcAddr(packet));
	printf("    -> dst flags: 0x%02X\n", getDstFlags(packet));
	printf("    -> dst type len: 0x%02X\n", getDstTypeLen(packet));
	printf("    -> dst type: 0x%04X\n", getDstType(packet));
	printf("    -> dst addr len: 0x%02X\n", getDstAddrLen(packet));
	printf("    -> dst addr: 0x%08lX\n", getDstAddr(packet));
	printf("    -> timing byte = 0x%02X\n", getTimingByte(packet));
	printf("    -> payload len = 0x%02X\n", getPayloadLen(packet));
	printf("  DATA:\n");
	printf("    ->packet is from device type '%s'\n", getDeviceType(payload[0]));
	if(payload[0] == 0x06){
	printf("    ->packet is from device '%s'\n", sn);
		printf("    ->Nike+ foot pod data:\n");
		printf("        ->on hours: %d\n", getOnHours(payload));
		printf("        ->Tc: %d\n", getTc(payload));
		printf("        ->walking steps: %lu\n", getWalkingStepCount(payload)); 
		printf("        ->running steps: %lu\n", getRunningStepCount(payload));
		printf("        -> lifetime walking miles: %lu\n", getLifetimeWalkingMiles(payload));
		printf("        -> lifetime running miles: %lu\n", getLifetimeRunningMiles(payload));
	}
	printf("    ->raw payload: ");
	printd(payload, getPayloadLen(packet));
	printf("\n");
}

int hexv(char c){

	if(c >= '0' && c <= '9') return c - '0';
	if(c >= 'A' && c <= 'F') return c + 10 - 'A';
	if(c >= 'a' && c <= 'f') return c + 10 - 'a';
	return -1;
}

int readPacket(char* dst){

	int c;
	int tik = 0;
	int v, t, d = 0;
	
	while((c = getchar()) != EOF && c != '\n'){
		
		t = hexv(c);
		if(t == -1) continue;
		if(tik){
			*dst++ = (v << 4) | t;
			d = 1;
		}
		else{
			v = t;
		}
		tik = !tik;
	}
	
	printf("\n");
	*dst = 0;
	
	return d;
}

int main(int argc, char** arv){
	
	char packet[32];
	int i = 0;
	
	
	
	while(readPacket(packet)){
	
		i++;
		printf("Packet %d:\n", i);
		process(packet);
	}
	
	
	return 0;
}