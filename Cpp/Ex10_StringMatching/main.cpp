#include <iostream>
using namespace std;

const int kMaxStr = 100; // 전역 상수

bool IsEqual(const char str1[], const char str2[])
{
    for(int idx = 0; idx < kMaxStr; idx++)
    {
        if(str1[idx] != str2[idx])
            return false;
        
        if(str1[idx] == '\0')
            return true;
    }

    return true;
}

int main()
{
    const char str1[kMaxStr] = "stop";
    char str2[kMaxStr];

    while(true)
    {
        cout << "문자열을 입력하세요 : ";
        cin.getline(str2, sizeof(str2));

        if(IsEqual(str1, str2))
            break;
        
        cout << "계속합니다" << endl;
    }

    cout << "프로그램을 종료합니다!" << endl;

    return 0;
}