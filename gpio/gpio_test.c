#include <stdio.h>
#include <wiringPi.h>

#define Lsw	0	// GPIO.0, BCM_GPIO 17
#define Rsw	2	// GPIO.2, BCM_GPIO 27

int main (void)
{
	if (wiringPiSetup() == -1)
		return 1 ;

	pinMode(Lsw, INPUT);
	pinMode(Rsw, INPUT);

	pullUpDnControl(Lsw, PUD_UP);
	pullUpDnControl(Rsw, PUD_UP);

	for(;;){
		if(digitalRead(Lsw) == 0 && digitalRead(Rsw) == 0)
		{
			printf("LRsw\n");
			delay(100) ;             // mS
		}
		else if(digitalRead(Lsw) == 0)
		{
			printf("Lsw\n");
			delay(100) ;             // mS
		}
		else if(digitalRead(Rsw) == 0)
		{
			printf("Rsw\n");
			delay(100) ;             // mS
		}

		
	}
	return 0 ;
}