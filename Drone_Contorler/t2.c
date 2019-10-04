#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
                  //int형 변수 num에 10 할당
    char *pointer_num = malloc(512);
	scanf("%s", pointer_num);    //싱글 포인터 선언 및 num의 주소 값 할당

    char **double_pointer = &pointer_num;    //더블 포인터 선언 및 pointer_num의 주소 할당
    
    printf("pointer_num : %s\n", pointer_num);
    printf("&pointer_num : %d\n", &pointer_num);
    printf("*pointer_num : %d\n", *pointer_num);
    printf("**double_pointer : %d\n", **double_pointer);
    printf("&double_pointer : %d\n", &double_pointer);
    printf("*double_pointer : %d\n", *double_pointer);
    printf("&*double_pointer : %d\n", &*double_pointer);
    printf("double_pointer : %s \n", *double_pointer);    //더블 포인터를 통한 num 값 접근

    printf("오류\n");

    free(pointer_num);

/*  char *input = malloc(512);
	scanf("%s", input);
    printf("%s", input);

    char **argv = &input;
	printf("%s", argv[0]);
*/
}