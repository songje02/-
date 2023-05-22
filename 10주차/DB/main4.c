//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//void tokenValues(char* str1, char* str2, int* intValue, char* charValue, char* strValue) {
//    char* strArr[100] = { NULL };
//    char* strToken = strtok(str2, " ");
//    int i = 0;
//    while (strToken != NULL) {
//        strArr[i] = strToken;
//        i++;
//        strToken = strtok(NULL, " ");
//    }
//
//    // Find and store integer value
//    char* intToken = strstr(str1, "%d");
//    if (intToken != NULL) {
//        int index = atoi(intToken + 2) - 1; // Adjust index by subtracting 1
//        if (index < i) {
//            *intValue = atoi(strArr[index]);
//        }
//    }
//
//    // Find and store character value
//    char* charToken = strstr(str1, "%c");
//    if (charToken != NULL) {
//        int index = atoi(charToken + 2) - 1; // Adjust index by subtracting 1
//        if (index < i) {
//            *charValue = strArr[index];
//        }
//    }
//
//    // Find and store string value
//    char* strToken2 = strstr(str1, "%s");
//    if (strToken2 != NULL) {
//        int index = atoi(strToken2 + 2) - 1; // Adjust index by subtracting 1
//        if (index < i) {
//            strcpy(strValue, strArr[index]);
//            *intValue = strlen(strArr[index]);
//        }
//    }
//}
//
//int main() {
//    FILE* file = fopen("db.txt", "r");
//    if (file == NULL) {
//        printf("파일을 열 수 없습니다.");
//        return 1;
//    }
//
//    char str1[1000];
//    char str2[1000];
//    int intValue;
//    char charValue;
//    char strValue[1000];
//
//    while (fgets(str1, sizeof(str1), file) && fgets(str2, sizeof(str2), file)) {
//        if (str1[strlen(str1) - 1] == '\n') {
//            str1[strlen(str1) - 1] = '\0';
//        }
//
//        if (str2[strlen(str2) - 1] == '\n') {
//            str2[strlen(str2) - 1] = '\0';
//        }
//
//        tokenValues(str1, str2, &intValue, &charValue, strValue);
//
//        printf("정수: %d\n", intValue);
//        printf("문자: %c\n", charValue);
//        printf("문자열: %s\n", strValue);
//    }
//
//    fclose(file);
//
//    return 0;
//}
