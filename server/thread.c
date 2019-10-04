#include "thread.h"

void *t_server(void *data)
{
    while (1)
    {
		server();
        sleep(1);  // 1초간 대기
    }
}

void *t_urlwrite(void *data)
{ 
    while (1)
    {
		urlwrite(droneNumber, intervalSec);
        sleep(3);  // 3초간 대기
    }
}