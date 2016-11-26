#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "shared_definitions.h"
#include "log.h"

void usage(){
	printf("./run-d -i <ip> -p <port> -m <msg>\n");
	printf("-i <ip>   : the ip for sending udp packets\n");
	printf("-p <port> : the port for sending udp packets\n");
	printf("-m <msg>  : message to be sent\n");
}

int main(int argc, char *argv[] ){
	int opt;
	char *ipstr = NULL;
	int port;
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


	return 0;
}
