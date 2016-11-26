#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shared_definitions.h"
#include "log.h"
#include "com.h"

void usage(){
	printf("./run-d -i <ip> -p <port> -m <msg>\n");
	printf("-i <ip>   : the ip for sending udp packets\n");
	printf("-p <port> : the port for sending udp packets\n");
	printf("-m <msg>  : message to be sent\n");
}

int main(int argc, char *argv[] ){
	int opt;
	char *ipstr = NULL;
	int port = -1;
	int config = 0;
	char *msg = NULL;
	while ( (opt = getopt(argc, argv, "i:p:m:hH") ) != -1 ){
		switch ( opt ){

			case 'i':
				if ( ( ipstr = malloc(strlen(argv[optind-1])+1) ) == NULL ){
					FATAL("Memory failure. Process will terminate")
					return -1;
				}
				strcpy(ipstr, argv[optind-1]);
				config++;
				break;

			case 'p':
				port= atoi( argv[optind-1]);
				config++;
				break;

			case 'm':
				msg = argv[optind-1];
				config++;
				break;

			case 'h':
			case 'H':
				usage();
				return 0;
			default:
				usage();
				return -1;
		}
	}
	if ( config != 3){
		if ( port == -1 ){
			usage();
			return -1;
		}
		if ( ipstr == NULL ){
			if ( ( ipstr = malloc( strlen("127.0.0.1")+1 ) ) == NULL ){
				FATAL("Memory failure. Process will terminate")
				return -1;
			}
			strcpy(ipstr, "127.0.0.1");
		}

	}
	int socket;
	if ( (socket = makeConnection(ipstr, port) ) == -1 ){
		FATAL("Can not open udp socket for sending")
		return -1;
	}
	if ( msg == NULL){
		if ( ( msg = malloc(1024)) == NULL ){
			FATAL("Memory failure");
			return -1;
		}
		while (1){
			printf("MSG ? (type \"quit\" for exit):");
			scanf("%s", msg);
			if ( !strcmp(msg, "quit") ){
				free(msg);
				LOG("quit received.. exit!")
				break;
			}
			printf("sending :%s\n", msg);
		}
	}else{
		printf("Sending :%s\n", msg);
		if ( sendUdp(socket, msg, strlen(msg)) == -1){
			FATAL("Cannot sent message\n")
			return -1;
		}
	}
	return 0;
}
