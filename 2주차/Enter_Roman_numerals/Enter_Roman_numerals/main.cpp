#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>

using namespace std;

// 로마자 문자를 아라비아 숫자로 변환하는 함수
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
        cout << "로마자 숫자를 입력하세요 (종료하려면 esc 키를 누르세요): ";

        romanNum = _getch();
        if (romanNum[0] != 27)
            getline(cin, romanNum);
        else {
            break;
        }

        if (romanNum.empty()) { // 입력 오류 처리
            cout << "입력 오류입니다. 프로그램을 종료합니다.";
            return 1;
        }

        // 로마자 숫자를 아라비아 숫자로 변환하는 과정
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            // 유효하지 않은 문자 처리
            if (romanToArabic(romanNum[i]) == 0) { // 로마자 문자가 아니면
                cout << "잘못된 입력입니다. 다시 입력해주세요.";
                break;
            }
            // 같은 문자가 네 번 이상 반복되는 경우 처리
            if (i < romanNum.length() - 3 && romanNum[i] == romanNum[i + 1] && romanNum[i + 1] == romanNum[i + 2] && romanNum[i + 2] == romanNum[i + 3]) {
                cout << "입력값 범위를 넘었습니다. 다시 입력해주세요.";
                break;
            }
            // 같은 문자가 두 번 연속으로 나오는 경우 처리
            if (i < romanNum.length() - 1 && romanNum[i] == romanNum[i + 1] && (romanNum[i] == 'V' || romanNum[i] == 'L' || romanNum[i] == 'D')) {
                cout << "잘못된 입력입니다. 다시 입력해주세요.";
                break;
            }
            // 규칙에 어긋나는 조합의 경우 처리
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
                    cout << "잘못된 입력입니다.";
                }
            }
            else {
                arabicNum += romanToArabic(romanNum[i]);
            }
        }
        cout << "아라비아 숫자로 변환한 결과: " << arabicNum << endl;
    }
}

int main() {

    thread inputThreadObj(inputThread); // 스레드 생성

    Render();

    inputThreadObj.join(); // 스레드 종료 대기
    return 0;
}