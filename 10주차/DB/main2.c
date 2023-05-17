//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//void tokenValues(char* str1, int* intValue, char* charValue, char* strValue) {
//    char* Token = strtok(str1, "\n"); //\n으로 토큰 구별
//
//    for (int i = 0; Token != NULL; i++) {
//        strcpy(strValue, Token);
//        //printf("%s", Token);
//        Token = strtok(NULL, "\n");
//        
//    }
//    
//    //
//    char* strArr[100] = { NULL, };
//    char* strToken = { strtok(str1, " ") };
//    for (int i = 0; strToken != NULL; i++) {
//        strArr[i] = strToken;
//        strcpy(strValue, strToken);
//        printf("문자열: %s\n", strValue);
//        strToken = strtok(NULL, " ");
//
//
//    //    // 정수
//    //    char* intToken = strstr(strArr[i - 1], "%d");
//    //    if (intToken != NULL) {
//    //        *intValue = atoi(strArr[i]);
//    //    }
//
//    //    // 문자
//    //    char* charToken = strstr(strArr[i - 1], "%c");
//    //    if (charToken != NULL) {
//    //        *charValue = strArr[i][0];
//    //    }
//
//    //    // 문자열
//    //    char* strToken2 = strstr(strArr[i - 1], "%s");
//    //    if (strToken2 != NULL) {
//    //        strcpy(strValue, strArr[i]);
//    //    }
//    }
//    //// 정수
//    //char* intToken = strstr(strArr, "%d");
//    //if (intToken != NULL) {
//    //    *intValue = atoi(strArr[5]);
//    //    //strValue = strtok(NULL, " ");
//    //}
//
//    //// 문자
//    //char* charToken = strstr(str1, "%c");
//    //if (charToken != NULL) {
//    //    *charValue = strValue[0];
//    //    strValue = strtok(NULL, " ");
//    //}
//
//    //// 문자열
//    //char* strToken2 = strstr(str1, "%s");
//    //if (strToken2 != NULL) {
//    //    strcpy(strValue, strValue);
//    //    strValue = strtok(NULL, " ");
//    //}
//}
//
//int main() {
//    FILE* file = fopen("db.txt", "r");
//    if (file == NULL) {
//        printf("파일을 읽으 수 없습니다.");
//        return 1;
//    }
//
//    char str1[1000];
//    int* intValue;
//    char* charValue;
//    char* strValue[1000];
//
//    while (fgets(str1, sizeof(str1), file)) {
//        if (str1[strlen(str1) - 1] == '\n') {
//            str1[strlen(str1) - 1] = '\0';
//        }
//
//        tokenValues(str1, &intValue, &charValue, strValue);
//
//        
//
//        //printf("정수: %d\n", &intValue);
//        //printf("문자: %c\n", charValue);
//        //printf("문자열: %s\n", strValue);
//
//    }
//
//    fclose(file);
//
//    return 0;
//}