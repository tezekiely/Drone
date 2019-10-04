#include "send.h"
#include <math.h>

#define PI 3.141592

///경도(longitude) || 동서
//위도(latitude) = 남북

struct gps drone[5] = {
	{ .active = "OFF", .lat = 37.546823, .lng = 127.051520, .alt = 0, .rotate = 0},
	{ .active = "OFF", .lat = 37.546843, .lng = 127.051564, .alt = 0, .rotate = 0},
	{ .active = "OFF", .lat = 37.546803, .lng = 127.051548, .alt = 0, .rotate = 0},
	{ .active = "OFF", .lat = 37.546925, .lng = 127.051590, .alt = 0, .rotate = 0},
	{ .active = "OFF", .lat = 37.546900, .lng = 127.051575, .alt = 0, .rotate = 0}
};

int count = 0;

//조이스틱 움직임 결과

void move(int i, char *buff_rcv){

	char *UpDown = malloc(256);
	char *Rotate = malloc(256);
	char *FBRL = malloc(256);
	char *Switch = malloc(256);

	sscanf(buff_rcv,"%s %s %s %s", UpDown, Rotate, FBRL, Switch);

	printf("UpDown : %s\n", UpDown);
	printf("Rotate : %s\n", Rotate);
	printf("FBRL : %s\n", FBRL);
	printf("Switch : %s\n", Switch);

	if(strcmp(drone[i].active, "OFF")==0 && strcmp(Switch, "LRsw")==0){
		count++;
		if(count==10){
			strcpy(drone[i].active, "ON");
			count = 0;
		}
	}
	else if(strcmp(drone[i].active, "ON")==0 && strcmp(Switch, "LRsw")==0){
		count++;
		if(count==10){
			strcpy(drone[i].active, "OFF");
			count = 0;
		}
	}

	printf("active : %s\n", drone[i].active);
	

	if(strcmp(drone[i].active, "ON")==0){
		if(strcmp(UpDown,"U")==0){
			drone[i].alt += 0.1;
		}
		if(strcmp(UpDown,"D")==0){
			drone[i].alt -= 0.1;
		}


		if(strcmp(Rotate,"Rr")==0){
			drone[i].rotate += 1;
		}
		if(strcmp(Rotate,"Lr")==0){
			drone[i].rotate -= 1;
		}


		if(strcmp(FBRL,"F")==0){
				drone[i].lng += 0.000001*sin(drone[i].rotate*(PI/180));
				drone[i].lat += 0.000001*cos(drone[i].rotate*(PI/180));
		}
		if(strcmp(FBRL,"FR")==0){
				drone[i].lng += 0.000001*sin((drone[i].rotate+45)*(PI/180));
				drone[i].lat += 0.000001*cos((drone[i].rotate+45)*(PI/180));
		}
		if(strcmp(FBRL,"FL")==0){
				drone[i].lng += 0.000001*sin((drone[i].rotate-45)*(PI/180));
				drone[i].lat += 0.000001*cos((drone[i].rotate-45)*(PI/180));
		}

		if(strcmp(FBRL,"B")==0){
				drone[i].lng += 0.000001*sin((drone[i].rotate+180)*(PI/180));
				drone[i].lat += 0.000001*cos((drone[i].rotate+180)*(PI/180));
		}
		if(strcmp(FBRL,"BR")==0){
				drone[i].lng += 0.000001*sin((drone[i].rotate+135)*(PI/180));
				drone[i].lat += 0.000001*cos((drone[i].rotate+135)*(PI/180));
		}
		if(strcmp(FBRL,"BL")==0){
				drone[i].lng += 0.000001*sin((drone[i].rotate+225)*(PI/180));
				drone[i].lat += 0.000001*cos((drone[i].rotate+225)*(PI/180));
		}

		if(strcmp(FBRL,"R")==0){
				drone[i].lng += 0.000001*cos(drone[i].rotate*(PI/180));
				drone[i].lat -= 0.000001*sin(drone[i].rotate*(PI/180));
		}
		if(strcmp(FBRL,"L")==0){
				drone[i].lng -= 0.000001*cos(drone[i].rotate*(PI/180));
				drone[i].lat += 0.000001*sin(drone[i].rotate*(PI/180));
		}
	}

	free(UpDown);
	free(Rotate);
	free(FBRL);
	free(Switch);

}