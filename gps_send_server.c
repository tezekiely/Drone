/* <DESC>
 * Simple HTTPS GET
 * </DESC>
 */ 
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int   main( void)
{
	// server.c 부분

   int   server_socket;
   int   client_socket;
   int   client_addr_size;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   char   buff_rcv[BUFF_SIZE+5];
   char   buff_snd[BUFF_SIZE+5];



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

	// bind 에러 방지
	int option;
	option = 1;          // SO_REUSEADDR 의 옵션 값을 TRUE 로
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


	char *format="https://us-central1-droneserverdev.cloudfunctions.net/addMessage?lat1=%f&lng1=%f&alt1=%f&lat2=%f&lng2=%f&alt2=%f&lat3=%f&lng3=%f&alt3=%f";


		float lat1,lng1,alt1;
		float lat2,lng2,alt2;
		float lat3,lng3,alt3;

		lat1=37.546843; lng1=127.051564; alt1=3;
		lat2=37.546803; lng2=127.051548; alt2=2;
		lat3=37.546925; lng3=127.051590; alt3=3;



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
      

// gps_send.c 부분
		
		if(strcmp(buff_rcv,"altup")==0){
				alt1+=1;
		}


		char *addr = malloc(1024);

		sprintf(addr,format,lat1,lng1,alt1,lat2,lng2,alt2,lat3,lng3,alt3);

		printf("%s\n", addr);

		CURL *curl;
		CURLcode res;
	
		curl_global_init(CURL_GLOBAL_DEFAULT);

		curl = curl_easy_init();
		if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, addr);
 
		#ifdef SKIP_PEER_VERIFICATION
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */ 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
 
    /* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
    /* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
	
		printf("\n");

    /* always cleanup */ 
		curl_easy_cleanup(curl);
		}
		curl_global_cleanup();

		sleep(0.05);
		free(addr);

//		return 0;

//      sprintf( buff_snd, "%d : %s", strlen( buff_rcv), buff_rcv);
//      write( client_socket, buff_snd, strlen( buff_snd)+1);          // +1: NULL까지 포함해서 전송
      close( client_socket);
   }
}
