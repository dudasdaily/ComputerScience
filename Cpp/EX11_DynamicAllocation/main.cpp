#include <iostream>
#include <cstring>
using namespace std;

const int kMaxStr = 100;

int Min(int a, int b)
{
    return (a < b ? a : b);
}

int main()
{
    // 문자열 복사
    // 정적배열, Stack에 저장됨
    char str1[] = "Hello, World!";
    char str2[kMaxStr];

    // str2 = str1; // Error
    
    // * memcpy(dest, src, size)
    memcpy(str2, str1, Min(sizeof(str1), sizeof(str2)));

    // * 동적할당
    // 힙 공간에 char(1 byte) * kMaxStr 만큼 공간을 확보한 뒤 그 공간의 첫번째 주소를 반환.
    char* dynamic_array = new char[kMaxStr];

    memcpy(dynamic_array, str1, Min(sizeof(str1), kMaxStr));

    delete[] dynamic_array; // 지우지 않고 재할당을 할 경우 원래 가리키고 있던 메모리 주소에 접근을 못함.


    return 0;
}