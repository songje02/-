#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myscanf(const char* format, void* d, void* f, void* c, void* str) {
    char input[100];
    char t[] = " \t";
    // 사용자로부터 문자열 입력 받기
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, t);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            switch (format[i])
            {
            case 'd':
                *(int*)d = atoi(token);
                token = strtok(NULL, t); // 다음 문자열을 잘라서 포인터를 반환
                break;
            case 'f':
                *(float*)f = atof(token);
                token = strtok(NULL, t);
                break;
            case 'c':
                *(char*)c = token[0];
                token = strtok(NULL, t);
                break;
            case 's':
                strcpy((char*)str, token);
                token = strtok(NULL, t);
                break;
            default:
                break;
            }
        }
    }
}

int main() {
    int num;
    float f;
    char c, str[100];

    printf("정수, 실수, 문자, 문자열을 입력하세요(구분: 띄어쓰기, 탭): ");
    myscanf("%d %f %c %s", &num, &f, &c, str);
    printf("[ 입력된 값 ]\n정수: %d / 실수: %f / 문자: %c / 문자열: %s\n", num, f, c, str);

    return 0;
}
