/*
	HTTPS GET
 */
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

//Curl로 url 보내기
void sendDataCurl(const char *addr) {
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
}

#define  BUFF_SIZE   256

int numberOfDrones = 1;
float intervalSec = 0.001;

struct gps {
	double lat;
	double lng;
	double alt;
};

struct gps drone1 = {37.546843, 127.051564, 0};

//조이스틱 움직임 결과
int move(char buff_rcv[BUFF_SIZE+5]){
	int move;
		if(strcmp(buff_rcv,"e")==0){
			drone1.lat += 0.00001;
		}
		if(strcmp(buff_rcv,"w")==0){
			drone1.lat -= 0.00001;
		}
		if(strcmp(buff_rcv,"s")==0){
			drone1.lng -= 0.00001;
		}
		if(strcmp(buff_rcv,"n")==0){
			drone1.lng += 0.00001;
		}
		if(strcmp(buff_rcv,"alt")==0){
			drone1.alt += 1;
		}
	return move;
}

struct DRONE {
	int droneNumber;
};

//url 작성해서 sendDataCurl()로 보내기
void urlwrite(const int numberOfDrones, const float intervalSec, char buff_rcv[BUFF_SIZE+5]){

	const char *urlFormat="https://us-central1-droneserverdev.cloudfunctions.net/addMessage?num=%d&lat=%f&lng=%f&alt=%f";

	struct DRONE drones[numberOfDrones];
	for(int index=0; index<numberOfDrones; index++) {
		drones[index].droneNumber = index + 1;
	}

	char *urlAddr = malloc(256);

	printf("numberOfDrones : %d\n",numberOfDrones);

	move(buff_rcv);

	for(int index=0; index<numberOfDrones; index++) {
		printf("DRONE#%d\n", drones[index].droneNumber);
			
		sprintf(urlAddr, urlFormat, drones[index].droneNumber, drone1.lat, drone1.lng, drone1.alt);
		printf("%s\n", urlAddr);
		sendDataCurl(urlAddr);
	}

	printf("\n");
	sleep(intervalSec);	// n 초 기다림

	free(urlAddr);
}

//서버 소켓
int server_socket(){
	int   server_socket;

	struct sockaddr_in   server_addr;

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

	return server_socket;
}

//서버에서 클라이언트 소켓 정보 받기
void server_listen(int server_socket){

	int   client_socket;
	int   client_addr_size;

	struct sockaddr_in   client_addr;

	char buff_rcv[BUFF_SIZE+5];
	char buff_snd[BUFF_SIZE+5];

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
		
		printf("numberofDrones :%d", numberOfDrones);

		urlwrite(numberOfDrones, intervalSec, buff_rcv);


		close( client_socket);
	}
}


int main()
{
	//numberOfDrones = 2;

	printf("통신 시작\n");
	server_listen(server_socket());

	return 0;
}

