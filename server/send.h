#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   256

int droneNumber;
float intervalSec;

struct gps {
	char active[4];
	double lat;
	double lng;
	double alt;
	double rotate;
};

struct gps drone[5];

void urlwrite(const int droneNumber, const float intervalSec);

void move(int i, char *buff_rcv);

void sendDataCurl(const char *addr);

void server();