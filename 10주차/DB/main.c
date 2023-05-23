#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveValues(const char* str1, const char* str2, char* strVal, int* intVal, char* charVal) {
    char* tokens1[100];
    char* tokens2[100];
    int tokenCount1 = 0;
    int tokenCount2 = 0;

    char* token = strtok(str1, " ");
    while (token != NULL) {
        tokens1[tokenCount1++] = token;
        token = strtok(NULL, " ");
    }

    token = strtok(str2, " ");
    while (token != NULL) {
        tokens2[tokenCount2++] = token;
        token = strtok(NULL, " ");
    }
    for (int i = 0; i < tokenCount1; i++) {
        if (strcmp(tokens1[i], tokens2[i]) != 0) {
            // 문자열
            if (strstr(tokens1[i], "%s") != NULL) {
                strcpy(strVal, tokens2[i]);
            }
            // 정수
            else if (strstr(tokens1[i], "%d") != NULL) {
                *intVal = atoi(tokens2[i + 1]) / 10000;
            }
            // 문자
            else if (strstr(tokens1[i], "%c") != NULL) {
                *charVal = tokens2[i + 1][0];
            }
        }
    }
}

int main() {
    FILE* file = fopen("db.txt", "r");
    if (file == NULL) {
        printf("파일을 읽을 수 없습니다.");
        return 1;
    }

    char str1[100];
    char str2[100];
    char strVal[100];
    int intVal;
    char charVal;

    while (fgets(str1, sizeof(str1), file) && fgets(str2, sizeof(str2), file)) {
        if (str1[strlen(str1) - 1] == '\n') {
            str1[strlen(str1) - 1] = '\0';
        }

        if (str2[strlen(str2) - 1] == '\n') {
            str2[strlen(str2) - 1] = '\0';
        }

        saveValues(str1, str2, strVal, &intVal, &charVal);

        printf("이름: %s\n", strVal);
        printf("점수: %d\n", intVal);
        printf("성적: %c\n", charVal);
        printf("\n");
    }

    fclose(file);

    return 0;
}
