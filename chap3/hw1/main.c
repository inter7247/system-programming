#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[5][MAXLINE]; //2차원 배열로 5개 입력
char temp[MAXLINE];

void copy(char from[], char to[]);

int main() {
	int len, max = 0;

	for (int i = 0; i < 5; i++) { //문자열 5개 입력받기
		fgets(line[i], MAXLINE, stdin);
	}
	
	for (int i = 0; i < 4; i++) { //temp 배열을 이용해 문자열 수 비교하여 정렬
		for (int j = 0; j < 4; j++) {
			if (strlen(line[j]) < strlen(line[j + 1])) {
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
