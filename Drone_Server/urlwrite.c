#include "send.h"

//url 작성해서 sendDataCurl()로 보내기
void urlwrite(const int droneNumber, const float intervalSec){

	const char *urlFormat="https://us-central1-droneserverdev.cloudfunctions.net/addMessage?num=%d&active=%s&lat=%f&lng=%f&alt=%f&rot=%f";

	char *urlAddr = malloc(256);

	printf("DRONE#%d\n", droneNumber);

	sprintf(urlAddr, urlFormat, droneNumber, drone[droneNumber].active, drone[droneNumber].lat, drone[droneNumber].lng, drone[droneNumber].alt, drone[droneNumber].rotate);
	printf("%s\n", urlAddr);
	sendDataCurl(urlAddr);

	printf("\n");
	sleep(intervalSec);	// n 초 기다림

	free(urlAddr);
}