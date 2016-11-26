#ifndef __udpCom
#define __udpCom

int makeConnection(char *ip, int port);
int sendUdp(int s, void *msg, int len);

#endif
