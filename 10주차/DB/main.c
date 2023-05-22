#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveValues(const char* str1, const char* str2, int* intValue, char* charValue, char* strValue) {
    char* token = strtok(str2, " ");

    // 정수
    char* intToken = strstr(str1, "%d");
    if (intToken != NULL) {
        *intValue = atoi(token);
        token = strtok(NULL, " ");
    }

    // 문자
    char* charToken = strstr(str1, "%c");
    if (charToken != NULL) {
        *charValue = token[0];
        token = strtok(NULL, " ");
    }

    // 문자열
    char* strToken = strstr(str1, "%s");
    if (strToken != NULL) {
        strcpy(strValue, token);
        token = strtok(NULL, " ");
    }
}

int main() {
    FILE* file = fopen("db.txt", "r");
    if (file == NULL) {
        printf("파일을 읽으 수 없습니다.");
        return 1;
    }

    char str1[100];
    char str2[100];
    int* intValue;
    char* charValue;
    char* strValue[100];

    while (fgets(str1, sizeof(str1), file) && fgets(str2, sizeof(str2), file)) {
        if (str1[strlen(str1) - 1] == '\n') {
            str1[strlen(str1) - 1] = '\0';  
        }

        if (str2[strlen(str2) - 1] == '\n') {
            str2[strlen(str2) - 1] = '\0'; 
        }

        saveValues(str1, str2, &intValue, &charValue, strValue);

        printf("정수: %d\n", intValue);
        printf("문자: %c\n", charValue);
        printf("문자열: %s\n", strValue);
        printf("\n");
    }

    fclose(file);

    return 0;
}