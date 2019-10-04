#include "send.h"

void server(){
    int   server_socket;
    int   client_socket;
    int   client_addr_size;

    struct sockaddr_in   server_addr;
    struct sockaddr_in   client_addr;

	char   *buff_rcv = malloc(BUFF_SIZE+5);

	server_socket  = socket( PF_INET, SOCK_STREAM, 0);
	if( -1 == server_socket)
	{
		printf( "server socket 생성 실패\n");
		exit( 1);
	}

	memset( &server_addr, 0, sizeof( server_addr));
	server_addr.sin_family     = AF_INET;
	server_addr.sin_port       = htons(25666);
	server_addr.sin_addr.s_addr= htonl( INADDR_ANY);

	int option;
	option = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
		
	if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	{
		printf( "bind() 실행 에러\n");
		exit( 1);
	}

	if( -1 == listen(server_socket, 5))
	{
		printf( "listen() 실행 실패\n");
		exit( 1);
	}

		int count;
		count =0;

	while( 1)
	{

		client_addr_size  = sizeof( client_addr);
		client_socket     = accept( server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

		if ( -1 == client_socket)
		{
			printf( "클라이언트 연결 수락 실패\n");
			exit( 1);
		}

		read ( client_socket, buff_rcv, BUFF_SIZE);
		printf( "receive: %s\n", buff_rcv);

		move(droneNumber, buff_rcv);

///		urlwrite(droneNumber, intervalSec, buff_rcv);

		printf("count : %d\n", count++ );
		printf("lat: %lf, lng: %lf, alt: %lf, rotation: %lf\n\n", drone[droneNumber].lat, drone[droneNumber].lng, drone[droneNumber].alt, drone[droneNumber].rotate);

		close( client_socket);
		usleep(200000);
	}
	free(buff_rcv);
}
	
	