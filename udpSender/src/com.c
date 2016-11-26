#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "log.h"

struct sockaddr_in si_other;

int makeConnection(char *ip, int port){
	TRACE_IN
	int s;
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
		FATAL("Unable to create socket")
		TRACE_OUT
		return -1;
	}
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	if (inet_aton(ip, &si_other.sin_addr)==0) {
		FATAL("inet_aton() failed");
		TRACE_OUT
		return -1;
	}
	TRACE_OUT
    return s;
}

int sendUdp(int s, void *msg, int len){
	TRACE_IN
	int offset = 0, res;
	while( offset < len){
		if (  ( res = sendto(s, msg+offset, len-offset, 0, (struct sockaddr *)&si_other, sizeof(si_other) ) ) == -1 ){
			FATAL("Msg was not sent correctly")
			return -1;
		}else{
			offset += res;
		}
	}
	TRACE_OUT
	return offset;
}
