#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[5][MAXLINE];
char temp[MAXLINE];

void copy(char from[], char to[]);

int main() {
	int len, max = 0;

	for (int i = 0; i < 5; i++) {
		fgets(line[i], MAXLINE, stdin);
	}
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (strlen(line[j]) < strlen(line[j + 1])) {
				copy(line[j], temp);
				copy(line[j + 1], line[j]);
				copy(temp, line[j + 1]);
			}
		}
	}
	printf("\n");

	for (int i = 0; i < 5; i++) {
		printf("%s", line[i]);
	}

	return 0;
}
