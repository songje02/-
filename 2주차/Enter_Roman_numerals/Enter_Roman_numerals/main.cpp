#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>

using namespace std;

// �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� �Լ�
int romanToArabic(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0;
    }
}

string romanNum;
int arabicNum = 0;

void inputThread() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            exit(0);
        }
    }
}

int Render() {

    while (true) {
        cout << "�θ��� ���ڸ� �Է��ϼ��� (�����Ϸ��� esc Ű�� ��������): ";

        romanNum = _getch();
        if (romanNum[0] != 27)
            getline(cin, romanNum);
        else {
            break;
        }

        if (romanNum.empty()) { // �Է� ���� ó��
            cout << "�Է� �����Դϴ�. ���α׷��� �����մϴ�.";
            return 1;
        }

        // �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� ����
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            // ��ȿ���� ���� ���� ó��
            if (romanToArabic(romanNum[i]) == 0) { // �θ��� ���ڰ� �ƴϸ�
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.";
                break;
            }
            // ���� ���ڰ� �� �� �̻� �ݺ��Ǵ� ��� ó��
            if (i < romanNum.length() - 3 && romanNum[i] == romanNum[i + 1] && romanNum[i + 1] == romanNum[i + 2] && romanNum[i + 2] == romanNum[i + 3]) {
                cout << "�Է°� ������ �Ѿ����ϴ�. �ٽ� �Է����ּ���.";
                break;
            }
            // ���� ���ڰ� �� �� �������� ������ ��� ó��
            if (i < romanNum.length() - 1 && romanNum[i] == romanNum[i + 1] && (romanNum[i] == 'V' || romanNum[i] == 'L' || romanNum[i] == 'D')) {
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.";
                break;
            }
            // ��Ģ�� ��߳��� ������ ��� ó��
            if (i < romanNum.length() - 1 && romanToArabic(romanNum[i]) < romanToArabic(romanNum[i + 1])) {
                if (romanNum[i] == 'I' && (romanNum[i + 1] == 'V' || romanNum[i + 1] == 'X')) {
                    arabicNum -= romanToArabic(romanNum[i]);
                }
                else if (romanNum[i] == 'X' && (romanNum[i + 1] == 'L' || romanNum[i + 1] == 'C')) {
                    arabicNum -= romanToArabic(romanNum[i]);
                }
                else if (romanNum[i] == 'C' && (romanNum[i + 1] == 'D' || romanNum[i + 1] == 'M')) {
                    arabicNum -= romanToArabic(romanNum[i]);
                }
                else {
                    cout << "�߸��� �Է��Դϴ�.";
                }
            }
            else {
                arabicNum += romanToArabic(romanNum[i]);
            }
        }
        cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
    }
}

int main() {

    thread inputThreadObj(inputThread); // ������ ����

    Render();

    inputThreadObj.join(); // ������ ���� ���
    return 0;
}