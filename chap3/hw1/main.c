#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[5][MAXLINE]; //2차원 배열로 5개 입력
char temp[MAXLINE]; //MAXLINE 100

void copy(char from[], char to[]);

int main() {

	for (int i = 0; i < 5; i++) { //문자열 5개 입력받기
		fgets(line[i], MAXLINE, stdin);
	}
        //temp 배열을 이용해 문자열 수 비교하여 정렬	
	for (int i = 0; i < 4; i++) { 
		for (int j = 0; j < 4; j++) { //j와 j+1을 비교하여 j+1이 크면 자리바꿈
			if (strlen(line[j]) < strlen(line[j + 1])) { //작은 순 일시 >으로 바꿈 
				copy(line[j], temp);
				copy(line[j + 1], line[j]);
				copy(temp, line[j + 1]);
			}
		}
	}

	printf("\n");
	printf("\n");

	for (int i = 0; i < 5; i++) { //결과 값 출력
		printf("%s", line[i]);
	}

	return 0;
}
