#include <iostream>
#include <string>
#include <conio.h>

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

int input() {
    cout << "�θ��� ���� �Է� (�����Ϸ��� esc Ű�� ��������) : ";

    romanNum = _getch();
    if (romanNum[0] != 27)
        getline(cin, romanNum);
    else {
        return 1;
    }

    return 0;
}

int gameLoop() {
        
    if (romanNum.empty()) { // �Է� ���� ó��
        cout << "�Է� �����Դϴ�. ���α׷��� �����մϴ�." << endl;
        return 1;
    }

    // �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� ����
    arabicNum = 0;
    for (int i = 0; i < romanNum.length(); i++) {
        if (romanToArabic(romanNum[i]) == 0) { // ��ȿ���� ���� ���� ó��
            cout << "�ٽ� �Է����ּ���." << endl;
            break;
        }
        if (i < romanNum.length() - 1 && romanToArabic(romanNum[i]) < romanToArabic(romanNum[i + 1])) {
            arabicNum -= romanToArabic(romanNum[i]); // ���� ���� ū �� �տ� ���� ���
        }
        else {
            arabicNum += romanToArabic(romanNum[i]);
        }
    }
    cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
    //if (romanNum.length() == arabicNum) { // ��ȿ�� �Է� ó��
    //    cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
    //}
}

int main() {
    
    while (1) 
    {
        input(); //�Է� ����
        gameLoop(); //���� ó�� 
    }

    return 0;
}
