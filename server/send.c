#include <stdio.h>
#include <pthread.h>
#include "thread.h"

int main(int argc, char **argv)
{
	/// ./send 1(드론 번호) 2(Firebase 업데이트 딜레이))

	droneNumber = atoi(argv[1]);
	intervalSec = atof(argv[2]);

	printf("통신 시작\n");

	pthread_t p_thread[2];
    int thr_id;
    int status;
    char p1[] = "thread_1";   // 1번 쓰레드 이름
    char p2[] = "thread_2";   // 2번 쓰레드 이름
//    char pM[] = "thread_m";   // 메인 쓰레드 이름

    sleep(1);  // 2초 대기후 쓰레드 생성
 
    // ① 1번 쓰레드 생성
    // 쓰레드 생성시 함수는 t_server
    // t_server 의 매개변수로 p1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_server, (void *)p1);
 
    // pthread_create() 으로 성공적으로 쓰레드가 생성되면 0 이 리턴됩니다
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // ② 2번 쓰레드 생성
    thr_id = pthread_create(&p_thread[1], NULL, t_urlwrite, (void *)p2);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
 
    printf("언제 종료 될까요?\n");

	return 0;
}

