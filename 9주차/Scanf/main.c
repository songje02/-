#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myscanf(const char* format, void* d, void* f, void* c, void* str) {
    char input[100];
    char t[] = " \t";
    // ����ڷκ��� ���ڿ� �Է� �ޱ�
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, t);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            switch (format[i])
            {
            case 'd':
                *(int*)d = atoi(token);
                token = strtok(NULL, t); // ���� ���ڿ��� �߶� �����͸� ��ȯ
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

    printf("����, �Ǽ�, ����, ���ڿ��� �Է��ϼ���(����: ����, ��): ");
    myscanf("%d %f %c %s", &num, &f, &c, str);
    printf("[ �Էµ� �� ]\n����: %d / �Ǽ�: %f / ����: %c / ���ڿ�: %s\n", num, f, c, str);

    return 0;
}
