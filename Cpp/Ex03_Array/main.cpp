#include <iostream>
using namespace std;

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    // ...

    // * 배열(Array)
    int my_array[3] = {1, 2, 3}; // 같은 자료형의 데이터를 저장하기 위해 메모리를 미리 잡아놓음

    // 인덱싱 (zero-based)
    for(int i = 0; i < sizeof(my_array) / sizeof(int); i++)
    {
        cout << my_array[i] << " ";
    }
    cout << endl;

    // * 문자열
    /*
    문자 '' 와 문자열 "" 구분
    char[] 초기화시 마지막에 Null character '\0'이 들어감
    */
    char name[] = "Hello, World!";

    cout << name << " " << sizeof(name) << endl;
    name[2] = '\0';
    cout << name << endl; // He

    return 0;
}