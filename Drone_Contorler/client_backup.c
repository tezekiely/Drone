#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int   main( int argc, char **argv)
{
   int   client_socket;

   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

	   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
	   if( -1 == client_socket)
	   {
	      printf( "socket ���� ����\n");
	      exit( 1);
	   }

	   memset( &server_addr, 0, sizeof( server_addr));
	   server_addr.sin_family     = AF_INET;
	   server_addr.sin_port       = htons( 25666);
	   server_addr.sin_addr.s_addr= inet_addr( "192.168.0.104");

	   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	   {
	      printf( "���� ����\n");
	      exit( 1);
	   }

	   write( client_socket, argv[1], strlen( argv[1])+1);      // +1: NULL���� �����ؼ� ����
	   read ( client_socket, buff, BUFF_SIZE);
	   printf( "%s\n", buff);
   
		
		close( client_socket);

   return 0;
}
