#include <iostream>
using namespace std;

int main()
{
    int a = 123;
    int* b = &a;

    cout << a << " " << b << endl;
    *b = 321;
    cout << a << " " << b << " " << *b << endl;
    
    double* c = 0; // = double* c = nullptr;

    // * 포인터 연산과 배열

    // size_t 자료형(여기서는 주소를 10진수로 변환 용도)
    cout << sizeof(size_t) << endl; // 8
    cout << size_t(b) << " " << size_t(b + 1) << " " << size_t(b + 2) << endl; // int* b에 1을 더하면 4가 더해짐
    cout << size_t(c) << " " << size_t(c + 1) << " " << size_t(c + 2) << endl; // double* c에 1을 더하면 8이 더해짐

    // 배열 == 포인터
    char my_str[] = {'a', 'b', 'c', 'd', 'e'};
    char* ptr = my_str;
    ptr += 2;
    cout << *(ptr + 2) << endl;

    return 0;
} 