#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

// 입력값이 유효한지 확인하는 함수
bool isValidInput(string input) {
    for (char c : input) {
        if (!isdigit(c)) { // 입력값이 숫자가 아닐 경우
            return 1;
        }
    }
    return true;
}

// 로마자로 변환하는 함수
string convertToRoman(int num) {
    if (num < 1 || num > 3000) { // 입력값이 범위를 벗어날 경우
        throw out_of_range("다시 입력해주세요.");
    }
    if (num == 2999) { // 2999일 경우 MMM으로 출력
        return "MMM";
    }
    string roman = "";
    int decimals[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string numerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    for (int i = 0; i < 13; i++) {
        while (num >= decimals[i]) {
            num -= decimals[i];
            roman += numerals[i];
        }
    }
    return roman;
}

int main() {
    string input;
    int num;
    bool invalidInput = false; // 입력값이 유효하지 않은지 여부를 저장하는 변수
    while (true) {
        if (!invalidInput) {
            cout << "숫자 입력 (종료하려면 esc 키를 누르세요) :";
        }
        else {
            cout << "잘 못 입력하셨습니다. 다시 입력해주세요 :";
        }

        input = _getch();
        if (input[0] != 27) {
            getline(cin, input);
        }
        else
            invalidInput = true;
            //return 1;

        if (!isValidInput(input)) { // 유효하지 않은 입력값인 경우
            invalidInput = true;
            continue;
        }
        try {
            num = stoi(input); // 입력값을 정수형으로 변환
        }
        catch (invalid_argument&) { // 변환 실패 시
            invalidInput = true;
            continue;
        }
        try {
            string roman = convertToRoman(num); // 로마자로 변환
            cout << "로마자로 변환한 결과: " << roman << endl;
            invalidInput = false;
        }
        catch (out_of_range&) { // 범위를 벗어난 입력값인 경우
            //cout << "Input value out of range." << endl;
            invalidInput = true;
        }
    }
    return 0;
}
