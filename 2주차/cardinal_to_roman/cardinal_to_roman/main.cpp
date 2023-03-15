#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

// �Է°��� ��ȿ���� Ȯ���ϴ� �Լ�
bool isValidInput(string input) {
    for (char c : input) {
        if (!isdigit(c)) { // �Է°��� ���ڰ� �ƴ� ���
            return 1;
        }
    }
    return true;
}

// �θ��ڷ� ��ȯ�ϴ� �Լ�
string convertToRoman(int num) {
    if (num < 1 || num > 3000) { // �Է°��� ������ ��� ���
        throw out_of_range("�ٽ� �Է����ּ���.");
    }
    if (num == 2999) { // 2999�� ��� MMM���� ���
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
    bool invalidInput = false; // �Է°��� ��ȿ���� ������ ���θ� �����ϴ� ����
    while (true) {
        if (!invalidInput) {
            cout << "���� �Է� (�����Ϸ��� esc Ű�� ��������) :";
        }
        else {
            cout << "�� �� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ��� :";
        }

        input = _getch();
        if (input[0] != 27) {
            getline(cin, input);
        }
        else
            invalidInput = true;
            //return 1;

        if (!isValidInput(input)) { // ��ȿ���� ���� �Է°��� ���
            invalidInput = true;
            continue;
        }
        try {
            num = stoi(input); // �Է°��� ���������� ��ȯ
        }
        catch (invalid_argument&) { // ��ȯ ���� ��
            invalidInput = true;
            continue;
        }
        try {
            string roman = convertToRoman(num); // �θ��ڷ� ��ȯ
            cout << "�θ��ڷ� ��ȯ�� ���: " << roman << endl;
            invalidInput = false;
        }
        catch (out_of_range&) { // ������ ��� �Է°��� ���
            //cout << "Input value out of range." << endl;
            invalidInput = true;
        }
    }
    return 0;
}
