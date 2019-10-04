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

// 드론 번호를 주어서 해당 드론 txt 파일에서 line 번호의 한줄을 읽어 온다. 어디로? lineBuff 로....
// return :
//    -1 : 에러
//    그외 : 읽은 buff 바이트수
int readDroneDataLine(int droneNumber, int lineNumber, char *lineBuff, int buffLen)
{
	int ret = -1;
	
	FILE *fp;
	char *filename = malloc(256);
	sprintf(filename, "drones/test_drone_%d.txt", droneNumber);

	printf("droneNumber=%d\n", droneNumber);
	printf("filename=%s\n", filename);

	fp = fopen(filename, "rt");
	if(fp==NULL) return ret;

	int lineCount = 0;
	while(1) {
		if(feof(fp)) break;
		char *s = fgets(lineBuff, buffLen-1, fp);
		if(s==NULL) {
			break;
		}
		lineCount++;
		if(lineCount==lineNumber) {
			ret = strlen(lineBuff);
			break;
		}
	}
	fclose(fp);
	free(filename);
	return ret;
}

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

#define  BUFF_SIZE   1024

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

void client_socket(){
	
	int   server_socket;
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

		close( client_socket);
	}
}


struct DRONE {
	int droneNumber;
	int lineNumber;
};


int main(int argc, char **argv)
{	
	const int numberOfDrones = atoi(argv[1]);
	const float intervalSec = atof(argv[2]);
	const char *urlFormat="https://us-central1-droneserverdev.cloudfunctions.net/addMessage?num=%d&lat=%f&lng=%f&alt=%f";

 	struct DRONE drones[numberOfDrones];
	for(int index=0; index<numberOfDrones; index++) {
		drones[index].droneNumber = index + 1;
		drones[index].lineNumber = 1;
	}

/*
	printf("서버 함수 앞\n");
	client_socket(server_socket());
	printf("서버함수 뒤\n");
*/

	int buffLen = 1024;
	char *lineBuff = malloc(buffLen);
	while(1) {
		for(int index=0; index<numberOfDrones; index++) {	
			int ret = readDroneDataLine(drones[index].droneNumber, drones[index].lineNumber, lineBuff, buffLen);
			printf(">>> index %d ret %d\n", index, ret);
			if(ret==-1) {
				drones[index].lineNumber = 1;
			} else {
				printf("DRONE#%d > %03d : %s", drones[index].droneNumber, drones[index].lineNumber, lineBuff);
			
				double lat,lng,alt;
				int n = sscanf(lineBuff,"%lf,%lf,%lf",&lat,&lng,&alt);

				if(n==3) {
					char *urlAddr = lineBuff;
					sprintf(urlAddr, urlFormat, drones[index].droneNumber, lat, lng, alt);
					printf("%s\n", urlAddr);
					sendDataCurl(urlAddr);
				}
				drones[index].lineNumber++;
			}
		}
		printf("\n");
		sleep(intervalSec);	// n 초 기다림
	}
	free(lineBuff);

	return 0;
}

