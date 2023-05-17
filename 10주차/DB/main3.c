#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenValues(char* str1, int* intValue, char* charValue, char* strValue) {
    char* Token = strtok(str1, "\n"); // \n으로 토큰 구별

    for (int i = 0; Token != NULL; i++) {
        strcpy(strValue, Token);
        Token = strtok(NULL, "\n");
    }

    char* strArr[100] = { NULL };
    char* strToken = strtok(strValue, " ");
    int i = 0;
    while (strToken != NULL) {
        strArr[i] = strToken;
        i++;
        strToken = strtok(NULL, " ");
    }

    // Find the value for %d
    for (int j = 0; j < i - 1; j++) {
        char* intToken = strstr(strArr[j], "%d");
        if (intToken != NULL) {
            *intValue = atoi(strArr[j + 1]);
            break;
        }
    }

    // Find the value for %c
    for (int j = 0; j < i - 1; j++) {
        char* charToken = strstr(strArr[j], "%c");
        if (charToken != NULL) {
            *charValue = strArr[j + 1][0];
            break;
        }
    }

    for (int j = 0; j < i - 1; j++) {
        char* charToken = strstr(strArr[j], "%c");
        if (charToken != NULL) {
            *charValue = strArr[j + 1][0];
            break;
        }
    }
}

int main() {
    FILE* file = fopen("db.txt", "r");
    if (file == NULL) {
        printf("파일을 읽을 수 없습니다.");
        return 1;
    }

    char str1[1000];
    int intValue = 0;
    char charValue = '\0'; // Initialize charValue to null character
    char strValue[1000];

    while (fgets(str1, sizeof(str1), file)) {
        if (str1[strlen(str1) - 1] == '\n') {
            str1[strlen(str1) - 1] = '\0';
        }

        tokenValues(str1, &intValue, &charValue, strValue);

        printf("정수: %d\n", intValue);
        printf("문자: %c\n", charValue);
    }

    fclose(file);
    return 0;
}