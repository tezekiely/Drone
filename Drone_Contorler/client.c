#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "control.h"

#define  BUFF_SIZE   256

int   main()
{
   int   client_socket;

   struct sockaddr_in   server_addr;

   char   *buff = malloc(BUFF_SIZE+5);

	char *input = malloc(256);

	while(!(strcmp(input,"close")==0)){
		
		input = strcat(control(), Switch());
		//scanf("%s", input);
		printf("input : ");
		printf("%s\n", input);

		char **argv = &input;

		client_socket  = socket( PF_INET, SOCK_STREAM, 0);
		if( -1 == client_socket)
		{
			printf( "socket 생성 실패\n");
			exit( 1);
		}

		memset( &server_addr, 0, sizeof( server_addr));
		server_addr.sin_family     = AF_INET;
		server_addr.sin_port       = htons( 25666);
		server_addr.sin_addr.s_addr= inet_addr( "192.168.0.111");

		if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
		{
			printf( "접속 실패\n");
			exit( 1);
		}

		write( client_socket, *argv, strlen(*argv)+1);  
		read ( client_socket, buff, BUFF_SIZE);

	}
	close( client_socket);

	free(input);
	free(buff);

	return 0;
}
